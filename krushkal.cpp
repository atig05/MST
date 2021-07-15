#include<bits/stdc++.h>
#include "disjoint_set_rank.cpp"
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
	char s;
	char d;
	int w;
	edge(char a,char b,int x){
		s=a;
		d=b;
		w=x;
	}
	void showe( ){
		cout<<s<<d<<"-"<<w<<endl;
	}
};

void swap(edge *a,edge* b){
	edge t=*a;
	*a=*b;
	*b=t;
}
int partition(edge *a,int i,int n){
	
	int pi=i;
	int l=i;
	int r=n;

	while(l<r){
	
		
		while(a[++l].w<a[pi].w){
			
		}
		
		while(a[r].w>a[pi].w &&r>0){
			r--;
		}
		
		if(l>=r)
			break;
			
		else{
			swap(&a[l],&a[r]);
		}
				
	
	}
	//if(l=r)
//	if(l)	
	swap(&a[r],&a[pi]);	
	return r;
}
void quick(edge *a,int i,int r){
	
	if(i>=r)
		return;
	int m=partition(a,i,r);
//	cout<<"m-- "<<m<<" i- "<<i<<endl;
	quick(a,i,m-1);
	quick(a,m+1,r);
}

class graph{
	int **G;
	public:
	vector<char> vset;
	int v;
	vector<edge> eset;
	
	graph(int n){
		G=(int**)malloc(sizeof(int*)*n);
		//eset=(edge*)malloc(sizeof(edge)*n);
		v=n;
	}
	void insert_vset(vector<char> k,int n){
		for(int i=0;i<n;i++)
			vset.push_back(k[i]);
	}
	void show(){
		int n=vset.size();
		for(int i=0;i<vset.size();i++)
			cout<<" "<<vset[i];
		cout<<endl;
		for(int i=0;i<n;i++){
			cout<<vset[i];
			for(int j=0;j<n;j++)
				cout<<" "<<G[i][j];
			cout<<endl;
		}
	}
	void show_edge_set(){
		for(int i=0;i<eset.size();i++){
			cout<<eset[i].s<<eset[i].d<<"-"<<eset[i].w<<endl;
		}
	}

	void in(int **a){
		int k=0;
		for(int i=0;i<v;i++){
			int *f=(int *)malloc(v*sizeof(int));
			for(int j=0;j<v;j++){
				f[j]=a[i][j];

					
			}
				*(G+i)=f;
		}
		for(int i=0;i<v;i++){
			for(int j=i+1;j<v;j++){
				if(a[i][j]!=0){
					edge e=edge(vset[i],vset[j],a[i][j]);
					eset.push_back(e);
				}
			}
		}
	}	
	void show_vertex(){
		for(int i=0;i<vset.size();i++)
			cout<<vset[i]<<" ";
		cout<<endl;
	}
	graph krushkal(){
		graph k=graph(v);
		k.insert_vset(vset,v);
		int n=eset.size();
		edge *eseta=(edge*)malloc(n*sizeof(edge));
		for(int i=0;i<n;i++)
			eseta[i]=eset[i];
		quick(eseta,0,n-1);
		int **a=(int**)malloc(v*sizeof(int*));
		for(int i=0;i<v;i++){
			int *f=(int *)malloc(v*sizeof(int));
			for(int j=0;j<v;j++)
				f[j]=0;
			*(a+i)=f;
		}		
		int c=0;
		disjoint_set_rank set=disjoint_set_rank(v);
		for(int i=0;i<eset.size();i++){
		

			if(c==0){
				c++;
				a[find(vset,eseta[i].s)][find(vset,eseta[i].d)]=eseta[i].w;
				a[find(vset,eseta[i].d)][find(vset,eseta[i].s)]=eseta[i].w;
				set.union_(find(vset,eseta[i].s),find(vset,eseta[i].d));
			}
			else if(set.find(find(vset,eseta[i].s))!=set.find(find(vset,eseta[i].d))){
				c++;
				a[find(vset,eseta[i].s)][find(vset,eseta[i].d)]=eseta[i].w;
				a[find(vset,eseta[i].d)][find(vset,eseta[i].s)]=eseta[i].w;
				set.union_(find(vset,eseta[i].s),find(vset,eseta[i].d));				
			}
			
			if(c==v-1)
				break;
				
		}
		k.in(a);
		return k;
	}
};
graph read_file(){
	int n;
	fstream g;
	g.open("GRAPH.txt",ios::in);
	g>>n;
	vector<char> k;
	for(int i=0;i<n;i++){
		char h;
		g>>h;
		k.push_back(h);
	}
		
	
	graph A=graph(n);
	A.insert_vset(k,n);
	int **a=(int **)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++){
		int *f=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++)
			g>>f[j];
		*(a+i)=f;
	}

	A.in(a);	
	//A.show();
	return A;
	}
int main(void){
	graph g=read_file();
	g.show();
	g.show_edge_set();
	graph k=g.krushkal();
	cout<<"MST is"<<endl;
	k.show();
	k.show_edge_set();
}
