#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int mod(int n) { return n > 0 ? n : -n; }
string Result = "";
map<int, string> CONV = {{1, ""}, {2, "2"}, {3, "'"}};
map<int, string> AUF = {{0, ""}, {1, "U"}, {2, "UU"}, {3, "UUU"}};
map<int, string> HEADLINE = {{0, ""}, {1, "UUU"}, {2, "UU"}, {3, "U"}};
map<int, string> OPSIDE = {{-2, "RRRDRDDDRRRDRDDD"}, {1, "RRRDRDDDRRRDRDDDRRRDRDDDRRRDRDDD"}, {3, ""}};
map<int, string> FrontCase = {{0, "UU"}, {1, "U"}, {3, "UUU"}, {4, "L"}, {5, "B"}, {6, "RURRR"}, {7, "LLL"}};
map<int, string> BackCase = {{4, "LLL"}, {5, "BBB"}, {6, ""}, {7, "L"}};
map<vector<int>, string> ALG = {{{2, -2}, "URUUURRR"}, {{2, 3}, "RUURRRUUURURRR"}, {{2, 1}, "RURRR"}};
map<char, vector<vector<int>>> Move = {{'R', {{1, 5, 6, 2}, {3, 2, -3, -2}}}, {'U', {{0, 1, 2, 3}, {2, 1, -2, -1}}}, {'F', {{2, 6, 7, 3}, {3, 1, -3, -1}}}, {'B', {{0, 4, 5, 1}, {1, 3, -1, -3}}}, {'L', {{0, 3, 7, 4}, {2, 3, -2, -3}}}, {'D', {{4, 7, 6, 5}, {1, 2, -1, -2}}}};
int find(vector<int> arr, int num, int n)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == num)
            return i;
    return -1;
}
int ReturnSlot(vector<vector<int>> position)
{
    for (int i = 0; i < 4; i++)
        if (position[i][0] == 2)
            return i;
}
vector<vector<int>> Turn(vector<vector<int>> position, char a)
{
    for (int i = 0; i < 8; i++)
        if (find(Move[a][0], position[i][0], 4) != -1)
        {
            position[i][0] = Move[a][0][(find(Move[a][0], position[i][0], 4) + 1) % 4];
            if (mod(position[i][1]) != mod(6 - Move[a][1][0] - Move[a][1][1]))
                position[i][1] = Move[a][1][(find(Move[a][1], position[i][1], 4) + 1) % 4];
        }
    return position;
}
vector<vector<int>> Execute(vector<vector<int>> position, string s)
{
    Result = Result + s;
    for (int i = 0; i < s.length(); i++)
        position = Turn(position, s[i]);
    return position;
}
vector<vector<int>> Perform_first_layer(vector<vector<int>> position, int i)
{
    if (position[i][0] == 2)
        return Execute(position, ALG[position[i]] + "DDD");
    else if (position[i][0] / 4 == 0)
    {
        position = Execute(position, FrontCase[position[i][0]]);
        position = Execute(position, ALG[position[i]] + "DDD");
        return position;
    }
    else
    {
        int temp = position[i][0];
        position = Execute(position, FrontCase[position[i][0]]);
        position = Execute(position, FrontCase[position[i][0]]);
        position = Execute(position, ALG[position[i]]);
        position = Execute(position, BackCase[temp] + "DDD");
        return position;
    }
}
vector<vector<int>> Perform_OPcolor(vector<vector<int>> position)
{
    int i = ReturnSlot(position);
    position = Execute(position, OPSIDE[position[i][1]] + "U");
    return position;
}
vector<int> Headline_stats(vector<vector<int>> position)
{
    vector<int> count = {0, 0};
    for (int i = 0; i < 4; i++)
        if (position[(i + 1) % 4][0] - position[i][0] == 1)
        {
            count[0]++;
            count[1] = i;
        }
    return count;
}
vector<vector<int>> Perform_Headline(vector<vector<int>> position)
{
    vector<int> stats = Headline_stats(position);
    if (stats[0] == 1)
    {
        position = Execute(position, HEADLINE[position[stats[1]][0]] + "RRRFRRRBBRFFFRRRBBRR");
        return position;
    }
    else if (stats[0] == 0)
    {
        position = Execute(position, "RRRFRRRBBRFFFRRRBBRR");
        position = Execute(position, HEADLINE[position[Headline_stats(position)[1]][0]] + "RRRFRRRBBRFFFRRRBBRR");
        return position;
    }
    else
    {
        position = Execute(position, "");
        return position;
    }
}
void Print_Res()
{
    Result = " " + Result + " ";
    vector<string> Alg;
    int a = 0;
    for (int i = 0; i < Result.length() - 1; i++)
    {
        if (Result[i] != Result[i + 1])
        {
            int temp = i - a;
            a = i;
            if (temp % 4 == 0)
                continue;
            Alg.push_back(Result[i] + CONV[temp % 4]);
        }
    }
    cout << " - ";
    for (int i = 0; i < Alg.size(); i++)
        cout << Alg[i] << " - ";
    cout << endl;
    Result = "";
}
int main()
{
    vector<vector<int>> position = {{4,2},{0,2},{6,-3},{1,2},{7,-1},{3,3},{5,1},{2,3}};
    // for(int i=0;i<8;i++)
    // for(int j=0;j<2;j++)
    // cin>>position[i][j];
    for (int i = 0; i < 8; i++)
    {
        cout << "{ ";
        for (int j = 0; j < 2; j++)
            cout << position[i][j] << " ";
        cout << "}  ";
    }
    cout << endl;
    for (int i = 7; i >= 4; i--)
    {
        position = Perform_first_layer(position, i);
        Print_Res();
    }
    for (int i = 0; i < 4; i++)
    {
        position = Perform_OPcolor(position);
        Print_Res();
    }
    position = Perform_Headline(position);
    Print_Res();
    position = Execute(position, AUF[(position[4][0] - position[0][0]) % 4]);
    Print_Res();
    for (int i = 0; i < 8; i++)
    {
        cout << "{ ";
        for (int j = 0; j < 2; j++)
            cout << position[i][j] << " ";
        cout << "}  ";
    }
}