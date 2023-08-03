#include<iostream>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
int mod(int n){return n>0?n:-n;}
string Result = "";
map<int,string> CONV={{1,""},{2,"2"},{3,"'"}};
map<int,string> AUF={{0,""},{1,"U"},{2,"UU"},{3,"UUU"}};
map<int,string> HEADLINE={{0,""},{1,"UUU"},{2,"UU"},{3,"U"}};
map<int,string> OPSIDE={{-2,"RRRDRDDDRRRDRDDD"},{1,"RRRDRDDDRRRDRDDDRRRDRDDDRRRDRDDD"},{3,""}};
map<int,string> FrontCase={{0,"UU"},{1,"U"},{3,"UUU"},{4,"L"},{5,"B"},{6,"RURRR"},{7,"LLL"}};
map<int,string> BackCase={{4,"LLL"},{5,"BBB"},{6,""},{7,"L"}};
map<vector<int>,string> ALG={{{2,-2},"URUUURRR"},{{2,3},"RUURRRUUURURRR"},{{2,1},"RURRR"}};
map<char,vector<vector<int>>> Move =  {{'R',{{1,5,6,2},{3,2,-3,-2}}},{'U',{{0,1,2,3},{2,1,-2,-1}}},{'F',{{2,6,7,3},{3,1,-3,-1}}},{'B',{{0,4,5,1},{1,3,-1,-3}}},{'L',{{0,3,7,4},{2,3,-2,-3}}},{'D',{{4,7,6,5},{1,2,-1,-2}}}};
int find(vector<int> arr,int num, int n)
{
    for(int i=0;i<n;i++)
    if(arr[i]==num)
    return i;
    return -1;
}
int ReturnSlot(vector<vector<int>> position)
{
    for(int i=0;i<4;i++)
    if(position[i][0]==2)
    return i;
}
vector<vector<int>> Turn(vector<vector<int>> position,char a)
{
    for(int i=0;i<8;i++)
    if(find(Move[a][0],position[i][0],4)!=-1)
    {
        position[i][0]=Move[a][0][(find(Move[a][0],position[i][0],4)+1)%4];
        if(mod(position[i][1])!=mod(6-Move[a][1][0]-Move[a][1][1]))
        position[i][1]=Move[a][1][(find(Move[a][1],position[i][1],4)+1)%4];
    }
    return position;
}
vector<vector<int>> Execute(vector<vector<int>> position, string s)
{
    Result=Result+s;
    for(int i=0;i<s.length();i++)
    position=Turn(position,s[i]);
    return position;
}
vector<vector<int>> Perform_first_layer(vector<vector<int>> position, int i)
{
    if(position[i][0]==2)
    return Execute(position,ALG[position[i]]+"DDD");
    else if(position[i][0]/4==0)
    {
        position=Execute(position,FrontCase[position[i][0]]);
        position=Execute(position,ALG[position[i]]+"DDD");
        return position;
    }
    else
    {
       int temp = position[i][0]; 
       position=Execute(position,FrontCase[position[i][0]]);
       position=Execute(position,FrontCase[position[i][0]]);
       position=Execute(position,ALG[position[i]]);
       position=Execute(position,BackCase[temp]+"DDD");
       return position; 
    }
}
vector<vector<int>> Perform_OPcolor(vector<vector<int>> position)
{
    int i=ReturnSlot(position);
    position=Execute(position,OPSIDE[position[i][1]]+"U");
    return position;
}
// string process(char ch, int n) // This function converts a character with 'n' repetitions into proper notations --> for instance, {R}-->{R}, {R,R}-->{R2}, {R,R,R}-->{R'}, {R,R,R,R}-->{}
// {
//     string temp = "";
//     temp = temp + ch;
//     n = n % 4;
//     if (n == 1)
//         return temp;
//     else if (n == 2)
//     {
//         temp = temp + "2";
//         return temp;
//     }
//     else if (n == 3)
//     {
//         temp = temp + "'";
//         return temp;
//     }
//     return "";
// }
// void Print_Res()
// {
//     if(Result.length()!=0)
//     {vector<char> Feed;
//     for(int i=0;i<Result.length();i++)
//     Feed.push_back(Result[i]);
//     vector<string> Algorithm;
//     vector<char>::iterator a, b;
//     for (a = Feed.begin(), b = Feed.begin(); b != Feed.end() + 1; b++)
//     {
//         if (b == Feed.end() && (*a == *b) && ((b - a) % 4 != 0))
//         {
//             Algorithm.push_back(process(*a, b - a));
//             break;
//         }
//         else if (*a != *b && ((b - a) % 4 != 0))
//         {
//             Algorithm.push_back(process(*a, b - a));
//             a = b;
//         }
//     }
//     for (int i = 0; i < Algorithm.size(); i++)
//     {
//         cout << Algorithm[i];
//         if (i != Algorithm.size() - 1)
//             cout << " - ";
//     }
//     cout<<endl;}
//     Result="";
// }
void Print_Res()
{
    Result=" "+Result+" ";
    vector<string> Alg;
    int a=0;
    for(int i=0;i<Result.length()-1;i++)
    {
        if(Result[i]!=Result[i+1])
        {
            int temp=i-a;
            a=i;
            if(temp%4==0)
            continue;
            Alg.push_back(Result[i]+CONV[temp%4]);
        }
    }
    for(int i=0;i<Alg.size();i++)
    cout<<Alg[i]<<" ";
    cout<<endl;
    Result="";
}
// vector<vector<int>> R(vector<vector<int>> position)
// {
//     vector<int> arr_pos[4]={1,5,6,2},arr_ori[4]={3,2,-3,-2};
//     for(int i=0;i<8;i++)
//     if(find(arr_pos,position[i][0],4)!=-1)
//     {
//         position[i][0]=arr_pos[(find(arr_pos,position[i][0],4)+1)%4];
//         if(position[i][0]!=1)
//         position[i][1]=arr_ori[(find(arr_ori,position[i][1],4)+1)%4];
//     }
//     return position;
// }
// vector<vector<int>> U(vector<vector<int>> position)
// {
//     vector<int> arr_pos[4]={0,1,2,3},arr_ori[4]={2,1,-2,-1};
//     for(int i=0;i<8;i++)
//     if(find(arr_pos,position[i][0],4)!=-1)
//     {
//         position[i][0]=arr_pos[(find(arr_pos,position[i][0],4)+1)%4];
//         if(position[i][0]!=3)
//         position[i][1]=arr_ori[(find(arr_ori,position[i][1],4)+1)%4];
//     }
//     return position;
// }
// vector<vector<int>> F(vector<vector<int>> position)
// {
//     vector<int> arr_pos[4]={2,6,7,3},arr_ori[4]={3,1,-3,-1};
//     for(int i=0;i<8;i++)
//     if(find(arr_pos,position[i][0],4)!=-1)
//     {
//         position[i][0]=arr_pos[(find(arr_pos,position[i][0],4)+1)%4];
//         if(position[i][0]!=-2)
//         position[i][1]=arr_ori[(find(arr_ori,position[i][1],4)+1)%4];
//     }
//     return position;
// }
vector<int> stats(vector<vector<int>> position)
{
    vector<int> stats;
    vector<int> pos;
    for(int i=0;i<4;i++)
    pos.push_back(position[i][0]);
    pos.push_back(pos[0]);
    for(int i=0;i<pos.size()-1;i++)
    if(pos[i+1]-pos[i]==1)
    stats.push_back(i);
    return stats;
}
int main()
{
    vector<vector<int>> position={{0,3},{1,3},{2,3},{3,3},{4,-3},{5,-3},{6,-3},{7,-3}};
    // for(int i=0;i<8;i++)
    // for(int j=0;j<2;j++)
    // cin>>position[i][j];
    for(int i=0;i<8;i++)
    {
        cout<<"{ ";
        for(int j=0;j<2;j++)
        cout<<position[i][j]<<" ";
        cout<<"}  ";
    }
    cout<<endl;
    position=Execute(position,"UUUU");
    vector<int> info = stats(position);
    for(int i=0;i<info.size();i++)
    cout<<info[i]<<" ";
    cout<<endl;
    for(int i=0;i<8;i++)
    {
        cout<<"{ ";
        for(int j=0;j<2;j++)
        cout<<position[i][j]<<" ";
        cout<<"}  ";
    }
}