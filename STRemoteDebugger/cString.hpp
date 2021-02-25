//******************************************************//
// Layer: Common										//
//														//
// 														//
// string.hpp											//
//														//
// string manipulation									//
//														//
// Copyright (C) 2013 Biotic Software LLC.			//
//******************************************************//

// I need sprintf and va_arg
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include "llttypes.h"

/////////////////////////////////////////////////////////////
void String::UnicodeToAscii(const u16* Uni, char* Ascii)
{
	while (Uni[0] != 0)
	{
		Ascii[0] = (char)Uni[0];
		Ascii++; Uni++;
	}
	Ascii[0] = 0;
}

/////////////////////////////////////////////////////////////
void String::AsciiToUnicode(const char* Ascii, u16* Uni)
{
	while (Ascii[0] != 0)
	{
		Uni[0] = (u16)Ascii[0];
		Ascii++; Uni++;
	}
	Uni[0] = 0;
}

/////////////////////////////////////////////////////////////
// Set String to Upper
char* String::ToUpper(char* Src)
{
	char* s = Src;

	if (s == NULL)
		return NULL;

	assert(Src);

	while (*s != 0)
	{
		if ( ( *s >= 'a') && (*s <= 'z') )
			*s -= 32;
		s++;
	}
	return Src;
}

/////////////////////////////////////////////////////////////
// Set String to Lower
char* String::ToLower(char* Src)
{
	char* s = Src;

	if (s == NULL)
		return NULL;

	assert(Src);

	while (*s != 0)
	{
		if ( (*s >= 'A') && (*s <= 'Z') )
			*s += 32;
		s++;
	}
	return Src;
}

/////////////////////////////////////////////////////////////
// ShiftJIS String

void String::ShiftJIS_String(char* Dst, const char* Src)
{
	s32	i = 0;
	s32 len = 0;

	//set the title name in Shift-JIS char format...
	len = String::Strlen(Src);

	for(; i < len; ++i) 
		*(u16*)&Dst[i*2] = ShiftJIS_Char(Src[i]);

	*(u16*)&Dst[i*2] = 0x0000; 
}

/////////////////////////////////////////////////////////////
// ShiftJIS Char

u16 String::ShiftJIS_Char(char Char)
{
	char	c = Char;
	u16		jisChar = 0;

	switch(c) 
	{
		case '\0':
			return 0x0000;

		case ' ':
			return 0x4081;

		case '.':
			return 0x4481;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		case 'G': case 'H': case 'I': case 'J': case 'K':
		case 'L': case 'M': case 'N': case 'O': case 'P':
		case 'Q': case 'R': case 'S': case 'T': case 'U':
		case 'V': case 'W': case 'X': case 'Y': case 'Z':
			jisChar = (u16)((((u16)Char + 31) << 8) | (0x82));
            return jisChar;

		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		case 'g': case 'h': case 'i': case 'j': case 'k':
		case 'l': case 'm': case 'n': case 'o': case 'p':
		case 'q': case 'r': case 's': case 't': case 'u':
		case 'v': case 'w': case 'x': case 'y': case 'z':
			jisChar = (u16)((((u16)Char + 32) << 8) | (0x82));
            return jisChar;

		default: return 0x0000;
	}
}

/////////////////////////////////////////////////////////////
// Strlen
s32 String::Strlen(const char* Str)
{
	const char *eos = Str;
	
	assert(Str);

	while( *eos++ )
	{
	}
	return( (s32)(eos - Str - 1) );
}

/////////////////////////////////////////////////////////////
// Strlen U16
s32 String::Strlen(const u16* Str)
{
	const u16 *eos = Str;
	
	assert(Str);

	while( *eos++ )
	{
	}
	return( (s32)(eos - Str - 1) );
}

/////////////////////////////////////////////////////////////
// String copy
char* String::Strcpy(char* Dst, const char* Src)
{	
	if (Src == NULL || Dst == NULL)
		return NULL;

	char* cp = Dst;
	
	while( (*cp++ = *Src++) ) 
	{
	}
	
	return(Dst);
}

/////////////////////////////////////////////////////////////
// String copy
u16* String::Strcpy(u16* Dst, const u16* Src)
{	
	if (Src == NULL || Dst == NULL)
		return NULL;

	u16* cp = Dst;

	while( (*cp++ = *Src++) ) 
	{
	}

	return(Dst);
}


/////////////////////////////////////////////////////////////
// String copy (n)
char* String::Strncpy(char* Dst, const char* Src, s32 Count)
{	
	char* start = Dst;

	assert( Dst );
	assert( Src );
	assert( (Count < 1024) && (Count >= 0) );

	while (Count && (*Dst++ = *Src++))
		Count--;

	if (Count)
		while (--Count)
			*Dst++ = '\0';

	return(start);
}

/////////////////////////////////////////////////////////////
// SubString Compare
char* String::Strstr(const char* MainStr, const char* SubStr )
{
	char* str;	
	char* substr;

	assert( MainStr );
	assert( SubStr  );

	str = (char*)MainStr;

	while( *str )
	{	
		while( *str && (*str != *SubStr) ) str++;
		for (substr=(char*)SubStr; *substr && (*str == *substr); str++, substr++ )
		{
		}
		
		if ( *substr == 0 ) 
			return str;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////
// String search char (reverse)
char* String::Strrchr(const char* Str, s32 C)
{
	char* start = (char*)Str;

    // Find end of string.
	while( *Str++ )
        ;

	// Search from back towards front.
	while( (--Str != start) && (*Str != (char)C) )
        ;

	// Did we find it?
	if( *Str == (char)C )
		return( (char*)Str );	
	else
		return( NULL );
}

/////////////////////////////////////////////////////////////
// String search char
char* String::Strchr(const char* Str, s32 C)
{
	char* end = (char*)Str;

	// Find end of string.
	while( *end++ )
		;

	// Search from back towards front.
	while( (Str++ != end) && (*Str != (char)C) )
		;

	// Did we find it?
	if( *Str == (char)C )
		return( (char*)Str );	
	else
		return( NULL );
}

/////////////////////////////////////////////////////////////
// String Compare
s32 String::Strcmp(const char* Src0, const char* Src1)
{
	s32		ret = 0; 

	if (Src0 == NULL || Src1 == NULL)
		return 0;

	while( ! (ret = *(u8 *)Src0 - *(u8 *)Src1) && *Src1 )
        ++Src0, ++Src1;
	
	return(ret);
}

/////////////////////////////////////////////////////////////
// String Compare (n)
s32 String::Strncmp(const char* Src0, const char* Src1, s32 Count)
{
	assert(Src0);
	assert(Src1);
	assert((Count>0) && (Count<1024));

	if (!Count)
		return(0);

	while (--Count && *Src0 && *Src0 == *Src1)
	{
		Src0++;
		Src1++;
	}
	return(s32)( *(u8 *)Src0 - *(u8 *)Src1 );
}

/////////////////////////////////////////////////////////////
// String Compare - no case
s32 String::Stricmp(const char* Src0, const char* Src1)
{
	s32		f, l;
	
	assert(Src0);
	assert(Src1);

	do
	{
		if ( ((f = (u8)(*(Src1++))) >= 'A') && (f <= 'Z') )
			f -= ('A' - 'a');

		if ( ((l = (u8)(*(Src0++))) >= 'A') && (l <= 'Z') )
			l -= ('A' - 'a');

	} while ( f && (f == l) );

	return(l - f);
}

/////////////////////////////////////////////////////////////
// String Compare
s32 String::Strcmp(const u16* Src0, const u16* Src1)
{
	assert(Src0);
	assert(Src1);

	while (*Src0 == *Src1++)
		if (*Src0++ == 0)
			return (0);

	return (*(const u16 *)Src0 - *(const u16 *)--Src1);
}

/////////////////////////////////////////////////////////////
// strcpy with len return
u32 String::Strcpy_len(char* dst, const char* src)
{
	u32		i = 0;
    while ((*dst++ = *src++))
		i++;

	return i;
}

/////////////////////////////////////////////////////////////
// strcat
char* String::Strcat(char* Dst, const char* Src)
{	
	char* cp = Dst;
	assert(Dst);
	assert(Src);

	while( *cp ) cp++;
	while( (*cp++ = *Src++) )
        ;
	return( Dst );
}

/////////////////////////////////////////////////////////////
// strcat (n)
char* String::Strncat(char* Front, const char* Back, s32 Count)
{
	char *start = Front;
	assert(Front);
	assert(Back);
	assert((Count > 0) && (Count < 1024));
	
	while (*Front++)
        ;
	Front--;
	while (Count--)
		if (!(*Front++ = *Back++))
			return(start);
	*Front = '\0';
	return(start);
}

/////////////////////////////////////////////////////////////
// Integer to Ascii
char* String::Itoa(s32 Val, char* Str)
{
	u32		i = 0;
	s32		fSign = 0;

	if (Val < 0)
	{
		fSign = 1;
		Val = -Val;
	}

	do 
	{
		Str[i++] = (char)(Val % 10 + '0');
	}while ( ( Val /= 10) > 0);

	if (fSign)
		Str[i++] = '-';

	Str[i] = '\0';
	Reverse(Str);
    return(Str);
}

/////////////////////////////////////////////////////////////
// Reverse
void String::Reverse(char* Str)
{
	u32		i;
	u32		j;
	char	c;

	for ( i = 0, j = Strlen(Str) - 1; i < j; i++, j--)
	{
		c = Str[i];
		Str[i] = Str[j];
		Str[j] = c;
	}
}

/////////////////////////////////////////////////////////////
// Strip Extension
u32 String::StripExtension(const char* SrcFname, char* DstFname)
{
	s32		len = (u32)Strlen(SrcFname);

	if (len == 0)
		return 0;

	while(SrcFname[len] != '.')
	{
		len--;
		if (len < 0)
			return 0;
	}

	Strncpy(DstFname, SrcFname, (s32)len);
	DstFname[len] = 0;
	return len;
}

/////////////////////////////////////////////////////////////
// Add trailing backslash 
// if it doesn't already exist
u32 String::AddTrailingBackslash(char* SrcFname, const char* separator)
{
	s32		len = (u32)Strlen(SrcFname);

	if (len == 0)
		return 0;

	if (SrcFname[len - 1] != '\\' && SrcFname[len - 1] != '/')
		Strcat(SrcFname, separator);

	return len;
}

/////////////////////////////////////////////////////////////
// Get Current Subdirectory
u32 String::GetCurrentSubDir(const char* SrcFname, char* DstFname)
{
	s32		len = (u32)Strlen(SrcFname);
	u32		SubDirCnt = 0;

	// if we have a backslash already at end, skip it
	if (SrcFname[len] == '\\' || SrcFname[len] == '/')
		len --;

	if (len == 0)
		return 0;

	// find previous trailing backslash
	while (SrcFname[len] != '\\' && SrcFname[len] != '/')
	{
		len--;
		if (len < 0)
			return 0;

		SubDirCnt++;
	}
	len++;			// skip leading backslash
	Strncpy(DstFname, &SrcFname[len], SubDirCnt - 1);
	
	DstFname[SubDirCnt - 1] = 0;

	return Strlen(DstFname);
}

/////////////////////////////////////////////////////////////
// Strip Path (optionally remove extension)
u32 String::StripPath(const char* SrcPath, char* DstPath, bool StripExt)
{
	s32		len = (u32)Strlen(SrcPath);

	if (len == 0)
		return 0;

	while(SrcPath[len] != '\\' && SrcPath[len] != '/')
	{
		len--;
		if (len < 0)
		{
			if (StripExt == true)
				String::StripExtension(SrcPath, DstPath);
			else
				Strcpy(DstPath, SrcPath);
			return 0;
		}
	}

	if (StripExt == true)
	{
		char	Temp[512];
		String::StripExtension(SrcPath, Temp);
		Strcpy(DstPath, &Temp[len + 1]);
	}
	else
		Strcpy(DstPath, &SrcPath[len + 1]);

	return len;
}

/////////////////////////////////////////////////////////////
// Get Path
void String::GetPath(const char* SrcPath, char* DstPath, bool stripDriveLetter)
{
	s32		len = (u32)Strlen(SrcPath);

	if (len == 0)
		return;

	while(SrcPath[len] != '\\' && SrcPath[len] != '/')
	{
		len--;
		if (len < 0)
		{
			DstPath[0] = 0;
			return;
		}
	}

	u32 sidx = 0;
	if (stripDriveLetter)
		sidx = 3;

	Strncpy(DstPath, &SrcPath[sidx], len - sidx);
	DstPath[len - sidx] = 0;
}

/////////////////////////////////////////////////////////////
// Has Extension
bool String::HasExtension(const char* FileName)
{
	s32		len = (u32)Strlen(FileName);

	if (len == 0)
		return 0;

	while(FileName[len] != '.')
	{
		len--;
		if (len < 0)
			return false;
	}

	return true;
}

///////////////////////////////////////////////////////////
// Get Extension of a filename
bool String::GetExtension(const char* Filename, char* Extension)
{
	s32		Length;

	// make sure no NULL ptrs..
	if (Filename == NULL || Extension == NULL)
		return false;

	Length = (s32)Strlen(Filename);

	// find the . in filename.. and store of the extension with dot
	while (Length >= 0)
	{
		if (Filename[Length] == '.')
		{
			Strcpy(Extension, &Filename[Length + 1]);
			return true;
		}
		Length--;
	}
	return false;
}

///////////////////////////////////////////////////////////
// Convert Filename from \ to / type path
void String::SlashConvertFromBackToFront(const char* SrcFilename, char* DstFilename, bool toUpper)
{
	assert(SrcFilename != NULL); // "SrcFilename == NULL!");
	assert(DstFilename != NULL); // "DstFilename == NULL!");
	
	u32 SrcCount = 0;
	u32	DstCount = 0;
	
	while (SrcFilename[SrcCount] != 0)
	{
		unsigned char	c = SrcFilename[SrcCount];
		if (c == '\\')
			DstFilename[DstCount] = '/';
		else
			DstFilename[DstCount] = c;
		SrcCount++;
		DstCount++;
	}

	DstFilename[DstCount] = 0;
	if (toUpper)
		ToUpper(DstFilename);
}

///////////////////////////////////////////////////////////
// Convert Filename from / to \ type path
void String::SlashConvertFromFrontToBack(const char* SrcFilename, char* DstFilename, bool toUpper)
{
	assert(SrcFilename != NULL); // "SrcFilename == NULL!");
	assert(DstFilename != NULL); // "DstFilename == NULL!");

	u32 SrcCount = 0;
	u32	DstCount = 0;

	while (SrcFilename[SrcCount] != 0)
	{
		unsigned char	c = SrcFilename[SrcCount];
		if (c == '/')
			DstFilename[DstCount] = '\\';
		else
			DstFilename[DstCount] = c;
		SrcCount++;
		DstCount++;
	}

	DstFilename[DstCount] = 0;
	if (toUpper)
		ToUpper(DstFilename);
}

/////////////////////////////////////////////////////////////////
// UnicodePathToAscii
//
// Takes Unicode path, converts to ascii, with options, such
// as remove path, lower case it, remove extension
void String::UnicodePathToAscii(const u16* SrcPath, char* DstFname, bool ToLower, bool StripPath, bool StripExt)
{
	char	cPath[512];
	char	Fname[128];
	char	FnameNoExt[128];

	UnicodeToAscii(SrcPath, cPath);
	if (ToLower)
		String::ToLower(cPath);

	// set the location property.. strip off the just the name
	if (StripPath)
	{
		String::StripPath(cPath, Fname);
		if (StripExt)
		{
			StripExtension(Fname, FnameNoExt);
			Strcpy(DstFname, FnameNoExt);
		}
		else
			Strcpy(DstFname, Fname);
	}
	else
	{
		if (StripExt)
		{
			StripExtension(cPath, FnameNoExt);
			Strcpy(DstFname, FnameNoExt);
		}
		else
			Strcpy(DstFname, cPath);
	}
}


