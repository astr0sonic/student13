#include <iostream>
#include <vector>
#include <string>

std::vector<int> getIndices(const std::string& my_template, const std::string& text) {
    std::vector<int> result;
    int i = 0, j = 0;
    std::vector<int> pref(size(my_template));
    pref[0] = 1;
    for (int i = 1; i < size(my_template); i++)
    {
        int j = pref[i - 1];
        while (j > 0 && my_template[i] != my_template[j])
            j = pref[j - 1];
        if (my_template[i] == my_template[j])
            j++;
        pref[j] = j;
    }
    while (i < size(text))
    {
        if (j == size(my_template))
        {
            result.push_back(i - j);
            j = 0;
        }
        if (text[i] == my_template[j])
        {
            i++;
            j++;
        }
        else if (j == 0)
            i++;
        else
        {
            j += pref[j - 1];
            i++;
        }
    }
    if (j == size(my_template))
        result.push_back(i - j);
    return result;
}