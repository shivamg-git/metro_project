#include<bits/stdc++.h>
#include<fstream>
#define ll long long
#define fi first
#define se second
using namespace std;
map<string,ll> M;
map<string,ll> ::iterator it;
int main()
{
	ifstream fin;
	string s;
	fin.open("list2.txt",ios::in);
	ll l=0;
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		//fin>>s;
		//cout<<s<<endl;
		M[s]=l++;
	}
	for(it=M.begin();it!=M.end();it++)
		cout<<it->se<<" "<<it->fi<<endl;
}
