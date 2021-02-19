#pragma once
#include <wtypes.h>
#include "cDynArray.h"
#include <stdio.h>

#define MEMORY_BUFFER_SIZE				(1024 * 4)			// 4K
#define OPCODE_TEXT_BUFFER_SIZE			64
#define	MEMORY_WINDOW_LINES				10
#define MEMORY_WINDOW_COLUMNS			8
#define MEMORY_WINDOW_BYTES_PER_COLUMN	4
#define MEMORY_WINDOW_BYTES_PER_LINE	MEMORY_WINDOW_BYTES_PER_COLUMN * MEMORY_WINDOW_COLUMNS				// 4 bytes per entry / 16 columns

class OpcodeInstruction
{
public:
	OpcodeInstruction(int pOpCode, const char* pText, const char* pLabel, const char* pComment)
	{
		Opcode = pOpCode;
		memset(Text, 0, OPCODE_TEXT_BUFFER_SIZE);
		strcpy(Text, pText);
		Label = new char[strlen(pLabel) + 1];
		strcpy(Label, pLabel);
		Comment = new char[strlen(pComment) + 1];
		strcpy(Comment, pComment);
		BreakpointSet = false;
	}

	~OpcodeInstruction() 
	{
	}

	int		Opcode = 0;									// raw 68K opcode
	char	Text[OPCODE_TEXT_BUFFER_SIZE] = { 0 };		// text conversion of the opcode
	char*	Label = nullptr;							// label
	char*	Comment = nullptr;							// comment
	bool	BreakpointSet = false;						// set breakpoint
};

class Register
{
public:
	Register(u32 pValue, const char* pLabel, char* const pComment)
	{
		SetValue(pValue);
		Label = new char[strlen(pLabel) + 1];
		strcpy(Label, pLabel);
		Comment = new char[strlen(pComment) + 1];
		strcpy(Comment, pComment);
	}

	~Register()
	{
		if (Label)
			delete[] Label;
		if (Comment)
			delete[] Comment;
	}

	void SetValue(u32 pValue)
	{
		sprintf(ValueString, "0x%08x", pValue);
	}

	u32		Value = 0;				// register value
	char*	Label = nullptr;		// label
	char*	Comment = nullptr;		// comment
	char	ValueString[12] = { 0 };// value as a string
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


	void DebugMemoryData();

private:
	void	ParseProgram();
	void	SetupRegisters();
	void	SetupMemory();
	int		GetMode(int instruction);
	int		GetWord();
	void	SprintMode(unsigned int mode, unsigned int reg, unsigned int size, char* out_s);

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


};
