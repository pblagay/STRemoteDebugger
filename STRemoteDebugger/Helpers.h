//******************************************************//
// Layer: Gaia											//
//														//
// 														//
// Helpers.h											//
//														//
// Author: Paul Blagay									//
//														//
// Conversion helpers between managed / C++				//
//														//
// Copyright (C) 2013 Biotic Software LLC.				//
//******************************************************//
#pragma once
#using "System.dll"

#ifndef _GAIAHELPERS_H
#define _GAIAHELPERS_H

char* ConvertStringToChar(System::String^ string);
void ConvertStringToLChar(System::String^ string, WCHAR& wcharString);
System::String^ ConvertCharToString(const char* string);
System::String^ ConvertFloatToString(float value);
System::String^ ConvertIntToString(int value);
System::String^ ConvertIntToAscii(int value);
System::String^ ConvertUintToString(unsigned int value);
System::Drawing::Bitmap^ createColorIcon(System::Drawing::Color colour);

#endif // _GAIAHELPERS_H