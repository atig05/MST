#include<bits/stdc++.h>
#define For(i , n) for(int i=0;i<n;i++)
using namespace std;
class disjoint_set_rank{
	int *parent;
	int *rank;
	public:
	disjoint_set_rank(int n){
		parent=(int*)malloc(n*sizeof(int));
		rank=(int*)malloc(n*sizeof(int));
		For(i , n){
			parent[i]=i;
			rank[i]=0;
		}
		
	}
	int find(int x){
		if(parent[x]==x)
			return x;
		find(parent[x]);		
	}
	void union_(int x,int y){
		if(find(x)==find(y))
			return;
		else if(rank[find(x)]==rank[find(y)]){
			parent[find(y)]=find(x);
			rank[find(x)]++;
		}
		else if(rank[find(x)]>rank[find(y)]){
			parent[y]=find(x);
		}
		else
			parent[x]=find(y);
	}
};

