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
#define MEMORY_WINDOW_BYTES_PER_LINE	(MEMORY_WINDOW_BYTES_PER_COLUMN * MEMORY_WINDOW_COLUMNS	)			// 4 bytes per entry / 16 columns

// window updates
#define UPDATE_REGISTERS_WINDOW			0x01
#define UPDATE_MEMORY_WINDOW			0x02

// line lengths etc
#define ASMWINDOW_LINE_LENGTH			48
#define ASMWINDOW_BP_LOCATION			20
#define ASMWINDOW_PC_LOCATION			22

// memory sizes by platform
#define	ATARI_520ST_MEMORY				(1024 * 512)							// 512 K
#define	ATARI_1040ST_MEMORY				(1024 * 1024)							// 1 MB
#define	ATARI_ST_MID_MEMORY				((1024 * 1024 ) * 2) + (512 * 1024)		// 2.5MB
#define	ATARI_ST_MAX_MEMORY				(1024 * 1024) * 4						// 4MB max
#define	ATARI_TT_MAX_MEMORY				(1024 * 1024) * 4						// 4MB max
#define	ATARI_FALCON_MAX_MEMORY			(1024 * 1024) * 14						// 14MB max

// computer type
#define COMPUTER_TYPE_ATARI_ST			0
#define	COMPUTER_TYPE_ATARI_STE			1
#define COMPUTER_TYPE_ATARI_TT			2
#define COMPUTER_TYPE_ATARI_FALCON		3

class Disassembler68K;

// Atari ST executable program header
typedef struct
{
	u16  ph_branch;			/* Branch to start of the program  */
							/* (must be 0x601a!)               */

	u16  ph_tlen[2];        /* Length of the TEXT segment      */
	u16  ph_dlen[2];        /* Length of the DATA segment      */
	u16  ph_blen[2];        /* Length of the BSS segment       */
	u16  ph_slen[2];        /* Length of the symbol table      */
	u16  ph_res1[2];        /* Reserved, should be 0;          */
							/* Required by PureC               */
	u16  ph_prgflags[2];    /* Program flags                   */
	u16  ph_absflag;		/* 0 = Relocation info present     */
} ProgramHeader;

class BreakPoint
{
public:
	BreakPoint()
	{
	}

	~BreakPoint()
	{
	}

	u32		LineNumber = 0;
	bool	Enabled = false;
};

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
		LastValue = Value;
		Value = pValue;
		ValueString.Set("0x%08x", pValue);
	}

	u32		LastValue = 0;			// last val (used to change register color if changed)
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

	void ReadIniFile();
	void WriteIniFile();

	void LoadExecutable(LPCWSTR Filename);
	void SetStartingMemoryAddress(u32 Address);
	void CreateMemoryBuffer();
	void SetupMemory();

//	void LoadMemory(u8* SrcData);

	// cmds
	void ConnectToTarget();
	void DisconnectFromTarget();
	void DisconnectFromTargetComplete();
	void RequestRegisters();
	void RequestMemory(u32 Address = 0, u32 Blocksize = MEMORY_BUFFER_SIZE);		// default to getting 4k blocks
	void DisassembleCode();
	void Run();
	void Stop();
	void StepOver();
	void StepInto();
	void StepOut();
	void RunToCursor();
	void SetPC();
	
	u32 GetMemoryWindowFirstCharacterPosition();
	u32	GetMemoryWindowLineLength();
	u32 GetMemoryWindowWrapRight();
	u32 GetMemoryWindowLastCharacterOfFirstLine();
	u32 GetMemoryWindowLastCharacterOfFirstLineAscii();
	u32 GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii();

	bool GetMemoryAddressChanged() { return MemoryAddressChanged; }
	void SetMemoryAddressChanged(bool pMemoryAddressChanged) { MemoryAddressChanged = pMemoryAddressChanged; }
	bool GetMemoryWindowInAsciiBlock() { return MemoryWindowInAsciiBlock; }
	void SetMemoryWindowInAsciiBlock(bool pMemoryWindowInAsciiBlock) { MemoryWindowInAsciiBlock = pMemoryWindowInAsciiBlock; }

	DynArray<ComPort*>&	GetComPortsArray() { return ComPorts; }
	char* GetComPortName() { return ComPortName.GetPtr(); }
	void SetComPortName(char* pComPortName) { ComPortName = pComPortName; }
	void SetBaudRate(u32 pBaudRate) { BaudRate = pBaudRate; }
	u32 GetBaudRate() { return BaudRate;  }

	bool GetReceiveInProgress() { return ReceiveInProgress; }
	void SetReceiveInProgress(bool pReceiveInProgress) { ReceiveInProgress = pReceiveInProgress; }
	bool GetSendInProgress() { return SendCmdInProgress; }
	void SetSendInProgress(bool pSendCmdInProgress) { SendCmdInProgress = pSendCmdInProgress; }

	void SetSendCmdTimeout(s32 pTimeout) { SendCmdTimeout = pTimeout;  }
	s32  GetSendCmdTimeout() { return SendCmdTimeout; }

	// clear refs
	void ClearMainWindowPreferencesReference();

	void DebugMemoryData();
	void RefreshWindows();

	HANDLE GetSerialPortHandle() { return SerialPortHandle; }
	bool GetIsConnectedToTarget() { return (SerialPortHandle != INVALID_HANDLE_VALUE);  }

	u8* GetReadBuffer() { return ReadBuffer; };
	u8 GetLastCommand() { return LastCommand; }

	void SetBreakpoint(u32 LineNumber);
	void RemoveBreakpoint(u32 LineNumber);
	u32	 GetCurrentLine() { return CurrentLine; }
	void SetCurrentLine(u32 LineNumber);

	u32 GetDataRegisterValue(u32 index) { return DataRegisters[index]->Value; }
	u32 GetAddressRegisterValue(u32 index) { return AddressRegisters[index]->Value; }
	u32 GetPCRegisterValue(u32 index) { return PC->Value; }
	u32 GetSRRegisterValue(u32 index) { return SR->Value; }
	u32 GetSSPRegisterValue(u32 index) { return SSP->Value; }

	u32 GetMemoryBlockIndex() {	return MemoryBlockIndex;  }

	u32	 GetTosVersion() { return TosVersion; }
	void SetTosVersion(u32 pTosVersion) { TosVersion = pTosVersion; }
	u32	 GetComputerType() { return ComputerType; }
	void SetComputerType(u32 pComputerType) { ComputerType = pComputerType; }
	u32	 GetSystemMemory() { return SystemMemory; }
	void SetSystemMemory(u32 pSystemMemory) { SystemMemory = pSystemMemory; }

	void SetMemoryViewSize(u32 pMemoryViewSize) { MemoryViewSize = pMemoryViewSize; }
	u32  GetMemoryViewSize() { return MemoryViewSize; }

	void SetMemoryWindowNumberOfColumns(u32 pMemoryWindowNumberOfColumns) { MemoryWindowNumberOfColumns = pMemoryWindowNumberOfColumns; }
	u32  GetMemoryWindowNumberOfColumns() { return MemoryWindowNumberOfColumns; }

	void SetMemoryViewSelectedColumnIndex(u32 pMemoryViewSelectedColumnIndex) { MemoryViewSelectedColumnIndex = pMemoryViewSelectedColumnIndex; }
	u32  GetMemoryViewSelectedColumnIndex() { return MemoryViewSelectedColumnIndex; }

private:
	void	GetComPortsAvailable();
	void	SetupRegisters();
	void	UpdateRegisters();
	void	UpdateLog();
	void	RedrawBreakpoints();

	// log
	void	OutputToLog(mString Text);
	DynArray<mString*>	LogQueue;

	// disasm
	int		GetMode(int instruction);
	int		GetWord();
	void	SprintMode(unsigned int mode, unsigned int reg, unsigned int size, char* out_s);

	// serial 
	bool	SetSerialConfig();
	bool	SendPacket(u8* packet, u32 NumBytes = 0);
	void	SendCmd(u8 Cmd, u32 MemoryAddress = 0, u32 NumBytes = 0);
	void	ProcessCommand(u8 Cmd, u8* packet);
	void	SetCmdInProgress(u8 Cmd);

	// thread
	s32		CreateTickThread();
	void	ShutdownThreads();
	static unsigned int __stdcall TickThread(void* lpParameter);

//	u32		TickThread(void* lpParameter);
	u8*		LoadBufferPtr = nullptr;
	bool	rawmode = false;

	// Vars
	DynArray<OpcodeInstruction*>	Opcodes;			// opcodes for the program
	DynArray<Register*>				DataRegisters;		// CPU registers
	DynArray<Register*>				AddressRegisters;	// CPU registers
	Register*						PC = nullptr;		// Program counter
	Register*						SR = nullptr;		// Status register
	Register*						SSP = nullptr;		// SSP
	u8*								LoadBuffer = nullptr;	// where raw 68K program is loaded
	u32								LoadBufferSize = 0;		// loaded size of buffer
	u32								LoadedCodeSize = 0;		// code size minus a header if it exists

	// Memory window
	u8	*	MemoryBuffer = nullptr;		// memory buffer for memory window
	u32		MemoryStartAddress = 0;		// Start Address of memory buffer
	u32		MemoryBlockIndex = 0;		// what block are we in
	u32		MemoryBytesPerLine = 0;		// Bytes per line
	u32		MemoryBytesPerColumn = 0;	// Byter per column
	u32		MemoryWindowNumberOfColumns = 8; 

	// need to be adjusted depending on view
	u32		MemoryWindowFirstCharacterPosition = 11;
	u32		MemoryWindowLastCharacterOfFirstLine = 88;
	u32		MemoryWindowFirstCharacterPositionOfFirstLineOfAscii = 92;
	u32		MemoryWindowLastCharacterOfFirstLineAscii = 123;
	u32		MemoryWindowLineLength = 125;
	u32		MemoryWindowWrapRight = 12;

	bool	MemoryAddressChanged = false;
	bool	MemoryWindowInAsciiBlock = false;
	u32		MemoryViewSize = 0;			// 4 byte / 2 byte / 1 byte view
	u32		MemoryViewSelectedColumnIndex = 3;

	// disassembler
	u32 address = 0;
	u32 programStart = 0;
	u32 currentWord = 0;
	u32 currentCPUType = 0;
	u32 NumberOfLinesInProgram = 0;
	u32 CurrentLine = 0;

	// Breakpoints
	void ClearBreakpoints();
	DynArray<BreakPoint*> BreakPoints;

	// form references
	void* FormWindow = nullptr;

	// Serial port
	DynArray<ComPort*>	ComPorts;
	mString				ComPortName = "COM1";
	u32					BaudRate = 19200;
	HANDLE				SerialPortHandle = INVALID_HANDLE_VALUE;
	bool				SendCmdInProgress = false;
	bool				ReceiveInProgress = false;

	// threads
	u32					TickThreadHandle = 0;
	u32					TickThreadID = 0;
	bool				TickFunctionExit = false;
	s32					SendCmdTimeout = 0;
	u8					LastCommand = 0;

	// read buffer
	u8*					ReadBuffer = nullptr;

	// update windows (threading)
	u32					UpdateWindowMask = 0;

	// prefs
	u32					TosVersion = 104;
	u32					ComputerType = COMPUTER_TYPE_ATARI_ST;
	u32					SystemMemory = ATARI_ST_MAX_MEMORY;
};
