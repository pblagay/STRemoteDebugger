//******************************************************//
// Layer: Common										//
//														//
// 														//
// string.h												//
//														//
// string manipulation									//
//														//
// Copyright (C) 2013 Biotic Software LLC.			//
//******************************************************//

#ifndef _LLSTRING_H
#define _LLSTRING_H

#include "llttypes.h"

namespace String
{
	// upper / lower
	inline char*	ToUpper(char* Src);
	inline char*	ToLower(char* Src);

	// unicode
	inline void		UnicodeToAscii(const u16* Uni, char* Ascii);
	inline void		AsciiToUnicode(const char* Ascii, u16* Uni);

	// shift JIS
	inline	void	ShiftJIS_String(char* Dst, const char* Src);
	inline	u16		ShiftJIS_Char(char Char);

	// len
	inline	s32		Strlen(const char* Str);
	inline	s32		Strlen(const u16* Str);

	// comparisons
	inline	char*	Strstr(const char* MainStr, const char* SubStr );
	inline  char*	Strchr(const char* Str, s32 C);
	inline	char*	Strrchr(const char* Str, s32 C);
	inline	s32		Strcmp(const char* Src0, const char* Src1);
	inline	s32		Stricmp(const char* Src0, const char* Src1);
	inline	s32		Strncmp(const char* Src0, const char* Src1, s32 Count);
	inline  s32		Strcmp(const u16* Src0, const u16* Src1);

	// strcpy funcs
	inline	char*	Strcpy(char* Dst, const char* Src);
	inline  u16*	Strcpy(u16* Dst, const u16* Src);
	inline	char*	Strncpy(char* Dst, const char* Src, s32 Count);
	inline	u32		Strcpy_len(char* dst, const char* src);		// returns length of copied string
	inline	char*	Strcat(char* Dst, const char* Src);
	inline	char*	Strncat(char* Front, const char* Back, s32 Count);

	// sprintf & helpers

	// helpers
	inline	char*	Itoa(s32 Val, char* Str);
	inline	void	Reverse(char* Str);

	// printfs
	s32		SprintfBuffInc(char** Buff, const char* fmt, ...);
	s32		FprintfBuffInc(char** Buff, const char* fmt, ...);

	// path management
	inline	u32		StripExtension(const char* SrcFname, char* DstFname);
	inline	u32		StripPath(const char* SrcPath, char* DstPath, bool StripExt = false);
	inline	void	GetPath(const char* SrcPath, char* DstPath, bool stripDriveLetter = false);
	inline	bool	HasExtension(const char* Filename);
	inline	bool	GetExtension(const char* Filename, char* Extension);
	inline	u32		GetCurrentSubDir(const char* SrcFname, char* DstFname);
	inline  void	SlashConvertFromBackToFront(const char* SrcFilename, char* DstFilename, bool toUpper = false);
	inline	void	SlashConvertFromFrontToBack(const char* SrcFilename, char* DstFilename, bool toUpper = false);
	inline	void	UnicodePathToAscii(const u16* SrcPath, char* DstFname, bool ToLower = false, bool StripPath = false, bool StripExt = false);
	inline  u32		AddTrailingBackslash(char* SrcFname, const char* separator);
}

// inline funcs
#include "cString.hpp"

#endif // _LLSTRING_H

