#include<bits/stdc++.h>
#include<fstream>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
map<string,ll>M;
char color[200][200]={'\0'};
class comparedis
{
	public:bool operator()(pair<ll,ll> &p,pair<ll,ll> &q)
		{
			return (p.se > q.se); // For min heap use > sign
		}
};
vector< pair<ll,ll> > v[100010];//Adjacency matrix
ll N;// N is no of vertices M is edges
string station[200];
//Given below code will print the path
void disp(ll src,ll dest,ll par[])
{
	ll i,x,y;
	stack<ll> st;
	st.push(dest);
	i=dest;
	while(par[i]!=-1)
	{
		i=par[i];
		st.push(i);				
	}
	char col='\0';
	while(!st.empty())
	{
		x=st.top();
		st.pop();
		if(!st.empty())
			y=st.top();
		cout<<station[x]<<" ";
		if(col=='\0')
			col=color[x][y];
		else if(col!='\0'&&col!=color[x][y])
		{
			char c=color[x][y];
			if(c=='b')
				cout<<"\t\tChange to blue line";
			else if(c=='y')
				cout<<"\t\tChange to yellow line";
			else if(c=='o')
				cout<<"\t\tChange to orange line";
			else if(c=='g')
				cout<<"\t\tChange to green line";
			else if(c=='r')
				cout<<"\t\tChange to red line";
			col=c;
		}		
		cout<<endl;
	}
	cout<<endl;
}
//To find shotest path
void bfs(ll src,ll dest) 
{
	bool vis[100010]={false};
	ll par[100010];
	for(ll i=0;i<N;i++)
		par[i]=-1;
	queue<ll> q;
	q.push(src);
	vis[src]=true;
	while(!q.empty())
	{
		ll x=q.front();
		q.pop();
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			if(!vis[y])
			{
				par[y]=x;
				vis[y]=true;
				q.push(y);
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
}
//To find most economical path
void dijkstra(ll src,ll dest)
{
	bool vis[100010]={false};
	ll dist[100010], par[100010];
	for(ll i=0;i<N;i++)
	{
		dist[i]=LLONG_MAX;
		par[i]=-1;
	}
	priority_queue< pair<ll,ll>,vector< pair<ll,ll> >,comparedis > pq;
	pq.push(mp(src,0));
	dist[src]=0;
	par[src]=-1;
	vis[src]=true;
	while(!pq.empty())
	{
		pair<ll,ll> k=pq.top();
		pq.pop();
		ll x=k.fi;
		//if(x==dest)
		//	break;
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			ll w=v[x][i].se;
			if(dist[x]+w < dist[y])
			{
				par[y]=x;
				dist[y]=dist[x]+w;
			}
			if(!vis[y])
			{
				vis[y]=true;
				pq.push(mp(y,dist[y]));
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
}
void consmap()//To assign values to metro stations
{
	ifstream fin;
	string s;
	fin.open("list.txt",ios::in);
	ll l=0;
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		M[s]=l;
		station[l]=s;
		l++;
	}
	N=l-1;
	fin.close();
	map<string,ll> ::iterator it;
	//for(it=M.begin();it!=M.end();it++)
	//	cout<<it->se<<" "<<it->fi<<endl;
}
void addedge(char fname[],ll w)//To add edges
{
	ifstream fin;
	string s;
	ll x,y;
	fin.open(fname,ios::in);
	fin.seekg(0);
	getline(fin,s);
	x=M[s];
	char c=fname[0];
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		y=M[s];
		v[x].pb(mp(y,w));
		v[y].pb(mp(x,w));
		color[x][y]=c;
		color[y][x]=c;
		x=y;
	}
	fin.close();
}
void consgraph()//To construct edges
{
	string s;
	addedge("blueline.txt",0);
	addedge("yellowline.txt",0);
	addedge("redline.txt",0);
	addedge("greenline.txt",0);
	addedge("violetline.txt",0);
	addedge("bluext.txt",0);
	addedge("orangeline.txt",1);
}
int main()
{
	string source,destination;
	ll i,x,y,w,src,dest,k,choice;
	consmap();
	consgraph();
	getline(cin,source);
	//cout<<source<<endl;
	getline(cin,destination);
	//cout<<destination<<endl;
	src=M[source];
	dest=M[destination];
	//cout<<src<<dest<<endl;
	//cin>>src>>dest;
	cout<<"1.For most economic path\n";
	cout<<"2.For shortest path";
	cin>>choice;
	switch(choice)
	{
		case 1:dijkstra(src,dest);
				break;
		case 2:bfs(src,dest);
				break;
	}			
	return 0;
}