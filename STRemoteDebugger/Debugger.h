#pragma once
#include <wtypes.h>
#include "cDynArray.h"
#include <stdio.h>
#include "mString.h"

#define MEMORY_BUFFER_SIZE				(1024 * 4)			// 4K
#define OPCODE_TEXT_BUFFER_SIZE			64
#define	MEMORY_WINDOW_LINES				10
#define MEMORY_WINDOW_COLUMNS			8
#define MEMORY_WINDOW_BYTES_PER_COLUMN	4
#define MEMORY_WINDOW_BYTES_PER_LINE	MEMORY_WINDOW_BYTES_PER_COLUMN * MEMORY_WINDOW_COLUMNS				// 4 bytes per entry / 16 columns

class ComPort
{
public:
	ComPort()
	{
	}

	~ComPort()
	{
	}

	mString PortName;
	mString PortDescription;
};

class OpcodeInstruction
{
public:
	OpcodeInstruction(int pOpCode, const char* pText, const char* pLabel, const char* pComment)
	{
		Opcode = pOpCode;
		Text = pText;
		Label = pLabel;
		Comment = pComment;
		BreakpointSet = false;
	}

	~OpcodeInstruction() 
	{
	}

	int		Opcode = 0;									// raw 68K opcode
	mString Text;
	mString Label;
	mString Comment;
	bool	BreakpointSet = false;						// set breakpoint
	u32		Color = 0xFFFFFFFF;							// Color for line
};

class Register
{
public:
	Register(u32 pValue, const char* pLabel, char* const pComment)
	{
		SetValue(pValue);
		Label = pLabel;
		Comment = pComment;
	}

	~Register()
	{
	}

	void SetValue(u32 pValue)
	{
		ValueString.Set("0x%08x", pValue);
	}

	u32		Value = 0;				// register value
	mString Label;
	mString Comment;
	mString ValueString;
	u32		Color = 0xFFFFFFFF;		// Color for register
};

// Main Class
class STDebugger
{
public:
	STDebugger();
	~STDebugger();

	// Methods
	void Init(void* formPtr);
	void Shutdown();

	void ConnectToTarget();
	void DisconnectFromTarget();
	void LoadExecutable(LPCWSTR Filename);
	void SetStartingMemoryAddress(u32 Address);
	void LoadMemory(char* SrcData);

	u32 GetMemoryWindowFirstCharacterPosition() { return MemoryWindowFirstCharacterPosition; }
	u32	GetMemoryWindowLineLength() { return MemoryWindowLineLength; }
	u32 GetMemoryWindowWrapRight() { return MemoryWindowWrapRight; }
	u32 GetMemoryWindowLastCharacterOfFirstLine() { return MemoryWindowLastCharacterOfFirstLine; }
	u32 GetMemoryWindowLastCharacterOfFirstLineAscii() { return MemoryWindowLastCharacterOfFirstLineAscii; }
	u32 GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii() { return MemoryWindowFirstCharacterPositionOfFirstLineOfAscii; }

	bool GetMemoryAddressChanged() { return MemoryAddressChanged; }
	void SetMemoryAddressChanged(bool pMemoryAddressChanged) { MemoryAddressChanged = pMemoryAddressChanged; }
	bool GetMemoryWindowInAsciiBlock() { return MemoryWindowInAsciiBlock; }
	void SetMemoryWindowInAsciiBlock(bool pMemoryWindowInAsciiBlock) { MemoryWindowInAsciiBlock = pMemoryWindowInAsciiBlock; }

	DynArray<ComPort*>&	GetComPortsArray() { return ComPorts; }
	char* GetComPortName() { return ComPortName.GetPtr(); }
	void SetComPortName(char* pComPortName) { ComPortName = pComPortName; }
	void SetBaudRate(u32 pBaudRate) { BaudRate = pBaudRate; }
	u32 GetBaudRate() { return BaudRate;  }

	// clear refs
	void ClearMainWindowPreferencesReference();

	void DebugMemoryData();


	HANDLE GetSerialPortHandle() { return SerialPortHandle; }

private:
	void	GetComPortsAvailable();
	void	ParseProgram();
	void	SetupRegisters();
	void	SetupMemory();

	// log
	void	OutputToLog(mString Text);

	// disasm
	int		GetMode(int instruction);
	int		GetWord();
	void	SprintMode(unsigned int mode, unsigned int reg, unsigned int size, char* out_s);

	// serial 
	bool	SetSerialConfig();
	bool	SendPacket(u8* packet, u32 NumBytes = 0);
	void	SendCmd(u8 Cmd, u32 MemoryAdress = 0, u32 NumBytes = 0);
	void	ProcessCommand(u8* packet);

	// thread
	s32		CreateTickThread();
	void	ShutdownThreads();
	static unsigned int __stdcall TickThread(void* lpParameter);

//	u32		TickThread(void* lpParameter);
	u8*		LoadBufferPtr = nullptr;
	bool	rawmode = false;

	// Vars
	u32								LoadBufferSize = 0;
	DynArray<OpcodeInstruction*>	Opcodes;			// opcodes for the program
	DynArray<Register*>				DataRegisters;		// CPU registers
	DynArray<Register*>				AddressRegisters;	// CPU registers
	Register*						PC = nullptr;		// Program counter
	Register*						SR = nullptr;		// Status register
	char*							LoadBuffer = nullptr;	// where raw 68K program is loaded

	// Memory window
	char*	MemoryBuffer = nullptr;		// memory buffer for memory window
	u32		MemoryStartAddress = 0;		// Start Address of memory buffer
	u32		MemoryBytesPerLine = 0;		// Bytes per line
	u32		MemoryBytesPerColumn = 0;	// Byters per column
	u32		MemoryWindowFirstCharacterPosition = 11;
	u32		MemoryWindowLastCharacterOfFirstLine = 88;
	u32		MemoryWindowFirstCharacterPositionOfFirstLineOfAscii = 92;
	u32		MemoryWindowLastCharacterOfFirstLineAscii = 123;
	u32		MemoryWindowLineLength = 125;
	u32		MemoryWindowWrapRight = 12;
	bool	MemoryAddressChanged = false;
	bool	MemoryWindowInAsciiBlock = false;

	// disassembler
	u32 address = 0;
	u32 programStart = 0;
	u32 currentWord = 0;

	// form references
	void* FormWindow = nullptr;

	// Serial port
	DynArray<ComPort*>	ComPorts;
	mString				ComPortName = "COM1";
	u32					BaudRate = 19200;
	HANDLE				SerialPortHandle = INVALID_HANDLE_VALUE;

	// threads
	u32					TickThreadHandle = 0;
	u32					TickThreadID = 0;
	bool				TickFunctionExit = false;
};
