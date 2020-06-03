//--------------------------------------------------------------------
//
//  Laboratory 15, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//--------------------------------------------------------------------

template <class LE>
void swap(LE& key1, LE& key2)
// key1, key2�� ���� ��ü
{
    LE temp = key1;
    key1 = key2;
    key2 = temp;
}

template < class LE >
void selectionSort ( LE keyList [], int numKeys )
// ��������
// �ּڰ��� �Ǿ����� ���� �Ѵ�.
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
                min_idx = j;    // �ּڰ� ����
        }
        swap<LE>(keyList[min_idx], keyList[i]); // list�� ������ keyList[i]�� �ּڰ� ��ȯ
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
            while ((keyList[left] > keyList[i]) && (i < right))     // a[i]�� pivot�� a[left]���� ������ ����
                i++;
            while (keyList[left] < keyList[j] && (j > left))    // a[j]�� pivot�� a[left]���� ũ�� ����
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
// �̿����ִ� �� ��Ҹ� ���Ͽ� ���� ���� ���� �迭�� ���� ����(start)�� ������ ��.
{
    for (int i = end; i > start; i--)
    {
        if (keyList[i] < keyList[i - 1])
            swap(keyList[i], keyList[i - 1]);
    }
}

template < class LE >
void bubbleSort ( LE keyList [], int numKeys )
// �̿����ִ� �� ��Ҹ� ���ϸ� ����. ������ �ٲ�� ������ swap
// ���� ���δ� ���ĵǰ� �Ѵ�.
// Time Complexity: O(N^2)
// Unknown sort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    for (int i = 0; i < numKeys - 1; i++)
    {
        bubbleUp(keyList, i, numKeys - i);  //���� ������ ����
    }
}
