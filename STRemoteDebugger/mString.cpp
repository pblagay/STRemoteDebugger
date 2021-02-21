//******************************************************//
// Layer: Common										//
// Module: String										//
// mString.cpp											//
//														//
// Simple string container								//
//														//
// Copyright (C) 2013 Biotic Software LLC.				//
//******************************************************//

//////////////////////////////////////////////////////////
// Includes 
//////////////////////////////////////////////////////////
#include <windows.h>
#include <debugapi.h>
#include <stdio.h>
#include <string.h>
#include "mString.h"
#include "cString.h"
#include <assert.h>



const char* mString_null = "\0\0";

//////////////////////////////////////////////////////////
// ctor / dtor
//////////////////////////////////////////////////////////
mString::mString()
{
	m_engineHeap = false;
	m_String = NULL;
	m_isWide = false;
	m_String = (char*)mString_null;
	m_Size = 0;
}

mString::mString(const char* string)
{
	m_engineHeap = false;
	m_String = (char*)mString_null;
	m_isWide = false;
	m_Size = 0;
	CreateString(string);
}

mString::mString(const u16* string)
{
	m_engineHeap = false;
	m_String = (char*)mString_null;
	m_isWide = true;
	m_Size = 0;
	CreateString(string);
}

mString::mString(u32 size, bool isWide)
{
	m_engineHeap = false;
	m_String = (char*)mString_null;
	m_isWide = isWide;
	Allocate(size, isWide);
	memset(m_String, 0, size);
	assert(m_String != NULL); // "mString - unable to allocate string memory!");
}

mString::~mString()
{
}

//////////////////////////////////////////////////////////
// helpers
//////////////////////////////////////////////////////////
void mString::CreateString(const char* string)
{
	if (string)
	{
		u32 len = strlen(string) + 1;
		if (len > m_Size)
			Free();
		
		Allocate(len);
//		Zero();
		assert(m_String != NULL); // "mString - unable to allocate string memory!");
		memcpy(m_String, string, len);
	}
}

void mString::CreateString(const u16* string)
{
	if (string)
	{
		u32 len = String::Strlen(string) + 1;
		Allocate(len * 2);
		Zero();
		assert(m_String != NULL); // "mString - unable to allocate string memory!");
		memcpy(m_String, string, len * 2);
		m_isWide = true;
	}
}

//////////////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////////////

// set zero
void mString::SetZero(u32 index)
{
	assert(index < m_Size); // "Exceeded length of allocated buffer!");

	if (m_isWide)
	{
		u16* ptr = (u16*)&m_String[index * 2];
		*ptr = 0;
	}
	else
		m_String[index] = 0;
}

// set a char / u16 in the string
void mString::SetChar(u32 index, const char* ch)
{
	assert(index < m_Size); // "Exceeded length of allocated buffer!");

	if (m_isWide)
	{
		OutputDebugString(L"Attempting to set a u8 in a wide string!\n");
		return;
	}
	m_String[index] = *ch;
}

void mString::SetChar(u32 index, const u16* ch)
{
	assert(index < (m_Size / 2)); // "Exceeded length of allocated buffer!");

	if (!m_isWide)
	{
		OutputDebugString(L"Attempting to set a u16 in a char string!\n");
		return;
	}
	u16* ptr = (u16*)&m_String[index * 2];
	*ptr = *ch;
}

// add a char / u16 in the string
void mString::AddChar(const char* ch)
{
	if (m_isWide)
	{
		OutputDebugString(L"Attempting to set a u8 in a wide string!\n");
		return;
	}
	if (m_String == mString_null)
	{
		OutputDebugString(L"Attempting to set a u8 with a null string!\n");
		return;
	}

	u32 index = strlen(m_String);
	assert(index < m_Size); // "Exceeded length of allocated buffer!");
	m_String[index] = *ch;
}

// return ptr to string
char* mString::GetPtr(u32 index)
{ 
	assert(index < m_Size); // "Index out of bounds of allocated buffer!");

	if (m_isWide)
		index *= 2;
	return &m_String[index]; 
}					

// Zero
void mString::Zero()
{ 
	if (m_String == mString_null)
		return;
	memset(m_String, 0, m_Size);
}

// Clear
void mString::Clear()
{ 
	Free();
	m_String = (char*)mString_null;
}

void mString::Clear(u32 size)
{ 
	if (size > m_Size)
		Free();
	Allocate(size);
	m_String[0] = 0;
	assert(m_String != NULL); // "mString - unable to allocate string memory!");
}

// StripPath
u32 mString::StripPath(const char* src, bool stripExtension)
{
	Free();
	u32 len = strlen(src) + 1;
	Allocate(len);
	assert(m_String != NULL); // "mString - unable to allocate string memory!");
	return String::StripPath(src, m_String, stripExtension);
}

u32 mString::StripPath(bool stripExtension)
{
	assert(m_String != NULL); // "m_String == NULL!");

	char* newString = NULL;
	u32 len = strlen(m_String) + 1;
	if (m_isWide)
	{
		assert(false); // "StripPath for u16 not implemented yet!");
		newString = AllocateNew(len * 2);
	}
	else
		newString = AllocateNew(len);

	u32 result = String::StripPath(m_String, newString, stripExtension);
	Free(false);
	m_String = newString;
	return result;
}

// StripExtension
void mString::StripExtension(const char* src)
{
	Free();
	u32 len = strlen(src) + 1;
	Allocate(len);
	assert(m_String != NULL); // "mString - unable to allocate string memory!");
	String::StripExtension(src, m_String);
}

void mString::StripExtension()
{
	assert(m_String != NULL); // "m_String == NULL!");

	char* newString = NULL;
	u32 len = strlen(m_String) + 1;
	if (m_isWide)
	{
		assert(false); // "StripExtension for u16 not implemented yet!");
		newString = AllocateNew(len * 2);
	}
	else
		newString = AllocateNew(len);

	if (String::StripExtension(m_String, newString))
	{
		Free(false);
		m_String = newString;
	}
	else
		Free();
}

// GetPath
void mString::GetPath(const char* src)
{
	Free();
	u32 len = strlen(src) + 1;
	Allocate(len);
	assert(m_String != NULL); // "mString - unable to allocate string memory!");
	String::GetPath(src, m_String);
}

void mString::GetPath(bool stripDriveLetter)
{
	assert(m_String != NULL); // "m_String == NULL!");

	char* newString = NULL;
	u32 len = String::Strlen(m_String) + 1;
	if (m_isWide)
	{
		assert(false); // "GetPath for u16 not implemented yet!");
		newString = AllocateNew(len * 2);
	}
	else
		newString = AllocateNew(len);

	String::GetPath(m_String, newString, stripDriveLetter);
	Free(false);
	m_String = newString;
}

// get drive letter
void mString::GetDriveLetter(mString& driveLetter)
{
	char rd[5] = { 0 };
	memcpy(rd, m_String, 2);
	driveLetter = rd; 
}

// SlashConvertFromFrontToBack
void mString::SlashConvertFromFrontToBack(bool toUpper)
{
	assert(m_String != NULL); // "m_String == NULL!");

	char* newString = NULL;
	u32 len = strlen(m_String) + 1;
	if (m_isWide)
	{
		assert(false); // "GetPath for u16 not implemented yet!");
		newString = AllocateNew(len * 2);
	}
	else
		newString = AllocateNew(len);

	String::SlashConvertFromFrontToBack(m_String, newString, toUpper);
	Free(false);
	m_String = newString;
}

// SlashConvertFromBackToFront
void mString::SlashConvertFromBackToFront(bool toUpper)
{
	assert(m_String != NULL); // "m_String == NULL!");

	char* newString = NULL;
	u32 len = strlen(m_String) + 1;
	if (m_isWide)
	{
		assert(false); // "GetPath for u16 not implemented yet!");
		newString = AllocateNew(len * 2);
	}
	else
		newString = AllocateNew(len);

	String::SlashConvertFromBackToFront(m_String, newString, toUpper);
	Free(false);
	m_String = newString;
}

// Add trailing backslash
u32 mString::AddTrailingBackslash(const char* separator)
{
	assert(m_String != NULL); // "m_String == NULL!");

	char* newString = NULL;
	u32 len = strlen(m_String) + 2;
	if (m_isWide)
	{
		assert(false); // "GetPath for u16 not implemented yet!");
		newString = AllocateNew(len * 2);
	}
	else
		newString = AllocateNew(len);

	memset(newString, 0, len);
	memcpy(newString, m_String, strlen(m_String));
	u32 pos = String::AddTrailingBackslash(newString, separator);
	Free(false);
	m_String = newString;
	return pos;
}

// Set
void mString::Set( const char* fmtString, ...)
{
	if(!fmtString)
		return;

	if (fmtString[0] == 0)
	{
		Free();
		return;
	}

	va_list args;

	char buf[1024];

	va_start(args, fmtString);
	vsprintf(buf, fmtString, args);
	va_end(args);
	CreateString(buf);
}

// to char (u8)
void mString::ToChar()
{
	assert(m_String != NULL); // "m_String == NULL!");

	if (!m_isWide)
		return;

	m_isWide = false;
	u32 len = String::Strlen((u16*)m_String) + 1;
	char* newString = AllocateNew(len);
	String::UnicodeToAscii((u16*)m_String, newString);
	Free(false);
	m_String = newString;
}

// to wide (u16)
void mString::ToWide()
{
	assert(m_String != NULL); // "m_String == NULL!");

	if (m_isWide)
		return;

	m_isWide = true;
	u32 len = String::Strlen(m_String) + 1;
	char* newString = AllocateNew(len * 2);
	String::AsciiToUnicode(m_String, (u16*)newString);
	Free(false);
	m_String = newString;
}


void mString::ToPZZTStr()
{
	u32 len = String::Strlen(m_String) + 2;
	char* newString = AllocateNew(len);
	memcpy(newString, m_String, len - 2);
	newString[len - 2] = 0;
	newString[len - 1] = 0;
	Free(false);
	m_String = newString;
}

// Length
u32 mString::Length()
{
	if (m_isWide)
		return String::Strlen((u16*)m_String);

	return String::Strlen(m_String);
}

// Upper / Lower
void mString::ToUpper()
{
	m_String = String::ToUpper(m_String);
}

void mString::ToLower()
{
	m_String = String::ToLower(m_String);
}

bool mString::Empty()
{
	if (m_String && m_String[0] == 0)
		return true;

	return false;
}


//////////////////////////////////////////////////////////
// overloads
//////////////////////////////////////////////////////////
void mString::operator= (mString& string)
{	
	CreateString(string.Get());
}

void mString::operator= (const char* string)
{	
	if(!string)
		return;

	CreateString(string);
}

void mString::operator= (const u16* string)
{	
	if(!string)
		return;

	CreateString(string);
}

void mString::operator+= (const u16* string)
{
	if (!string)
		return;

	u32 oldLen = String::Strlen((u16*)m_String) * 2;
	u32 newLen = String::Strlen(string) * 2;
	
	char* newString = AllocateNew( max((s32)(oldLen + newLen + 2), (s32)m_Size) );
	memcpy(newString, m_String, oldLen);
	memcpy( (void*)((u32)newString + oldLen), string, newLen);
	Free(false);
	m_String = newString;
}

void mString::operator+= (const char* string)
{
	if (!string)
		return;

	u32 oldLen = 0;
	if (m_String)
		oldLen = String::Strlen(m_String);
	u32 newLen = String::Strlen(string);
	
	char* newString = AllocateNew( max((s32)(oldLen + newLen + 1), (s32)m_Size) );
	if (m_String && m_String[0] != 0)
		memcpy(newString, m_String, oldLen);
	memcpy( (void*)((u32)newString + oldLen), string, newLen);
	newString[oldLen + newLen] = 0;
	Free(false);
	m_String = newString;
}

void mString::operator+= (mString& string)
{
	u32 oldLen = 0;
	if (m_String)
		oldLen = String::Strlen(m_String);
	u32 newLen = string.Length();

	char* newString = AllocateNew( max((s32)(oldLen + newLen + 1), (s32)m_Size) );
	if (m_String && m_String[0] != 0)
		memcpy(newString, m_String, oldLen);
	memcpy( (void*)((u32)newString + oldLen), string.Get(), newLen);
	newString[oldLen + newLen] = 0;
	Free(false);
	m_String = newString;
}

bool mString::operator== (mString& string)
{
	if (m_isWide && !string.IsWide())
	{
		OutputDebugString(L"Attempting to compare a u8 string with a u16 string\n"); // %s <> %s\n", m_String, string.Get());
		return false;
	}

	if (!String::Strcmp(m_String, string.Get()))
		return true;

	return false;
}

bool mString::operator!= (mString& string)
{
	if (m_isWide && !string.IsWide())
	{
		OutputDebugString(L"Attempting to compare a u8 string with a u16 string\n"); //% s <>% s\n", m_String, string.Get());
		return false;
	}

	if (String::Strcmp(m_String, string.Get())) 
		return true;

	return false;
}

bool mString::operator== (const char* string)
{
	if (m_isWide)
		return false;

	if (!String::Strcmp(m_String, string))
		return true;

	return false;
}

bool mString::operator== (const u16* string)
{
	if (!m_isWide)
		return false;

	if (!String::Strcmp((u16*)m_String, string))
		return true;

	return false;
}

void mString::Allocate(u32 size, bool isWide)
{
	if (size == 0)
		return;

	if (size <= m_Size && (m_String != mString_null && m_String != NULL))
		return;

	m_String = new char[size];
	m_Size = size;

	m_engineHeap = true;
}

char* mString::AllocateNew(u32 size, bool isWide)
{
	if (size == 0)
		return NULL;

	if (isWide)
		size *= 2;

	char* addr = new char[size];
	addr[0] = 0;
	m_Size = size;

	m_engineHeap = true;
	return addr;
}

void mString::Free(bool resetSize)
{
	if (m_String == mString_null || m_String == NULL)
		return;

	delete[] m_String;
	m_String = (char*)mString_null;
	if (resetSize)
		m_Size = 0;
}