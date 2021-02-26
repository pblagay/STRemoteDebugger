//******************************************************//
// ST Remote Debugger									//
// 														//
// Author: Paul Blagay									//
//														//
//														//
// Copyright (C) 2021 Biotic Software LLC.				//
//******************************************************//

#include <stdio.h>
#include <process.h>
#include "Form1.h"
#include "Debugger.h"
#include "Commands.h"
#include "..\..\..\VariousSourceCodes\minIni-master\dev\minIni.h"
#include "68kDisasm.h"

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))
const char inifile[] = "STRemoteDebugger.ini";



using namespace System;

// opcodes
struct OpcodeDetails 
{
	u16 and;
	u16 xor;
};

const struct OpcodeDetails optab[88] = {
	{0x0000,0x0000}, {0xF1F0,0xC100}, {0xF000,0xD000}, {0xF0C0,0xD0C0},
	{0xFF00,0x0600}, {0xF100,0x5000}, {0xF130,0xD100}, {0xF000,0xC000},
	{0xFF00,0x0200}, {0xF118,0xE100}, {0xFFC0,0xE1C0}, {0xF118,0xE000},
	{0xFFC0,0xE0C0}, {0xF000,0x6000}, {0xF1C0,0x0140}, {0xFFC0,0x0840},
	{0xF1C0,0x0180}, {0xFFC0,0x0880}, {0xF1C0,0x01C0}, {0xFFC0,0x08C0},
	{0xF1C0,0x0100}, {0xFFC0,0x0800}, {0xF1C0,0x4180}, {0xFF00,0x4200},
	{0xF100,0xB000}, {0xF0C0,0xB0C0}, {0xFF00,0x0C00}, {0xF138,0xB108},
	{0xF0F8,0x50C8}, {0xF1C0,0x81C0}, {0xF1C0,0x80C0}, {0xF100,0xB100},
	{0xFF00,0x0A00}, {0xF100,0xC100}, {0xFFB8,0x4880}, {0xFFC0,0x4EC0},
	{0xFFC0,0x4E80}, {0xF1C0,0x41C0}, {0xFFF8,0x4E50}, {0xF118,0xE108},
	{0xFFC0,0xE3C0}, {0xF118,0xE008}, {0xFFC0,0xE2C0}, {0xC000,0x0000},
	{0xFFC0,0x44C0}, {0xFFC0,0x46C0}, {0xFFC0,0x40C0}, {0xFFF0,0x4E60},
	{0xC1C0,0x0040}, {0xFB80,0x4880}, {0xF138,0x0108}, {0xF100,0x7000},
	{0xF1C0,0xC1C0}, {0xF1C0,0xC0C0}, {0xFFC0,0x4800}, {0xFF00,0x4400},
	{0xFF00,0x4000}, {0xFFFF,0x4E71}, {0xFF00,0x4600}, {0xF000,0x8000},
	{0xFF00,0x0000}, {0xFFC0,0x4840}, {0xFFFF,0x4E70}, {0xF118,0xE118},
	{0xFFC0,0xE7C0}, {0xF118,0xE018}, {0xFFC0,0xE6C0}, {0xF118,0xE110},
	{0xFFC0,0xE5C0}, {0xF118,0xE010}, {0xFFC0,0xE4C0}, {0xFFFF,0x4E73},
	{0xFFFF,0x4E77}, {0xFFFF,0x4E75}, {0xF1F0,0x8100}, {0xF0C0,0x50C0},
	{0xFFFF,0x4E72}, {0xF000,0x9000}, {0xF0C0,0x90C0}, {0xFF00,0x0400},
	{0xF100,0x5100}, {0xF130,0x9100}, {0xFFF8,0x4840}, {0xFFC0,0x4AC0},
	{0xFFF0,0x4E40}, {0xFFFF,0x4E76}, {0xFF00,0x4A00}, {0xFFF8,0x4E58}
};

const char bra_tab[][4] = 
{
	"BRA",	"BSR",	"BHI",	"BLS",
	"BCC",	"BCS",	"BNE",	"BEQ",
	"BVC",	"BVS",	"BPL",	"BMI",
	"BGE",	"BLT",	"BGT",	"BLE"
};
const char scc_tab[][4] = 
{
	"ST",	"SF",	"SHI",	"SLS",
	"SCC",	"SCS",	"SNE",	"SEQ",
	"SVC",	"SVS",	"SPL",	"SMI",
	"SGE",	"SLT",	"SGT",	"SLE"
};
const char size_arr[3] = { 'B','W','L' };

//****************************************************************************
// ST Debugger Class
//****************************************************************************

// Ctor / Dtor
STDebugger::STDebugger()
{
	LoadBuffer = nullptr;
}

STDebugger::~STDebugger()
{
	if (LoadBuffer)
	{
		delete[] LoadBuffer;
		LoadBuffer = nullptr;
	}
}

// Init
void STDebugger::Init(void* formPtr)
{
	FormWindow = formPtr;
	SetupRegisters();
	DebugMemoryData();
//	LoadMemory();
	SetupMemory();

	GetComPortsAvailable();
	ReadIniFile();

	ReadBuffer = new u8[MEMORY_BUFFER_SIZE];
	memset(ReadBuffer, 0, MEMORY_BUFFER_SIZE);
}

// Shutdown
void STDebugger::Shutdown()
{
	WriteIniFile();
	ShutdownThreads();

	// cleanup regs
	for (s32 i = 0; i < DataRegisters.Count(); i++)
	{
		delete DataRegisters[i];
	}
	DataRegisters.Reset();

	for (s32 i = 0; i < AddressRegisters.Count(); i++)
	{
		delete AddressRegisters[i];
	}
	AddressRegisters.Reset();
	if (PC)
	{
		delete PC;
		PC = nullptr;
	}

	if (SR)
	{
		delete SR;
		SR = nullptr;
	}

	if (SSP)
	{
		delete SSP;
		SSP = nullptr;
	}

	// cleanup opcodes
	for (s32 i = 0; i < Opcodes.Count(); i++)
	{
		delete Opcodes[i];
	}
	Opcodes.Reset();

	// cleanup ports
	for (s32 i = 0; i < ComPorts.Count(); i++)
	{
		delete ComPorts[i];
	}
	ComPorts.Reset();

	if (ReadBuffer)
	{
		delete[] ReadBuffer;
	}
}

// read ini file
void STDebugger::ReadIniFile()
{
	char str[100];
	long n;

	n = ini_gets("Serial Port", "Port", "COM1", str, sizearray(str), inifile);
	ComPortName = str;

	n = ini_getl("Serial Port", "Baud", 19200, inifile);
	BaudRate = n;
}

// write ini file
void STDebugger::WriteIniFile()
{
	long n;

	n = ini_puts("Serial Port", "Port", ComPortName.GetPtr(), inifile);
	n = ini_putl("Serial Port", "Baud", BaudRate, inifile);
}

// Connect to target
void STDebugger::ConnectToTarget()
{
	mString logString;

	if (SerialPortHandle != INVALID_HANDLE_VALUE)
	{
		// need to disconnect first, ignoring
		logString.Set("Serial port '%s' already open, disconnect first then try again..", ComPortName.GetPtr());
		OutputToLog(logString);
		return;
	}

	mString FullPortName = "\\\\.\\";
	FullPortName += ComPortName;

	SerialPortHandle = CreateFileA(FullPortName.GetPtr(),
		GENERIC_READ | GENERIC_WRITE,	// Read/Write
		0,								// No Sharing
		NULL,							// No Security
		OPEN_EXISTING,					// Open existing port only
		0,								// Non Overlapped I/O
		NULL);							// Null for Comm Devices

	if (SerialPortHandle == INVALID_HANDLE_VALUE)
	{
		logString.Set("Failed to open Serial port '%s'!", ComPortName.GetPtr());
		OutputToLog(logString);
		return;
	}
	
	logString.Set("Serial port '%s' opened successfully!", ComPortName.GetPtr());
	OutputToLog(logString);
	SetSerialConfig();
	CreateTickThread();

	SendCmd(DEBUGGER_CMD_CONNECT);
}

// Set Serial Port baud rate etc
bool STDebugger::SetSerialConfig()
{
	mString logString;

	if (SerialPortHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	bool	fSuccess = false;
	DCB		dcb;

	//  Initialize the DCB structure.
	SecureZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	//  Build on the current configuration by first retrieving all current
	//  settings.
	fSuccess = GetCommState(SerialPortHandle, &dcb);

	if (!fSuccess)
	{
		logString.Set("Failed to get Serial port comm config for '%s'", ComPortName.GetPtr());
		OutputToLog(logString);
		return false;
	}

	//  Fill in some DCB values and set the com state: 
	//  57,600 bps, 8 data bits, no parity, and 1 stop bit.
	dcb.BaudRate = BaudRate;		//  baud rate
	dcb.ByteSize = 8;				//  data size, xmit and rcv
	dcb.Parity = NOPARITY;			//  parity bit
	dcb.StopBits = ONESTOPBIT;		//  stop bit

	fSuccess = SetCommState(SerialPortHandle, &dcb);
	if (!fSuccess)
	{
		logString.Set("Failed to set Serial port comm config for '%s'", ComPortName.GetPtr());
		OutputToLog(logString);
		return false;
	}

	// TODO
	COMMTIMEOUTS cto;
	GetCommTimeouts(SerialPortHandle, &cto);
	// Set the new timeouts
//	cto.ReadIntervalTimeout = MAXDWORD;
//	cto.ReadTotalTimeoutConstant = 0;
//	cto.ReadTotalTimeoutMultiplier = 0;
//	SetCommTimeouts(SerialPortHandle, &cto);

	logString.Set("Set config for Serial port '%s', Baud Rate: %d", ComPortName.GetPtr(), BaudRate);
	OutputToLog(logString);

	return fSuccess;
}

// Disconnect from target
void STDebugger::DisconnectFromTarget()
{
	if (SerialPortHandle == INVALID_HANDLE_VALUE)
	{
		// not connected, ignore
		OutputToLog(mString("Target not connected!"));
		return;
	}

	SendCmd(DEBUGGER_CMD_DISCONNECT);
}

// Disconnect from target complete
void STDebugger::DisconnectFromTargetComplete()
{
	Sleep(100);

	ShutdownThreads();

	if (SerialPortHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(SerialPortHandle);
		OutputToLog(mString("Serial port closed successfully!"));
	}
	SerialPortHandle = INVALID_HANDLE_VALUE;
}

// send commands to serial port
void STDebugger::SendCmd(u8 Cmd, u32 MemoryAddress, u32 NumBytes)
{
	mString logString;

	u8 packetBuffer[MEMORY_BUFFER_SIZE] = { 0 };
	u32* packetData = (u32*)(packetBuffer + 4);

	packetBuffer[0] = Cmd;		// set cmd

	// wait here if a send is already in progress
	// we may want to just ignore any commands that happen 
	if (SendCmdInProgress)
	{
		Sleep(1);
	}

	switch (Cmd)
	{
	// on host
	case DEBUGGER_CMD_STEP:
	case DEBUGGER_CMD_RUN:
	case DEBUGGER_CMD_STOP:
	case DEBUGGER_CMD_CONNECT:
	{
		logString.Set("Attempting to connect to target on '%s'...", ComPortName.GetPtr());
		OutputToLog(logString);
		SetCmdInProgress(Cmd);
		*packetData++ = BaudRate;				// send baud rate
		SendPacket(packetBuffer, 4 + 4);
	}
	break;

	case DEBUGGER_CMD_DISCONNECT:
	{
		logString.Set("Attempting to disconnect from target on '%s'...", ComPortName.GetPtr());
		OutputToLog(logString);
		SetCmdInProgress(Cmd);
		SendPacket(packetBuffer, 4);
	}
	break;

	case DEBUGGER_CMD_REQUEST_REGISTERS:
		logString.Set("Attempting to get registers from target on '%s'...", ComPortName.GetPtr());
		OutputToLog(logString);
		SetCmdInProgress(Cmd);
		SendPacket(packetBuffer, 4);
		break;

	case DEBUGGER_CMD_REQUEST_MEMORY:
		logString.Set("Attempting to get memory from target on '%s'...", ComPortName.GetPtr());
		OutputToLog(logString);
		SetCmdInProgress(Cmd);
		*packetData++ = MemoryAddress;
		*packetData = NumBytes;
		SendPacket(packetBuffer, 4 + 4 + 4);
		break;

	default:
		SendCmdInProgress = false;
		break;
	}
}

// send packet to serial port
bool STDebugger::SendPacket(u8* packet, u32 NumBytes)
{
	bool	result = false;
	u32		NumBytesWritten = 0;
	DWORD	errCode = 0;

	if (NumBytes == 0)
	{
		NumBytes = strlen((char*)packet);
	}
	else
	{

	}

	result = WriteFile(SerialPortHandle, packet, NumBytes, &NumBytesWritten, NULL);
	if (result)
	{
//		OutputDebugString(L"Sent packet successfully..\n");
//		OutputToLog(mString("Sent packet successfully.."));
	}
	else
	{
		OutputDebugString(L"Packet failed to send..\n");
//		OutputToLog(mString("Packet failed to send"));
	}

	return result;
}

// update registers
void STDebugger::RequestRegisters()
{
	SendCmd(DEBUGGER_CMD_REQUEST_REGISTERS);
}

// get memory
void STDebugger::RequestMemory()
{
	char* ad = (char*)this;
	SendCmd(DEBUGGER_CMD_REQUEST_MEMORY, (u32)ad, 1024);
}

// Get COM ports available
void STDebugger::GetComPortsAvailable()
{
	TCHAR lpTargetPath[1024];
	WCHAR* deviceNameW = new WCHAR[32];

	for (u32 i = 0; i < 255; i++) // checking ports from COM0 to COM255
	{
		System::String^ deviceName = "COM" + ConvertIntToString(i);
		ConvertStringToLChar(deviceName, *deviceNameW);

		DWORD numChars = QueryDosDevice(deviceNameW, lpTargetPath, 1024);
		if (numChars > 0)
		{
			ComPort* port = new ComPort();
			port->PortName = ConvertStringToChar(deviceName);

			char buf[1024];
			ConvertWCharToChar(lpTargetPath, buf);
			port->PortDescription = buf;
			ComPorts.Add(port);
		}
	}
}

// debug memory data
void STDebugger::DebugMemoryData()
{
	u8 buf[MEMORY_BUFFER_SIZE];
	for (s32 k = 0; k < MEMORY_BUFFER_SIZE; k++)
	{
		buf[k] = (char)k;
	}
	LoadMemory(buf);
}

// Load memory
void STDebugger::LoadMemory(u8* SrcData)
{
	if (MemoryBuffer)
	{
		delete[] MemoryBuffer;
	}

	MemoryBuffer = new u8[MEMORY_BUFFER_SIZE];
	memset(MemoryBuffer, 0, MEMORY_BUFFER_SIZE);
	memcpy(MemoryBuffer, SrcData, MEMORY_BUFFER_SIZE);
}

// Setup Memory 
void STDebugger::SetupMemory()
{
	MemoryBytesPerLine = MEMORY_WINDOW_BYTES_PER_LINE;
	MemoryBytesPerColumn = MEMORY_WINDOW_BYTES_PER_COLUMN;

	// get form
	System::Runtime::InteropServices::GCHandle ht = System::Runtime::InteropServices::GCHandle::FromIntPtr(System::IntPtr(FormWindow));
	CppCLRWinformsSTDebugger::Form1^ mainWindow = (CppCLRWinformsSTDebugger::Form1^)ht.Target;

	// draw all the registers
	System::Windows::Forms::RichTextBox^ memoryWindow = mainWindow->GetMemoryWindow();

	if (memoryWindow != nullptr)
	{
		memoryWindow->Clear();
		System::String^ MemoryString;
		System::String^ AsciiString;

		u32 CurrentMemoryAddress = MemoryStartAddress;
		u8* CurrentMemoryBuffer = &MemoryBuffer[CurrentMemoryAddress];

		// number of lines 
		s32 numLines = 32;

		// create a string to show the memory
		for (s32 i = 0; i < numLines; i++)
		{
			// display the address first
			char AddressString[12];
			sprintf(AddressString, "0x%08d", CurrentMemoryAddress);
			MemoryString += ConvertCharToString(AddressString) + "\t";

			AsciiString = "";

			// loop over columns
			for (s32 columns = 0; columns < MEMORY_WINDOW_COLUMNS; columns++)
			{
				// now show the bytes
				char MemDword[MEMORY_WINDOW_BYTES_PER_COLUMN] = { 0 };
				for (u32 bytes = 0; bytes < MemoryBytesPerColumn; bytes++)
				{
					char mv = *CurrentMemoryBuffer++;
					MemDword[bytes] = mv;
					if (mv > 32 && mv < 127)
					{
						AsciiString += ConvertIntToAscii(mv);
					}
					else
					{
						AsciiString += ".";
					}
				}

				char MemValue1[8] = { 0 };
				char MemValue2[8] = { 0 };
				char MemValue3[8] = { 0 };
				char MemValue4[8] = { 0 };
				switch (MemoryBytesPerColumn)
				{
				case 4:
					{
						u8 c = MemDword[0];
						sprintf(MemValue1, "%02x", c);
						MemoryString += ConvertCharToString(MemValue1);
						c = MemDword[1];
						sprintf(MemValue2, "%02x", c);
						MemoryString += ConvertCharToString(MemValue2);
						c = MemDword[2];
						sprintf(MemValue3, "%02x", c);
						MemoryString += ConvertCharToString(MemValue3);
						c = MemDword[3];
						sprintf(MemValue4, "%02x", c);
						MemoryString += ConvertCharToString(MemValue4);
					}
					break;
				case 2:
					MemoryString += ConvertIntToString(MemDword[0]);
					MemoryString += ConvertIntToString(MemDword[1]);
					break;
				case 1:
				default:
					MemoryString += ConvertIntToString(MemDword[0]);
					break;
				}

				MemoryString += "  ";
			}

			MemoryString += "\t";
			MemoryString += AsciiString;
			MemoryString += "\r\n";

			// increment for next line
			CurrentMemoryAddress += MemoryBytesPerLine;
		}
		memoryWindow->Text = MemoryString;
	}
}

// Setup Registers
void STDebugger::SetupRegisters()
{
	Register* reg = nullptr;

	// Data registers
	for (u32 i = 0; i < 8; i++)
	{
		char RegString[10];
		sprintf(RegString, "D%d", i);
		reg = new Register(0x00000000, RegString, "");
		DataRegisters.Add(reg);
	}

	// Address registers
	for (u32 i = 0; i < 8; i++)
	{
		char RegString[10];
		sprintf(RegString, "A%d", i);
		reg = new Register(0x00000000, RegString, "");
		AddressRegisters.Add(reg);
	}

	// PC
	PC = new Register(0x00000000, "PC", "");

	// Status
	SR = new Register(0x00000000, "SR", "");

	// SSP
	SSP = new Register(0x00000000, "SSP", "");
	UpdateRegisters();
}

// udpate registers display
void STDebugger::UpdateRegisters()
{
	// get form
	System::Runtime::InteropServices::GCHandle ht = System::Runtime::InteropServices::GCHandle::FromIntPtr(System::IntPtr(FormWindow));
	CppCLRWinformsSTDebugger::Form1^ mainWindow = (CppCLRWinformsSTDebugger::Form1^)ht.Target;

	// draw all the registers
	System::Windows::Forms::RichTextBox^ registerWindow = mainWindow->GetRegisterWindow();
	if (registerWindow != nullptr)
	{
		registerWindow->Clear();

		System::String^ RegString;

		DynArray<Register*>	Regs;
		for (s32 i = 0; i < DataRegisters.Count(); i++)
		{
			Regs.Add(DataRegisters[i]);
		}
		for (s32 i = 0; i < AddressRegisters.Count(); i++)
		{
			Regs.Add(AddressRegisters[i]);
		}

		// Data registers
		for (s32 i = 0; i < DataRegisters.Count(); i++)
		{
			RegString += ConvertCharToString(Regs[i]->Label.GetPtr()) + ": " + ConvertCharToString(Regs[i]->ValueString.GetPtr()) + "\t  " +
						 ConvertCharToString(Regs[i + DataRegisters.Count()]->Label.GetPtr()) + ": " + ConvertCharToString(Regs[i + DataRegisters.Count()]->ValueString.GetPtr());

			RegString += "\r\n";
		}

		RegString += "\r\n";
		RegString += ConvertCharToString(PC->Label.GetPtr()) + ":  " + ConvertCharToString(PC->ValueString.GetPtr()) + "\r\n";
		RegString += ConvertCharToString(SR->Label.GetPtr()) + ":  " + ConvertCharToString(SR->ValueString.GetPtr()) + "\r\n";
		RegString += ConvertCharToString(SSP->Label.GetPtr()) + ": " + ConvertCharToString(SSP->ValueString.GetPtr()) + "\r\n";

		registerWindow->Text = RegString;
	}
}

// set starting memory address for memory window
void STDebugger::SetStartingMemoryAddress(u32 Address)
{
	MemoryStartAddress = Address;
	SetupMemory();
}

// Load Executable
void STDebugger::LoadExecutable(LPCWSTR Filename)
{
	// unload existing?
	if (LoadBuffer)
	{
		delete[] LoadBuffer;
		LoadBuffer = nullptr;
	}

	// open / read the file into memory
	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		LPDWORD highFileSize = 0;
		LPDWORD bytesRead = 0;
		DWORD fileSize = GetFileSize(hFile, highFileSize);
		if (fileSize != 0)
		{
			LoadBuffer = new u8[fileSize + 2];
			memset(LoadBuffer, 0, fileSize + 2);
			BOOL result = ReadFile(hFile, LoadBuffer, fileSize, bytesRead, NULL);
			if (!result)
			{
				OutputDebugString(L"Read file failed..\n");
				delete[] LoadBuffer;
				LoadBuffer = nullptr;
			}
			else // success
			{
				LoadBufferSize = fileSize;
				DisassembleCode();
				OutputDebugString(L"Read file succeeded..\n");
			}
		}
		else
		{
			OutputDebugString(L"File size == 0..\n");
		}
	}
	else
	{
		OutputDebugString(L"Failed to open file for reading..\n");
	}
}

// Clears the windows and re draws the code
void STDebugger::DisassembleCode()
{
	if (!LoadBuffer || LoadBufferSize == 0)
	{
		return;
	}

	mString AsmText;
	mString DisassemblyText;

	System::Runtime::InteropServices::GCHandle ht = System::Runtime::InteropServices::GCHandle::FromIntPtr(System::IntPtr(FormWindow));
	CppCLRWinformsSTDebugger::Form1^ mainWindow = (CppCLRWinformsSTDebugger::Form1^)ht.Target;

	System::Windows::Forms::RichTextBox^ codeWindow = mainWindow->GetAssemblyWindow();
	codeWindow->Clear();

	Disasm_SetCPUType(currentCPUType, 0, false);

	u32 sizeOfHeader = sizeof(ProgramHeader);
	u32 codeSize = LoadBufferSize - sizeOfHeader;
	u32 startOfCode = (u32)(LoadBuffer + sizeOfHeader);
	u32 endOfCode = startOfCode + codeSize;
	m68k_disasm(AsmText, DisassemblyText, startOfCode, endOfCode, 0, 100);

	codeWindow->Text = ConvertCharToString(AsmText.GetPtr());
}

// Clear mainWindow reference
void STDebugger::ClearMainWindowPreferencesReference()
{
	System::Runtime::InteropServices::GCHandle ht = System::Runtime::InteropServices::GCHandle::FromIntPtr(System::IntPtr(FormWindow));
	CppCLRWinformsSTDebugger::Form1^ mainWindow = (CppCLRWinformsSTDebugger::Form1^)ht.Target;

	mainWindow->preferencesWindow = nullptr;
}

//////////////////////////////////////////////////////////////
void STDebugger::OutputToLog(mString Text)
{
	mString* t = new mString(Text);
	LogQueue.Add(t);
}

//////////////////////////////////////////////////////////////
void STDebugger::UpdateLog()
{
	if (LogQueue.Count() == 0)
		return;

	System::Runtime::InteropServices::GCHandle ht = System::Runtime::InteropServices::GCHandle::FromIntPtr(System::IntPtr(FormWindow));
	CppCLRWinformsSTDebugger::Form1^ mainWindow = (CppCLRWinformsSTDebugger::Form1^)ht.Target;

	if (mainWindow != nullptr)
	{
		System::Windows::Forms::RichTextBox^ logWindow = mainWindow->GetLogWindow();
		if (logWindow != nullptr)
		{
			for (s32 i = 0; i < LogQueue.Count(); i++)
			{
				logWindow->Text += "\n" + ConvertCharToString(LogQueue[i]->GetPtr());
			}
		}
		logWindow->Select(logWindow->Text->Length, 0);
	}
	LogQueue.RemoveAll();
}

//////////////////////////////////////////////////////////////
void STDebugger::RefreshWindows()
{
	UpdateLog();

	if (UpdateWindowMask & UPDATE_REGISTERS_WINDOW)
	{
		UpdateRegisters();
		UpdateWindowMask = UpdateWindowMask & ~UPDATE_REGISTERS_WINDOW;
	}
	if (UpdateWindowMask & UPDATE_MEMORY_WINDOW)
	{
		SetupMemory();
		UpdateWindowMask = UpdateWindowMask & ~UPDATE_MEMORY_WINDOW;
	}
}

//////////////////////////////////////////////////////////////
// SERIAL IO
//////////////////////////////////////////////////////////////
s32 STDebugger::CreateTickThread()
{
	DWORD	dwThrdParam = 1;
	BOOL	result;
	s32		handle = 0;
	TickFunctionExit = false;

	// create a new thread
	TickThreadHandle = _beginthreadex(NULL, 65536, &STDebugger::TickThread, this, 0 /*CREATE_SUSPENDED*/, (unsigned int*)&TickThreadID);

	if (!TickThreadHandle)
		return -1;			// bad handle

	// set the priority
	result = SetThreadPriority((HANDLE)TickThreadHandle, THREAD_PRIORITY_NORMAL);
	if (!result)
		return -1;

	result = ResumeThread((HANDLE)TickThreadHandle);
	if (result == -1)
		return -1;

	return (s32)TickThreadHandle;
}

// Serial IO input / output


// tick function
unsigned int __stdcall STDebugger::TickThread(void* lpParameter)
{
	mString			logString;
	STDebugger*		std = (STDebugger*)lpParameter;
	u32				numBytesRead = 0;
	u32				numBytesReceivedTotal = 0;
	u8				cmd = DEBUGGER_CMD_NONE;
	u8*				buffer = std->GetReadBuffer();
	u8*				dstBuf = buffer;
	u8				ringBuffer[32];

	HANDLE handle = std->GetSerialPortHandle();

	while (!std->TickFunctionExit)
	{
		bool result = ReadFile(handle, ringBuffer, 32, &numBytesRead, NULL);

		if (result && numBytesRead != 0 && !std->GetReceiveInProgress())
		{
			std->SetReceiveInProgress(true);
			cmd = ringBuffer[0];
			numBytesReceivedTotal = numBytesRead;
			memcpy(dstBuf, ringBuffer, 32);
			dstBuf += numBytesRead;
		}
		else if (std->GetReceiveInProgress() && result && numBytesRead != 0)
		{
			memcpy(dstBuf, ringBuffer, 32);
			dstBuf += numBytesRead;
			numBytesReceivedTotal += numBytesRead;
		}
		else if (result && std->GetReceiveInProgress() && numBytesRead == 0)
		{
			std->SetReceiveInProgress(false);
			std->ProcessCommand(cmd, buffer);
			dstBuf = buffer;
			memset(buffer, 0, MEMORY_BUFFER_SIZE);
			logString.Set("Received %d bytes from target..", numBytesReceivedTotal);
			std->OutputToLog(logString);
			numBytesReceivedTotal = 0;
		}

		if (std->GetSendInProgress())
		{
			std->SetSendCmdTimeout(std->GetSendCmdTimeout() - 1);

			if (std->GetSendCmdTimeout() <= 0)
			{
				std->SetSendInProgress(false);
				logString.Set("Serial port cmd timed out on '%s'! Cancelling command..", std->GetComPortName());
				std->OutputToLog(logString);

				if (std->GetLastCommand() == DEBUGGER_CMD_CONNECT || std->GetLastCommand() == DEBUGGER_CMD_DISCONNECT)
				{
					std->DisconnectFromTargetComplete();
				}
			}
		}

		Sleep(1);
	}

	DWORD	ExitCode = 0;
	GetExitCodeThread((HANDLE)std->TickThreadHandle, &ExitCode);
	_endthreadex(ExitCode);
	return 0;
}

void STDebugger::SetCmdInProgress(u8 Cmd)
{
	LastCommand = Cmd;
	SendCmdInProgress = true;
//	SendCmdTimeout = 20 * 5;					// time in seconds
	SendCmdTimeout = 1000000000;
}

// process command from serial port
void STDebugger::ProcessCommand(u8 cmd, u8* packet)
{
	u32* packetData = (u32*)packet;

	mString output;

	switch (cmd)
	{
		// on the host
	case DEBUGGER_TARGET_RESPONSE_STEP:
	{
		char* response = (char*)&packet[4];
		// update PC if response we ok
		SendCmdInProgress = false;
	}
	break;

	case DEBUGGER_TARGET_RESPONSE_STOP:
	{
		char* response = (char*)&packet[4];
		// did we stop (set PC)
		SendCmdInProgress = false;
	}
	break;

	case DEBUGGER_TARGET_RESPONSE_RUN:
	{
		char* response = (char*)&packet[4];
		// did we run? set debugger to active
		SendCmdInProgress = false;
	}
	break;

	case DEBUGGER_TARGET_RESPONSE_CONNECTED:
	{
		char* targetInfo = (char*)&packet[4];
		output = "Connected to Target: ";
		output += targetInfo;
		output += "\n";
		OutputToLog(mString(output));
		output.ToWide();
		OutputDebugString((LPCWSTR)output.GetPtr());
		SendCmdInProgress = false;
	}
	break;

	case DEBUGGER_TARGET_RESPONSE_DISCONNECTED:
	{
		char* targetInfo = (char*)&packet[4];
		output += targetInfo;
		output += "\n";
		OutputToLog(mString(output));
		output.ToWide();
		OutputDebugString((LPCWSTR)output.GetPtr());
		SendCmdInProgress = false;
		DisconnectFromTargetComplete();
	}
		break;

	case DEBUGGER_TARGET_RESPONSE_REGISTERS:
	{
		OutputDebugString(L"Updated Registers from Target");

		// udpate the debugger registers
		u32* regBuf = (u32*)&packet[4];
		for (s32 i = 0; i < DataRegisters.Count(); i++)
		{
			Register* reg = DataRegisters[i];
			reg->SetValue(*regBuf++);
		}
		for (s32 i = 0; i < AddressRegisters.Count(); i++)
		{
			Register* reg = AddressRegisters[i];
			reg->SetValue(*regBuf++);
		}
		PC->Value = *regBuf++;
		SR->Value = *regBuf++;
		SSP->Value = *regBuf++;

		UpdateWindowMask |= UPDATE_REGISTERS_WINDOW;
		SendCmdInProgress = false;
	}
	break;

	case DEBUGGER_TARGET_RESPONSE_MEMORY:
	{
		char* memoryData = (char*)&packet[4];

		// copy memory to buffer
		memcpy(MemoryBuffer, memoryData, 4096);

		OutputToLog(mString("Got memory block from Target"));
		UpdateWindowMask |= UPDATE_MEMORY_WINDOW;
		SendCmdInProgress = false;
	}
	break;


	default:
		break;
	}
}

// shutdown threads
void STDebugger::ShutdownThreads()
{
	WaitForSingleObject((HANDLE)TickThreadHandle, 1);
	TickFunctionExit = true;
	WaitForSingleObject((HANDLE)TickThreadHandle, 1);
	CloseHandle((HANDLE)TickThreadHandle);

	TickThreadHandle = 0;
}