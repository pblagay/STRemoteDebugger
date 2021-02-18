//******************************************************//
// Layer: Common										//
// 														//
// lltcommon/llttypes.h									//
//														//
// Main App Class + common includes						//
//														//
// Copyright (C) 2013 Biotic Software LLC               //
//******************************************************//

#ifndef INCLUDED_LLTCOMMON_LLTTYPES_H
#define INCLUDED_LLTCOMMON_LLTTYPES_H

// This header is REQUIRED for Xbox 360 intrinsic support.
// Removal of the lines below would cause all intrinsic operations to fail
#if defined(LLT_X360)
#ifndef __PPCINTRINSICS_H__
#include <ppcintrinsics.h>
#endif

#ifndef __VECTORINTRINSICS_H__
#include <vectorintrinsics.h>
#endif
#endif

///////////////////////////////////////////////////////////
// a common bool type so we dont have issues between 
// platforms

//typedef signed char bool;
typedef unsigned int ubool;	// Return value that's the size of an int, but only 0 or 1 allowed

///////////////////////////////////////////////////////////
// new types

typedef unsigned char	u8;
typedef signed char		s8;
typedef unsigned short	u16;
typedef signed short	s16;
typedef float			f32;
typedef double			f64;
typedef f32				OPT_VEC;

// UTF-16 string
typedef unsigned short schar;

// u32, u64, vector and common operations that change with each target
#if defined (LLT_DX)
	#if defined( X86 )	// Wii define needed to make typedefs the same when compiling ModelRip
	typedef unsigned int u32;
	typedef signed	 int s32;
	#else
	typedef unsigned long u32;
	typedef long s32;
	#endif
	typedef unsigned __int64 u64;
	typedef signed __int64 s64;
	typedef __w64 unsigned long uPtr;
	typedef f64 LL_F64;
#define LLT_ALIGN(x,s) __declspec(align(s))(x)
#define LLT_PREALIGN(s) __declspec(align(s))
#define LLT_POSTALIGN(s)
#define LLT_LITTLEENDIAN
#define LLT_INTEL
#define	PLATFORM_ID		"PC"

#elif defined (LLT_X360)
	typedef unsigned long u32;
	typedef long s32;
	typedef unsigned __int64 u64;
	typedef signed	 __int64 s64;
	typedef unsigned long uPtr;
	typedef f64 LL_F64;
	typedef __vector4 intvector128;
#define LLT_VECTOR128
#define LLT_ALIGN(x,s) __declspec(align(s))(x)
#define LLT_PREALIGN(s) __declspec(align(s))
#define LLT_POSTALIGN(s)
#define LLT_BIGENDIAN
#define LLT_POWERPC
#define	PLATFORM_ID		"X360"

#elif defined(LLT_MAC)
	typedef unsigned int			u32;
	typedef signed int				s32;
	typedef unsigned long long		u64;
	typedef signed long long		s64;
	typedef unsigned long uPtr;
	typedef f64						LL_F64;
#if defined(__MWERKS__)
#define LLT_ALIGN(x,s) __declspec(align(s))(x)
#define LLT_PREALIGN(s) __declspec(align(s))
#define LLT_POSTALIGN(s)
#else
#define LLT_ALIGN(x,s) (x) __attribute__(aligned(s))
#define LLT_PREALIGN(s)
#define LLT_POSTALIGN(s) __attribute__((aligned(s)))
#endif
#define LLT_BIGENDIAN
#if defined(__i386__)
#define LLT_INTEL
#else
#define LLT_POWERPC
#endif
#define	PLATFORM_ID		"MAC"
#elif defined (LLT_ANDROID) 
	typedef unsigned int			u32;
	typedef signed int				s32;
	typedef unsigned long long		u64;
	typedef signed long long		s64;
	typedef unsigned long uPtr;
	typedef f64						LL_F64;

#define LLT_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define LLT_PREALIGN(s)
#define LLT_POSTALIGN(s) __attribute__((aligned(s)))
#if defined _LITTLE_ENDIAN
#define LLT_LITTLEENDIAN
#else
#define LLT_BIGENDIAN
#endif
#define LLT_MIPS
#define	PLATFORM_ID		"ANDR"
#elif defined (LLT_IOS) 
typedef unsigned int			u32;
typedef signed int				s32;
typedef unsigned long long		u64;
typedef signed long long		s64;
typedef unsigned long uPtr;
typedef f64						LL_F64;

#define LLT_ALIGN(x,s) (x) __attribute__((aligned(s)))
#define LLT_PREALIGN(s)
#define LLT_POSTALIGN(s) __attribute__((aligned(s)))
#if defined _LITTLE_ENDIAN
#define LLT_LITTLEENDIAN
#else
#define LLT_BIGENDIAN
#endif
#define LLT_MIPS
#define	PLATFORM_ID		"IOS"

#else
	typedef unsigned long			u32;
	typedef long					s32;
	typedef unsigned __int64		u64;
	typedef signed	 __int64		s64;
	typedef unsigned long uPtr;
	typedef f64						LL_F64;
#define LLT_ALIGN(x,s) __declspec(align(s))(x)
#define LLT_PREALIGN(s) __declspec(align(s))
#define LLT_POSTALIGN(s)
#define LLT_LITTLEENDIAN
#define LLT_INTEL
#define	PLATFORM_ID		"PC"		// Assume PC
#endif

///////////////////////////////////////////////////////////
// a common handle
typedef s32 _Handle;

///////////////////////////////////////////////////////////////////////////
// Abort Vector (assert)
typedef void (debug_fndec)(u32 Type,const char* File, u32 Line, const char* Func,const char* ExpStr,const char* MsgStr, ... );
typedef	debug_fndec* debug_fnptr;

// Standard macros.
#if !defined(NULL)
#define NULL 0
#endif

#if !defined(TRUE)
#define TRUE 1
#endif

#if !defined(FALSE)
#define FALSE 0
#endif

// to remove warnings on some func types
//#define		true		1
//#define		false		0

#endif // INCLUDED_LLTCOMMON_TYPES_H


