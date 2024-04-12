#include "volume.h"

int getMaxVolume(int a, int b, int c, int n, int* arr)
{
    int* arr_copy = arr;
    int res = 0;
    for (int* p = arr; p + a < arr + n; p++)
        if (std::min({ *p, p[a] }) > res && std::min({ *p, p[a] }) <= c)
        {
            res = *p;
            if (res > p[a])
                res = p[a];
            arr_copy = p;
        }

    res *= a;
    int i = 0, j = n - 1;
    if (a < n - 1)
        j = a;
    while (i < j)
    {
        if (arr_copy[i] > arr_copy[j])
        {
            if (res < arr_copy[j] * (j - i) && (j - i) <= a && arr_copy[j] <= c)
                res = arr_copy[j] * (j - i);
            j--;
        }
        else
        {
            if (res < arr_copy[i] * (j - i) && (j - i) <= a && arr_copy[i] <= c)
                res = arr_copy[i] * (j - i);
            i++;
        }
    }
    return res * b;
}
