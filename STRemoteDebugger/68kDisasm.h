/***
 *	68k disassembler, written 2010 by Markus Fritze, www.sarnau.com
 *	
 *	This file is distributed under the GNU Public License, version 2 or at
 *	your option any later version. Read the file gpl.txt for details.
 ***/
#include "llttypes.h"

typedef char uae_char;
typedef unsigned int uae_u32;
typedef unsigned char uae_u8;
typedef unsigned short uae_u16;

void m68k_disasm(mString& AsmOutput, mString& DisAsmOutput, u32 addr, u32 endAddr, u32* nextpc, int cnt, u32& LineCount);
void Disasm_SetCPUType(int CPU, int FPU, bool bMMU);