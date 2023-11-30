#include <bits/stdc++.h>
using namespace std;
// unordered_set<vector<int>> rSide = {{1, 5, 6, 2}, {}};
map<vector<int>, char> Side = {{{1, 5, 6, 2}, 'R'}, {{5, 6, 2, 1}, 'R'}, {{6, 2, 1, 5}, 'R'}, {{2, 1, 5, 6}, 'R'}, {{0, 1, 2, 3}, 'U'}, {{1, 2, 3, 0}, 'U'}, {{2, 3, 0, 1}, 'U'}, {{3, 0, 1, 2}, 'U'}, {{2, 6, 7, 3}, 'F'}, {{6, 7, 3, 2}, 'F'}, {{7, 3, 2, 6}, 'F'}, {{3, 2, 6, 7}, 'F'}, {{0, 4, 5, 1}, 'B'}, {{4, 5, 1, 0}, 'B'}, {{5, 1, 0, 4}, 'B'}, {{1, 0, 4, 5}, 'B'}, {{0, 3, 7, 4}, 'L'}, {{3, 7, 4, 0}, 'L'}, {{7, 4, 0, 3}, 'L'}, {{4, 0, 3, 7}, 'L'}, {{4, 7, 6, 5}, 'D'}, {{7, 6, 5, 4}, 'D'}, {{6, 5, 4, 7}, 'D'}, {{5, 4, 7, 6}, 'D'}};
map<vector<int>, string> sol1;
map<char, int> Orientation = {{'R', 1}, {'U', 3}, {'F', -2}, {'B', 2}, {'L', -1}, {'D', -3}};
unordered_map<char, vector<vector<int>>> Move = {{'R', {{1, 5, 6, 2}, {3, 2, -3, -2}}}, {'U', {{0, 1, 2, 3}, {2, 1, -2, -1}}}, {'F', {{2, 6, 7, 3}, {3, 1, -3, -1}}}, {'B', {{0, 4, 5, 1}, {1, 3, -1, -3}}}, {'L', {{0, 3, 7, 4}, {2, 3, -2, -3}}}, {'D', {{4, 7, 6, 5}, {1, 2, -1, -2}}}};
vector<vector<map<int, int>>> manhattenDistance = {
    {{{3, 0}, {}}},
    {{}},
    {{}},
    {{}},
    {{}},
    {{}},
    {{}},
    {{}},
};
int find(vector<int> arr, int num, int n)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == num)
            return i;
    return -1;
}
vector<int> conv(vector<vector<int>> position)
{
    vector<int> v;
    for (auto i : position)
        for (auto j : i)
            v.push_back(j);
    return v;
}
vector<vector<int>> Turn(vector<vector<int>> position, char a)
{
    for (int i = 0; i < 8; i++)
        if (find(Move[a][0], position[i][0], 4) != -1)
        {
            position[i][0] = Move[a][0][(find(Move[a][0], position[i][0], 4) + 1) % 4];
            if (abs(position[i][1]) != abs(6 - Move[a][1][0] - Move[a][1][1]))
                position[i][1] = Move[a][1][(find(Move[a][1], position[i][1], 4) + 1) % 4];
        }
    return position;
}
vector<vector<int>> Execute(vector<vector<int>> position, string s)
{
    for (auto i : s)
        position = Turn(position, i);
    return position;
}
// bool checkSidePosSame()
// bool check
bool isSolved(vector<vector<int>> position)
{
    vector<int> upPos = {position[0][0], position[1][0], position[2][0], position[3][0]}, downPos = {position[4][0], position[7][0], position[6][0], position[5][0]}, rightPos = {position[1][0], position[5][0], position[6][0], position[2][0]};
    if (!(Side.count(upPos) && Side.count(downPos) && Side.count(rightPos)))
        return false;
    for (int i = 0; i < 4; i++)
        if (position[i][1] != Orientation[Side[upPos]])
            return false;
    for (int i = 4; i < 8; i++)
        if (position[i][1] != Orientation[Side[downPos]])
            return false;
    return true;
}
void printPos(vector<vector<int>> position)
{
    cout << "{{" << position[0][0] << "," << position[0][1] << "}";
    for (int i = 1; i < 8; i++)
        cout << ",{" << position[i][0] << "," << position[i][1] << "}";
    cout << "}\n";
}
pair<vector<string>, int> alg(string moves)
{
    int steps = 0;
    stack<pair<char, int>> s;
    vector<string> v = {"", "", "2", "'"}, result;
    for (auto i : moves)
    {
        if (s.empty() || s.top().first != i)
            s.push({i, 1});
        else
        {
            auto x = s.top();
            s.pop();
            if (get<1>(x) != 3)
                s.push({get<0>(x), (get<1>(x) + 1) % 4});
        }
    }
    while (!s.empty())
    {
        auto x = s.top();
        if (get<1>(x))
            result.insert(begin(result), get<0>(x) + v[get<1>(x)]);
        steps += get<1>(x);
        s.pop();
    }
    return {result, steps};
}
vector<int> convert(vector<vector<int>> position)
{
    vector<int> temp;
    for (auto i : position)
        for (auto j : i)
            temp.push_back(j);
    return temp;
}
int heuristicVal(vector<vector<int>> position)
{
    int val = 0;
    for (int i = 0; i < 8; i++)
        val += abs(position[i][0] - i) + abs(position[i][1]) == 3 ? 0 : 1;
    return val;
}
struct comp
{
    bool operator()(vector<vector<int>> a, vector<vector<int>> b)
    {
        return a != b;
    }
};
struct lol
{
    bool operator()(tuple<vector<vector<int>>, string, int> a, tuple<vector<vector<int>>, string, int> b)
    {
        return get<2>(a) > get<2>(b);
    }
};
string revAlgo(string s)
{
    string result = "";
    for (auto i : s)
        for (int j = 0; j < 3; j++)
            result += i;
    reverse(result.begin(), result.end());
    return result;
}
pair<string, string> func()
{
    vector<vector<int>> pos = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, -3}, {5, -3}, {6, -3}, {7, -3}};
    queue<pair<vector<vector<int>>, string>> q;
    vector<string> op = {"R", "U", "F"};
    q.push({pos, ""});
    while (q.front().second.length() < 10)
    {
        auto x = q.front();
        q.pop();
        for (auto i : op)
        {
            vector<vector<int>> temp = Execute(x.first, i);
            if (sol1.count(conv(temp)))
                return {sol1[conv(temp)], x.second + i};
            q.push({temp, x.second + i});
        }
    }
}
int main()
{
    int num = 1;
    string input;
    cin >> input;
    vector<vector<int>> position = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, -3}, {5, -3}, {6, -3}, {7, -3}}, solvePos = position;
    position = Execute(position, input);
    queue<pair<vector<vector<int>>, string>> q;
    q.push({position, ""});
    sol1[conv(position)] = "";
    vector<string> op = {"R", "U", "F"};
    for (auto i : alg(input).first)
        cout << i << " ";
    cout << endl;
    while (q.front().second.length() < 10)
    {
        auto x = q.front();
        q.pop();
        // cout << num++ << " -> " << x.second << " -> ";
        // printPos(x.first);
        for (auto i : op)
        {
            vector<vector<int>> temp = Execute(x.first, i);
            if (!sol1.count(conv(temp)) || alg(sol1[conv(temp)]).first.size() > alg(x.second + i).first.size())
            {
                sol1[conv(temp)] = x.second + i;
                q.push({temp, x.second + i});
            }
        }
    }
    auto x = func();
    vector<string> formula = alg(x.first + revAlgo(x.second)).first;
    for (auto i : formula)
        cout << i << " ";
    // cout<<formula.size();
    // cout << x.first << "  -  " << x.second;
    // cout << "done";

    // cout<<x.first.size();
}