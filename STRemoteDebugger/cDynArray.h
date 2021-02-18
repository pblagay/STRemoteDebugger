//******************************************************//
// Layer: Common										//
// Module: Utility										//
// DynArray.h											//
//														//
// Dynamic Array Template								//
//														//
// Copyright (C) 2013 Biotic Software LLC.				//
//******************************************************//

#ifndef _CDYNARRAY_H_
#define _CDYNARRAY_H_

#ifndef INCLUDED_LLTCommon_llttypes_H
#include "llttypes.h"
#endif

template <class T> class DynArray
{
public:
	// NumInitItems - how many we start with
	// NumGrowItems - how many it will add if our array grows
	// ZeroInit     - Zero out new entries
	inline			DynArray(u32 NumInitItems = 4, u32 NumGrowItems = 4, bool ZeroInit = false);
	inline			~DynArray(void);						// shutdown
	inline void		Init(u32 NumInitItems = 4, u32 NumGrowItems = 4, bool ZeroInit = false);
	inline void		Clear(void);							// zero entries, does not shrink or free
	inline void		Reset(void);							// make sure list is empty and free memory
	inline s32		Count(void) const { return m_Count; }	// Num items in array
	inline u32		Total(void) const { return m_Total; }	// How big is list
	inline void		Lock(void) { m_Locked = true; }			// Lock, cant grow.. must have enough space
	inline bool		IsLocked(void) const { return m_Locked;}// Is this array locked?
	inline bool		Add(const T &item, s32 pos = -1, s32* Index = 0);		// add item, -1 or > currentSize adds to end of array
	inline T		*Expand(void);							// Expand by 1 item, return 0 on fail
	inline bool		Delete(s32 index);						// Delete item 'index',
	inline bool		DeletePtr(const T &item);				// Delete item 
	inline bool		Replace(s32 index, T &item);			// Replace item 'index'
	inline bool		Swap(s32 index1, s32 index2);			// Swap item 'index'
	inline T		*Get(s32 index) const;					// Get item 'index' 
	inline T		*GetPtr() const;						// Get ptr to top of array
	inline s32		Contains( const T &item );				// Is item in list (returns index)
	inline void		RemoveAll();							// delete all items (ptr types only!)

	inline T		&operator[](s32 index) const;			// Get item at 'index'

public:
	T			*m_List;								// List ptr
private:
	s32			m_Count;								// num valid items in array
	s32			m_Total;								// total number of items in the array
	u32			m_Grow;									// Num items to grow by
	bool		m_Zero;									// zero new entries
	bool		m_Locked;								// arrary is locked to not grow
};

#include "cDynArray.hpp"
#endif // _CDYNARRAY_H_
