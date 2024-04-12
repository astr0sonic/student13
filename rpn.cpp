#include "rpn.h"
#include <cmath>
#include <stack>

double calculateRPN(const std::string& expr) {
    std::stack<double> st;
    double num;
    char k, lst;
    int i = 0;
    while (i < size(expr))
    {
        k = expr[i];
        i++;
        if (isdigit(k))
            st.push(k - '0');
        else if (k == '+' || k == '-' || k == '*' || k == '^' || k == '/')
        {
            lst = k;
            num = st.top();
            st.pop();
            if (k == '+')
                num += st.top();
            else if (k == '-')
                num = st.top() - num;
            else if (k == '*')
                num *= st.top();
            else if (k == '/')
                num = st.top() / num;
            else if (k == '^')
                num = pow(st.top(), num);
            st.pop();
            st.push(num);
        }
    }
    return st.top();
}
