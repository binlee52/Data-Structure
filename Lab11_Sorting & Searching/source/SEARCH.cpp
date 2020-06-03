//--------------------------------------------------------------------
//
//  Laboratory 15, In-lab Exercise 1                      search.cpp
//
//  Implementation of a set of searching routines
//
//--------------------------------------------------------------------

template < class LE >
int linearSearch ( LE keyList [], int numKeys,
                   LE searchKey, int &index    )

// Linear search routine. Searches the first numKeys keys in keyList
// for searchKey. If searchKey is found, then returns 1 with index
// returning the array index of the entry containing searchKey.
// Otherwise, returns 0 with index returning the array index of the
// entry containing the largest key that is smaller than searchKey
// (or -1 if there is no such key).

{
    for (int i = 0; i < numKeys; i++)
    {
        if (searchKey == keyList[i])    // found key
        {
            index = i;
            return 1;
        }
    }
    return -1;  // no such key
}

//--------------------------------------------------------------------

template <class LE>
int binarySearchSub(LE keyList[], LE searchKey, int start, int end, int& index)
{
    int mid;
    if (start > end)    // not found
        return -1;
    else
    {
        mid = (start + end) / 2;
        if (keyList[mid] == searchKey)  // found
        {
            index = mid;
            return 1;
        }
        else if (keyList[mid] > searchKey)  // search low half
            return binarySearchSub(keyList, searchKey, start, mid - 1, index);
        else    // search big half
            return binarySearchSub(keyList, searchKey, mid + 1, end, index);
    }
}


template < class LE >
int binarySearch ( LE keyList [], int numKeys,
                   LE searchKey, int &index    )

// Binary search routine. Searches the first numKeys keys in keyList
// for searchKey. If searchKey is found, then returns 1 with index
// returning the array index of the entry containing searchKey.
// Otherwise, returns 0 with index returning the array index of the
// entry containing the largest key that is smaller than searchKey
// (or -1 if there is no such key).

{
    return binarySearchSub<LE>(keyList, searchKey, 0, numKeys - 1, index);
}

//--------------------------------------------------------------------

