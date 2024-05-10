
/*
    Adapted from:
        "Formal Verification of Constant-Space Quicksort" Adrian-Stefan Mareş
    Written by Wojciech Kieloch - 2024
*/
#include <iostream>

using namespace std;

void printArray(const int *arr, const unsigned len)
{
    if (len == 0)
    {
        cout << "Empty" << endl;
        return;
    }

    for (unsigned i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int lomutoPartition(int *arr, int from, int to)
{
    int i = from - 1;
    int j = from;
    while (j < (to - 1))
    {
        if (arr[j] < arr[to - 1])
        {
            i++;
            swap(arr[i], arr[j]);
        }

        j++;
    }

    swap(arr[i + 1], arr[to - 1]);

    return i + 1;
}

void constQuicksort(int *arr, const unsigned len)
{
    if (len <= 1)
        return;

    int p = 1;
    int q = len;
    while (p < q)
    {
        if (arr[0] < arr[p])
        {
            swap(arr[0], arr[p]);
            q = len;
            p++;
        }
        else if (arr[0] == arr[p])
        {
            q--;
            swap(arr[p], arr[q]);
        }
        else
            p++;
    }

    unsigned r = 0;
    while (r < len)
    {
        unsigned nx = r + 1;
        while (nx < len && arr[nx] < arr[r])
            nx++;

        if (nx == r + 1)
            r++;
        else
        {
            const int pivIdx = lomutoPartition(arr, r + 1, nx);
            swap(arr[pivIdx], arr[r]);
        }
    }
}

int main()
{
    int N;
    cin >> N;

    if (N <= 0)
    {
        cout << "Invalid size." << endl;
        return 0;
    }

    int *arr = new int[N];
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    constQuicksort(arr, (unsigned)N);
    printArray(arr, (unsigned)N);

    delete[] arr;

    return 0;
}