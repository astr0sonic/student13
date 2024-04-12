#include "volume.h"

int getMaxVolume(int a, int b, int c, int n, int* arr)
{
    int* arr_cpoy = arr;
    int res = 0;
    for (int* p = arr; p + a < arr + n; ++p)
        if (*p > res && p[a] > res && *p <= c && p[a] <= c)
        {
            res = p[a];
            if (*p < p[a])
                res = *p;
            arr_cpoy = p;
        }
    int i = 0, j = n - 1;
    if (a < n - 1)
        j = a;
    while (i < j)
    {
        if (arr_cpoy[i] > arr_cpoy[j])
        {
            if (res < arr_cpoy[j] * (j - i) && (j - i) <= a && arr_cpoy[j] <= c)
                res = arr_cpoy[j] * (j - i);
            j--;
        }
        else
        {
            if (res < arr_cpoy[i] * (j - i) && (j - i) <= a && arr_cpoy[i] <= c)
                res = arr_cpoy[i] * (j - i);
            i++;
        }
    }
    return res * b;
}
