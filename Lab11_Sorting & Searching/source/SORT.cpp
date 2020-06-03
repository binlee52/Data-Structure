//--------------------------------------------------------------------
//
//  Laboratory 15, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//--------------------------------------------------------------------

template <class LE>
void swap(LE& key1, LE& key2)
// key1, key2의 값을 교체
{
    LE temp = key1;
    key1 = key2;
    key2 = temp;
}

template < class LE >
void selectionSort ( LE keyList [], int numKeys )
// 선택정렬
// 최솟값을 맨앞으로 오게 한다.
// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
    int min_idx;
    for (int i = 0; i < numKeys - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < numKeys; j++)
        {
            if (keyList[min_idx] > keyList[j])
                min_idx = j;    // 최솟값 갱신
        }
        swap<LE>(keyList[min_idx], keyList[i]); // list의 시작점 keyList[i]와 최솟값 교환
    }
}


//--------------------------------------------------------------------
template < class LE >
void quickPartition(LE keyList[], int left, int right);

template < class LE >
void quickSort ( LE keyList [], int numKeys )

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList, 0, numKeys-1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class LE >
void quickPartition ( LE keyList [], int left, int right)

// Recursive partner of the quickSort routine. Partitions the array
// entries between left and right into two subarrays. One subarray
// contains the keys that are less than or equal to splitValue, and
// the other contains the keys that are greater than splitValue.
// Recursively sorts each of these subarrays.

{
    if (left < right)
    {
        int i = left + 1;
        int j = right;
        while (true)
        {
            while ((keyList[left] > keyList[i]) && (i < right))     // a[i]가 pivot인 a[left]보다 작으면 증가
                i++;
            while (keyList[left] < keyList[j] && (j > left))    // a[j]가 pivot인 a[left]보다 크면 감소
                j--;
            if (i >= j) // stop roop
                break;
            swap(keyList[i++], keyList[j--]);   // exchange 
        }
        swap(keyList[left], keyList[j]);
        quickPartition(keyList, left, j - 1);
        quickPartition(keyList, j + 1, right);
    }
}

//--------------------------------------------------------------------

template <class LE>
void bubbleUp(LE keyList[], int start, int end)
// 이웃해있는 두 요소를 비교하여 가장 작은 값이 배열의 가장 왼쪽(start)에 오도록 함.
{
    for (int i = end; i > start; i--)
    {
        if (keyList[i] < keyList[i - 1])
            swap(keyList[i], keyList[i - 1]);
    }
}

template < class LE >
void bubbleSort ( LE keyList [], int numKeys )
// 이웃해있는 두 요소를 비교하며 정렬. 순서가 바뀌어 있으면 swap
// 왼쪽 끝부다 정렬되게 한다.
// Time Complexity: O(N^2)
// Unknown sort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    for (int i = 0; i < numKeys - 1; i++)
    {
        bubbleUp(keyList, i, numKeys - i);  //왼쪽 끝부터 정렬
    }
}
