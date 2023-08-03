#include<iostream>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
map<char,vector<vector<int>>> Move =  {{'R',{{1,5,6,2},{3,2,-3,-2}}},{'U',{{0,1,2,3},{2,1,-2,-1}}},{'F',{{2,6,7,3},{3,1,-3,-1}}},{'B',{{0,4,5,1},{1,3,-1,-3}}}};
int main()
{
    for(int i=0;i<2;i++)
    for(int j=0;j<4;j++)
    cout<<Move['R'][i][j];
}