#include "bracket.h"
#include <stack>

bool checkBrackets(const std::string& s) {
    std::stack<int> br;
    for (int i = 0; i < std::size(s); i++)
        if (s[i] == '(' || s[i] == '{' || s[i] == '[' || s[i] == '<')
            br.push(s[i]);
        else if (s[i] == ')')
        {
            if (std::size(br) == 0 || br.top() != '(')
                return false;
            br.pop();
        }
        else if (s[i] == '}')
        {
            if (std::size(br) == 0 || br.top() != '{')
                return false;
            br.pop();
        }
        else if (s[i] == ']')
        {
            if (std::size(br) == 0 || br.top() != '[')
                return false;
            br.pop();
        }
        else if (s[i] == '>')
        {
            if (std::size(br) == 0 || br.top() != '<')
                return false;
            br.pop();
        }
    return true;
}
