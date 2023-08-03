#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
map<int,string> CONV={{1,""},{2,"2"},{3,"'"}};
// bool check(vector<char> temp,int x, int y)
// {
//     set<char> a;
//     for(int i=x;i<=y;i++)
//     a.insert(temp[i]);
//     if(a.size()==1)
//     return true;
//     return false;
// }
// string refine(string s)
// {
//     vector<char> temp;
//     for(int i=0;i<s.length();i++)
//     temp.push_back(s[i]);
//     int a=0;
//     for(int i=3;i<temp.size()-1;i++)
//     if(check(temp,a,i))
//     {
//         temp.erase(temp.begin()+a,temp.begin()+i)
//     }

// }
int main()
{
    // string Feed="RUUUURRR";
    // Feed=" "+Feed+" ";
    // vector<string> Alg;
    // int a=0;
    // for(int i=0;i<Feed.length()-1;i++)
    // {
    //     if(Feed[i]!=Feed[i+1])
    //     {
    //         int temp=i-a;
    //         a=i;
    //         if(temp%4==0)
    //         continue;
    //         Alg.push_back(Feed[i]+CONV[temp%4]);
    //     }
    // }
    // for(int i=0;i<Alg.size();i++)
    // cout<<Alg[i]<<" ";
    string Feed="RRRR";
    Feed=" "+Feed+" ";
    string Alg="";
    int a=0;
    for(int i=0;i<Feed.length()-1;i++)
    {
        if(Feed[i]!=Feed[i+1])
        {
            int temp=i-a;
            a=i;
            if(temp%4==0)
            continue;
            for(int j=0;j<temp;j++)
            Alg=Alg+Feed[a];
        }
    }
    for(int i=0;i<Alg.length();i++)
    cout<<Alg[i]<<" ";
}