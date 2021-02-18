//******************************************************//
// Layer: Gaia											//
//														//
// 														//
// Helpers.cpp											//
//														//
// Author: Paul Blagay									//
//														//
// Conversion helpers between managed / C++				//
//														//
// Copyright (C) 2013 Biotic Software LLC.				//
//******************************************************//
// system includes
#include <stdio.h>
#include <wtypes.h>
#include "Helpers.h"

// string helper function to convert from marshalled C++ to char*
char* ConvertStringToChar(System::String^ string)
{
	System::IntPtr ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
	return static_cast<char*>(ptrToNativeString.ToPointer());
}
// string helper function to convert from marshalled C++ to wchar
void ConvertStringToLChar(System::String^ string, WCHAR& wcharString)
{
	System::IntPtr ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
	char* simpleString = static_cast<char*>(ptrToNativeString.ToPointer());
	int length = strlen(simpleString);
	mbstowcs(&wcharString, simpleString, length);
	WCHAR* w = &wcharString;
	w[length] = 0;
}

// convert from char* to System.String
System::String^ ConvertCharToString(const char* string)
{
	System::String ^strString = gcnew System::String(string);
	return strString;
}
// convert from float to System.String
System::String^ ConvertFloatToString(float value)
{
	char	buf[32];
	sprintf(buf, "%.2f", value);
	System::String ^strString = gcnew System::String(buf);
	return strString;
}
// convert from int to System.String
System::String^ ConvertIntToString(int value)
{
	char	buf[32];
	sprintf(buf, "%d", value);
	System::String ^strString = gcnew System::String(buf);
	return strString;
}

// convert from int to System.String
System::String^ ConvertIntToAscii(int value)
{
	char	buf[2] = { 0 };
	buf[0] = value;
	System::String^ strString = gcnew System::String(buf);
	return strString;
}

// convert from Uint to System.String
System::String^ ConvertUintToString(unsigned int value)
{
	char	buf[32];
	sprintf(buf, "%lu", value);
	System::String ^strString = gcnew System::String(buf);
	return strString;
}

// create color icon
System::Drawing::Bitmap^ createColorIcon(System::Drawing::Color colour)
{
	System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(16, 16);
	for( int x = 0; x <  bitmap->Height; ++x )
	{
		for( int y = 0; y < bitmap->Width; ++y )
		{
			bitmap->SetPixel(x, y, colour);
		}
	}
	return bitmap;
}
