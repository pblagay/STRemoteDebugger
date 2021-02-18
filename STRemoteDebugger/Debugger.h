#pragma once
#include <wtypes.h>
#include "cDynArray.h"
#include <stdio.h>

class OpcodeInstruction
{
public:
	OpcodeInstruction(int pOpCode, const char* pText, const char* pLabel, const char* pComment)
	{
		Opcode = pOpCode;
		memset(Text, 0, sizeof(Text));
		strcpy(Text, pText);
		Label = new char[strlen(pLabel) + 1];
		strcpy(Label, pLabel);
		Comment = new char[strlen(pComment) + 1];
		strcpy(Comment, pComment);
	}

	~OpcodeInstruction() 
	{
	}

	int		Opcode = 0;				// raw 68K opcode
	char	Text[64] = { 0 };		// text conversion of the opcode
	char*	Label = nullptr;		// label
	char*	Comment = nullptr;		// comment
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
	char* LoadBuffer;	// where raw 68K program is loaded
	u32								LoadBufferSize;
	DynArray<OpcodeInstruction*>	Opcodes;			// opcodes for the program
	DynArray<Register*>				DataRegisters;		// CPU registers
	DynArray<Register*>				AddressRegisters;	// CPU registers
	Register*						PC = nullptr;		// Program counter
	Register*						SR = nullptr;		// Status register

	// disassembler
	u32 address = 0;
	u32 programStart = 0;
	u32 currentWord = 0;

	// form references
	void* FormWindow = nullptr;
};
