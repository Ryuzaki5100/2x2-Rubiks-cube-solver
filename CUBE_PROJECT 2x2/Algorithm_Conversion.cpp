#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
string process(char ch, int n) // This function converts a character with 'n' repetitions into proper notations --> for instance, {R}-->{R}, {R,R}-->{R2}, {R,R,R}-->{R'}, {R,R,R,R}-->{}
{
    string temp = "";
    temp = temp + ch;
    n = n % 4;
    if (n == 1)
        return temp;
    else if (n == 2)
    {
        temp = temp + "2";
        return temp;
    }
    else if (n == 3)
    {
        temp = temp + "'";
        return temp;
    }
    return "";
}
int main()
{
    vector<char> Feed = {'U','U','U','U','R'};
    vector<string> Algorithm;
    vector<char>::iterator a, b;
    for (a = Feed.begin(), b = Feed.begin(); b != Feed.end() + 1; b++)
    {
        if (b == Feed.end() && (*a == *b) && ((b - a) % 4 != 0))
        {
            Algorithm.push_back(process(*a, b - a));
            break;
        }
        else if (*a != *b && ((b - a) % 4 != 0))
        {
            Algorithm.push_back(process(*a, b - a));
            a = b;
        }
    }
    for (int i = 0; i < Algorithm.size(); i++)
    {
        cout << Algorithm[i];
        if (i != Algorithm.size() - 1)
            cout << " - ";
    }
}