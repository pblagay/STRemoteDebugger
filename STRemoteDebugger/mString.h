//******************************************************//
// Layer: Common										//
// Module: String										//
// mString.h											//
//														//
// Simple string container								//
//														//
// Copyright (C) 2013 Biotic Software LLC.				//
//******************************************************//

#ifndef _MSTRING_H_
#define	_MSTRING_H_

#include "llttypes.h"


class mString
{
public:
	mString();												// default (string == NULL)
	mString(mString& string)
	{
		m_String = NULL;
		m_engineHeap = false;
		m_String = NULL;
		m_isWide = false;
		m_Size = 0;
		CreateString(string.Get());
	};

	mString(const char* string);							// assign and allocate char string
	mString(const u16* string);								// assign and allocate u16 string
	mString(u32 size, bool isWide = false);					// assign empty space of size
	~mString();

	// methods
	const char* Get() { return m_String; }					// get string buffer
	char* GetPtr(u32 index = 0);							// get pointer into string
	void Set( const char* fmtString, ...);					// set with variable args
	void SetChar(u32 index, const char* ch);				// set a character at position
	void SetChar(u32 index, const u16* ch);					// set a character at position
	void AddChar(const char* ch);							// add a character to the current string
	void SetZero(u32 index);								// set a character at position
	bool Empty();											// is empty?
	void Clear();											// clear data
	void Clear(u32 size);									// clear data and allocate space of size
	void ToWide();											// convert to wide characters
	void ToChar();											// convert to char characters
	bool IsWide() { return m_isWide; }						// is string wide
	u32  Length();											// get length
	void ToUpper();											// force to upper case
	void ToLower();											// force to lower case
	void Zero();											// zeroes out the string memory
	void ToPZZTStr();										// for windows

	// file name helpers
	u32  StripPath(const char* src, bool stripExtension = false);	// strip path from source and set (creates a new string from src and strips path)
	u32  StripPath(bool stripExtension = false);					// strips path from existing string
	void StripExtension(const char* src);					// strip extension from source (creates a new string from src and strips extension)
	void StripExtension();									// strips extension from existing string
	void GetPath(const char* src);							// keeps the existing path (creates a new string from src and strips filename)
	void GetPath(bool stripDriveLetter = false);				// keeps just the path from existing string
	void SlashConvertFromFrontToBack(bool toUpper = false);	// convert front slash to back
	void SlashConvertFromBackToFront(bool toUpper = false);	// convert backslash to front
	u32  AddTrailingBackslash(const char* separator);		// add trailing backslash to path if not found
	void GetDriveLetter(mString& driveLetter);				// return root drive

	// operators
	void operator= (mString& string);
	void operator= (const char* string);
	void operator= (const u16* string);
	void operator+= (mString& string);
	void operator+= (const char* string);
	void operator+= (const u16* string);
	bool operator== (const char* string);
	bool operator== (const u16* string);
	bool operator== (mString& string);
	bool operator!= (mString& string);

private:
	void  CreateString(const char* string);					// create a char string
	void  CreateString(const u16* string);					// create a wide string
	void  SetHeap();										// set heap to handle statically allocated
	void  Allocate(u32 size, bool isWide = false);			// allocate m_String
	char* AllocateNew(u32 size, bool isWide = false);		// allocate a new string and set heap
	void  Free(bool resetSize = true);						// free from heap
private: 
	char*	m_String;										// allocated string
	u32		m_Size;											// size of allocation
	bool	m_isWide;										// char or wide
	bool	m_engineHeap;									// uses engine heap
};

#endif // _MSTRING_H_