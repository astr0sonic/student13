#include "calculator.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

bool check(const std::string expr)
{
    int k = 0, i = 0;
    char pred = ' ', ppred = ' ', cur = ' ';
    std::vector<char> sgn = { '+', '-', '*', '/', '^' };
    while (size(expr))
    {
        cur = expr[i];
        i++;
        if (find(sgn.begin(), sgn.end(), cur) == sgn.end() && cur != '(' && cur != ')' && cur != '.' && !isdigit(cur))
            return false;
        if (pred == '(' && (find(sgn.begin(), sgn.end(), cur) == sgn.end() && cur != '(' && cur != ')'))
            return false;
        if (cur == ')')
        {
            if (find(sgn.begin(), sgn.end(), pred) == sgn.end() && pred != '(' && pred != ')')
                return false;
            k++;
        }
        else if (cur == '(')
            k--;
        if (k < 0)
            return false;
        if (find(sgn.begin(), sgn.end(), cur) != sgn.end() && find(sgn.begin(), sgn.end(), pred) != sgn.end())
            return false;
        if ((!isdigit(ppred) || !isdigit(cur)) && pred == '.')
            return false;
        ppred = pred;
        pred = cur;
    }
    if (k != 0 || cur == '.' || find(sgn.begin(), sgn.end(), cur) != sgn.end())
        return false;
    return true;
}
double number(std::string expr, double p, int& i)
{
    i++;
    double n = p, t = 0;
    if (p == -1)
        n = 0;
    while (i < size(expr) && (isdigit(expr[i]) || expr[i] == '.'))
    {
        if (isdigit(expr[i]) && !t)
            n = n * 10.0 + (expr[i] - '0');
        else if (expr[i] == '.')
            t = 10.0;
        else
        {
            n += (expr[i] - '0') / t;
            t *= 10.0;
        }
        i++;
    }
    i--;
    if (p == -1)
        n *= -1;
    return n;
}
double calculator(const std::string& expr, int& i)
{
    std::vector<char> zn;
    std::vector<double> nm;
    while (i < size(expr) && expr[i] != ')')
    {
        if (expr[i] == '(')
        {
            i++;
            nm.push_back(calculator(expr, i));
        }
        else if (isdigit(expr[i]))
            nm.push_back(number(expr, expr[i] - '0', i));
        else if (expr[i] == '+' or expr[i] == '*' or expr[i] == '/' or expr[i] == '^')
            zn.push_back(expr[i]);
        else if (expr[i] == '-' && i > 0 && (isdigit(expr[i - 1]) || expr[i - 1] == ')' || expr[i - 1] == ' '))
            zn.push_back(expr[i]);
        else if (expr[i] == '-')
            nm.push_back(number(expr, -1, i));
        i++;
    }
    while (find(zn.begin(), zn.end(), '^') != zn.end())
    {
        int ind = find(zn.begin(), zn.end(), '^') - zn.begin();
        nm[ind] = pow(nm[ind], nm[ind + 1]);
        nm.erase(nm.begin() + ind + 1);
        zn.erase(zn.begin() + ind);
    }
    while (find(zn.begin(), zn.end(), '*') != zn.end() || find(zn.begin(), zn.end(), '/') != zn.end())
    {
        int ind1 = find(zn.begin(), zn.end(), '*') - zn.begin();
        int ind2 = find(zn.begin(), zn.end(), '/') - zn.begin();
        if (ind1 < ind2)
            nm[ind1] = nm[ind1] * nm[ind1 + 1];
        else
        {
            nm[ind2] = nm[ind2] / nm[ind2 + 1];
            ind1 = ind2;
        }
        nm.erase(nm.begin() + ind1 + 1);
        zn.erase(zn.begin() + ind1);
    }
    while (find(zn.begin(), zn.end(), '+') != zn.end() || find(zn.begin(), zn.end(), '-') != zn.end())
    {
        int ind1 = find(zn.begin(), zn.end(), '+') - zn.begin();
        int ind2 = find(zn.begin(), zn.end(), '-') - zn.begin();
        if (ind1 < ind2)
            nm[ind1] = nm[ind1] + nm[ind1 + 1];
        else
        {
            nm[ind2] = nm[ind2] - nm[ind2 + 1];
            ind1 = ind2;
        }
        nm.erase(nm.begin() + ind1 + 1);
        zn.erase(zn.begin() + ind1);
    }
    return nm[0];
}
double calculate(const std::string& expr)
{
    int i = 0;
    std::string expr_copy = expr;
    expr_copy.erase(remove_if(expr_copy.begin(), expr_copy.end(), isspace), expr_copy.end());
    if (check(expr_copy))
        return calculator(expr_copy, i);
    else
        throw std::logic_error("syntax error");
}