#include <bits/stdc++.h>
using namespace std;
string notations(int n)
{
    switch (n)
    {
    case 1:
        return "";
    case 2:
        return "2";
    case 3:
        return "'";
    }
}
vector<string> convert(string input)
{
    stack<char> temp;
    vector<string> result;
    input += " ";
    for (int i = 0; i < input.length(); i++)
    {
        if (temp.empty() || temp.top() == input[i])
            temp.push(input[i]);
        else
        {
            int n = 0;
            char x = temp.top();
            while (!temp.empty() && temp.top() == x)
            {
                n++;
                temp.pop();
            }
            for (int i = 0; i < n % 4; i++)
                temp.push(x);
            temp.push(input[i]);
        }
    }
    while (!temp.empty())
    {
        int n = 0;
        char x = temp.top();
        while (!temp.empty() && temp.top() == x)
        {
            n++;
            temp.pop();
        }
        result.push_back(x + notations(n));
    }
    reverse(result.begin(), result.end());
    result.pop_back();
    return result;
}
int main()
{
    string x;
    cin >> x;
    vector<string> temp = convert(x);
    for (auto i : temp)
        cout << i << ' ';
}