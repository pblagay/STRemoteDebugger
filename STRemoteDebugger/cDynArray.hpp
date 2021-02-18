//******************************************************//
// Layer: Common										//
// Module: Utility										//
// DynArray.hpp											//
//														//
// Author: Paul Blagay									//
//														//
// Dynamic Array Template								//
//														//
// Copyright (C) 2013 Biotic Software LLC.				//
//******************************************************//

#include <assert.h>

///////////////////////////////////////////////////////////
// Create Array
//
// NumInitItems - how many we start with
// NumGrowItems - how many it will add if our array grows
// ZeroInit     - Zero out new entries
template <class T>
inline DynArray<T>::DynArray(u32 NumInitItems, u32 NumGrowItems, bool ZeroInit)
{
	if (NumInitItems != 0)
	{
		m_List = (T *)new char[NumInitItems * sizeof(T)];
		assert(m_List != NULL); // , "Out of Memory creating Array");
	}
	else
		m_List = NULL;

	m_Total		= NumInitItems;
	m_Grow		= NumGrowItems;
	m_Zero		= ZeroInit;
	m_Locked	= false;
	m_Count		= 0;

	// Setup the items
	if (m_Zero && m_List)
		memset(m_List, 0, NumInitItems * sizeof(T));
}

///////////////////////////////////////////////////////////
// Free Array
template <class T>
inline DynArray<T>::~DynArray(void)
{
	if (m_List)
		delete [] m_List;
}

template <class T>
inline void DynArray<T>::Init(u32 NumInitItems, u32 NumGrowItems, bool ZeroInit)
{
	if (NumInitItems != 0)
	{
		m_List = (T *)new char[NumInitItems * sizeof(T)];
		assert(m_List != NULL); // , "Out of Memory creating Array");
	}
	else
		m_List = NULL;

	m_Total		= NumInitItems;
	m_Grow		= NumGrowItems;
	m_Zero		= ZeroInit;
	m_Locked	= false;
	m_Count		= 0;

	// Setup the items
	if (m_Zero && m_List)
		memset(m_List, 0, NumInitItems * sizeof(T));
}

///////////////////////////////////////////////////////////
// Clear items
template <class T>
inline void DynArray<T>::Clear(void)
{
	if (m_Zero && m_List)
		memset(m_List, 0, m_Total * sizeof(T));

	m_Count = 0;
}

///////////////////////////////////////////////////////////
// Free Memory
template <class T>
inline void DynArray<T>::Reset(void)
{
	assert(m_Locked == false);

	// free memory
	if (m_List)
		delete [] m_List;

	m_Count = 0;
	m_Total = 0;
	m_List	= NULL;
}

///////////////////////////////////////////////////////////
// Add item to array
template <class T>
inline bool DynArray<T>::Add(const T &item, s32 pos, s32* Index)
{
	if (pos < 0 || pos > m_Count)
		pos = m_Count;

	// is array big enough
	if (m_Count == m_Total)
	{
		// get new size
		u32 oldsize = m_Total * sizeof(T);
		u32 newsize = (m_Total + m_Grow) * sizeof(T);

		// more space
		assert(!m_Locked);	
		T *tempList = (T *)new char[newsize];
		if (!tempList)
			return false;
		if (m_List)
			memcpy(tempList, m_List, oldsize);

		if (m_List)
			delete [] m_List;
      
		m_List = tempList;

		// new size
		m_Total += m_Grow;

		// zero it?
		if (m_Zero)
			memset((char *)m_List + oldsize, 0, newsize - oldsize);
	}

	char *olditem = (char *)m_List + pos * sizeof(T);
	u32 toMove = (u32)((u32)(m_Count) - pos);
	if (toMove > 0)
		memmove(olditem + sizeof(T), olditem, toMove * sizeof(T));

	// Insert the item
	memcpy(olditem, &item, sizeof(T));

	if (Index != NULL)
		*Index = m_Count;

	m_Count++;

	return true;
}

///////////////////////////////////////////////////////////
// Expand array by 1
template <class T>
inline T *DynArray<T>::Expand(void)
{
	// is array big enough?
	if (m_Count == m_Total)
	{
		// how big?
		u32 oldSize = m_Total * sizeof(T);
		u32 newSize = (m_Total + m_Grow) * sizeof(T);

		// need space
		assert(!m_Locked);
		T *tempList = (T *)new char[newSize];
		if (!tempList)
			return NULL;
		if (m_List)
			memcpy(tempList, m_List, oldSize);

		// remove old list, point to new
		if (m_List)
			delete [] m_List;
		
		m_List = tempList;

		// new total
		m_Total += m_Grow;

		// clear entries
		if (m_Zero)
			memset((char *)m_List + oldSize, 0, newSize - oldSize);
	}

	char *item = (char *)m_List + m_Count * sizeof(T);
	m_Count++;
	return (T *)item;
}

///////////////////////////////////////////////////////////
// Delete item from Array at 'index'
template <class T>
inline bool DynArray<T>::Delete( s32 index )
{
	// 
	if (index < 0)
		index = m_Count - 1;
	if (index < 0 || index >= m_Count)
		return false;

   // delete item
	char*	item	= (char*)m_List + index * sizeof(T);
	u32		toMove	= (u32)(m_Count - 1 - index);	
	if (toMove > 0)
		memmove(item, item + sizeof(T), toMove * sizeof(T));

	--m_Count;

	if (m_Zero)
		memset(&m_List[m_Count], 0, sizeof(T));

	return true;
}

///////////////////////////////////////////////////////////
// Delete item from Array by pointer
template <class T>
inline bool DynArray<T>::DeletePtr( const T &pitem )
{
	// find item
	s32 index = Contains(pitem);
	// 
	if (index < 0)
		index = m_Count - 1;
	if (index < 0 || index >= m_Count)
		return false;

	// delete item
	char*	item	= (char*)m_List + index * sizeof(T);
	u32		toMove	= (u32)(m_Count - 1 - index);	
	if (toMove > 0)
		memmove(item, item + sizeof(T), toMove * sizeof(T));

	--m_Count;

	if (m_Zero)
		memset(&m_List[m_Count], 0, sizeof(T));

	return true;
}

///////////////////////////////////////////////////////////
// Replace item at 'index'
template <class T>
inline bool DynArray<T>::Replace( s32 index, T &newItem)
{
	if (index < 0)
		index = m_Count - 1;
	if (index < 0 || index >= m_Count)
		return false;

	// replace him
	memcpy(&m_List[index], &newItem, sizeof(T));
	return true;
}

///////////////////////////////////////////////////////////
// Swap items at index1, index2
template <class T>
inline bool DynArray<T>::Swap( s32 index1, s32 index2)
{
	assert(false); // , "WIP - don't use");
	if (index1 < 0 || index1 >= m_Count)
		return false;
	if (index2 < 0 || index2 >= m_Count)
		return false;

	// swap elements
	T* tempItem = (T*)new char[sizeof(T)];
	memcpy(&tempItem, &m_List[index1], sizeof(T));
	memcpy(&m_List[index1], &m_List[index2], sizeof(T));
	memcpy(&m_List[index2], &tempItem, sizeof(T));
	delete tempItem;

	return true;
}

///////////////////////////////////////////////////////////
// Get item @ index
template <class T>
inline T *DynArray<T>::Get( s32 index ) const
{
	if (index < 0)
		index = m_Count - 1;
	if (index < 0 || index >= m_Count)
		return NULL;

	return &m_List[index];
}

///////////////////////////////////////////////////////////
// Get ptr
template <class T>
inline T *DynArray<T>::GetPtr(void) const
{
	return m_List;
}

///////////////////////////////////////////////////////////
// array lookup
template <class T>
inline T &DynArray<T>::operator[](s32 index) const
{
	assert(index >= 0 && index < m_Count);
	return m_List[index];
}

///////////////////////////////////////////////////////////
// Contains
template <class T>
inline s32 DynArray<T>::Contains( const T &item ) 
{
	for (int i = 0; i < m_Count; i++)
	{
		if (m_List[i] == item)
		{
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////
// RemoveAll
template <class T>
inline void DynArray<T>::RemoveAll() 
{
	for (int i = 0; i < m_Count; i++)
		delete m_List[i];

	Reset();
}
