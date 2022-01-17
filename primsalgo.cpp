#include<bits/stdc++.h>

using namespace std;

int find(vector<char> s,char a){
	for(int i=0;i<s.size();i++){
		if(s[i]==a)
			return i;
	}
	return -1;
}

class edge{
	public:
	int s;
	int second;
	int d;
};

void swap(edge *a,edge *b){
	edge t=*a;
	*a=*b;
	*b=t;
}

class heap{
	edge *h;
	int r;
	int size;
	public:
	heap(int n){
		h=(edge *)malloc(n*sizeof(edge));
		size=n;
		r=-1;
	}
	void heapify(int k){
		int rc=k*2+2;
		int lc=k*2+1;
		int t=k;
		if(k>=r)
			return;
		if( lc<=r and h[k].second>h[lc].second)
			t=lc;
		if(rc<=r and h[k].second>h[rc].second)
			t=rc;
		
		if(t!=k){
			swap(&h[t],&h[k]);
			k=t;
			heapify(k);				
		}
	
	}
	
	void insert(edge x){
		
		if(r==-1){
			h[++r]=x;
		//	cout<<"hh"<<endl;
			return;
		}
		if(r==size-1)
			return;
		int k=r/2;
		h[++r]=x;
		do{
			heapify(k);
			k=(k-1)/2;	
		}while(k);
		 heapify(k);
	}
	edge extract_min(){
		edge ret;
		if(r==0){
			ret=h[0];
			r=-1;
			return ret;
		}
		ret=h[0];
		swap(&h[r],&h[0]);
		r--;
		heapify(0);
		return ret;
	}

	bool empty(){
		if(r==-1)
			return true;
		return false;
	}
	
};
class graph{
	int v=0;
	int **G;
	vector<char> vset;
	public:

	graph(int n){
		v=n;
		G=(int**)malloc(n*sizeof(int*));
	}
	void add_vertex_set(vector<char> &a){
		vset=a;
	}
	void in(int **a){
		G=a;
	}
	void show(){
		int n=v;
		cout<<"-----THE adjacency Matrix-----"<<endl;
		for(int i=0;i<n;i++)
			cout<<vset[i]<<" ";
		cout<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				cout<<G[i][j]<<" ";
			cout<<endl;
		}
		cout<<"------------------------------"<<endl;		
	}
	graph prims(){
		int **a=(int**)malloc(v*sizeof(int *));
		for(int i=0;i<v;i++){
			int *f=(int*)malloc(v*sizeof(int ));
			for(int j=0;j<v;j++)
				f[j]=0;
			*(a+i)=f;
		}
		char o;
		cout<<"Enter root-";
		cin>>o;
		int ai=find(vset,o);
		bool visit[v];
		for(int h=0;h<v;h++)
			visit[h]=false;
		visit[ai]=true;		
		heap pq=heap(v*v);
		int c=0;
		vector<int> eset;
		while(c!=v-1){
			for(int i=0;i<v;i++){
				if(G[ai][i] && !visit[i]){
					edge t;
					t.s=ai;
					t.second=G[ai][i];
					t.d=i;
					pq.insert(t);
				}
			}
			//pq.show();
			if(!pq.empty()){
				edge t=pq.extract_min();

			
				a[t.s][t.d]=t.second;
				a[t.d][t.s]=t.second;
				eset.push_back(t.second);
				c++;
				visit[t.d]=true;
				ai=t.d;					
			}
			

			
		}
		vector<char> k;
		for(int i=0;i<v;i++)
			k.push_back(vset[i]);
		graph A=graph(v);
		A.add_vertex_set(k);
		A.in(a);
		return A;
	}

};
graph read_file(){
	int n;
	fstream g;
	g.open("GRAPH.txt",ios::in);
	g>>n;
	graph A=graph(n);
	vector<char> k;
	for(int i=0;i<n;i++){
		char f;
		g>>f;
		k.push_back(f);
	}
	A.add_vertex_set(k);	
	int **a=(int **)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++){
		int *f=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++)
			g>>f[j];
		*(a+i)=f;
	}

	A.in(a);	
	
	return A;
	}
int main(void){
	graph g=read_file();
	g.show();
	graph A=g.prims();
	A.show();
}
