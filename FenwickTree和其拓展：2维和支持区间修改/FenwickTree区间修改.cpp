/*

支持区间修改需要维护的是差分数组吧b[i]=a[i]-a[i-1];
而a[i]=sum(b[1]...b[i]);
同样sum(a[1]..a[n])=n*sum(b[1]..b[i])-sum(b[i]*(i-1)) 
*/

#include<cstdio>
#include<iostream>
using namespace std;
typedef int T;
class FenwickTree
{
	private:
		T *a;
		T *sum1;
		T *sum2;
		int size=0;
	public:
		FenwickTree(int size);
		~FenwickTree();
		
		void insert(int index,T key);
		void update(int index,T key);//单点修改
		void range_update(int left,int right,T key);//区间修改
		T get_sum(int left,int right);
		
	private:
		int lowbit(int x);
		T getsum(int index);
}; 
FenwickTree::FenwickTree(int size)
{
	this->size=size;
	a=new T[size+1];
	sum1 = new T[size+1];
	sum2 = new T[size+1];
	for(int i=0;i<=size;++i)
	{
		a[i]=0;sum1[i]=0;sum2[i]=0;
	}
}
FenwickTree::~FenwickTree()
{
	delete[] a;delete[] sum1;delete[] sum2;
}
int FenwickTree::lowbit(int x)
{
	return x&(-x);
}
void FenwickTree::insert(int index,T key)
{
	a[index]=key;
	update(index,a[index]-a[index-1]);
} 
void FenwickTree::update(int index,T key)
{
	for(int i=index;i<=size;i+=lowbit(i))
	{
		sum1[i]+=key;//维护前缀和b[i] 
		sum2[i]+=key*(index-1);//维护前缀和 b[i]*(n-1);
	}
}
void FenwickTree::range_update(int left,int right,T key)
{
	update(left,key);//差分序列只要在最左边加上就可以给区间加上 
	update(right+1,-key);//序列右边的需要减去 
}
T FenwickTree::getsum(int x)
{
	T res=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		res+=x*sum1[i]-sum2[i];
	}
	return res;
} 
T FenwickTree::get_sum(int left,int right)
{
	return getsum(right)-getsum(left-1);
} 
int main()
{
	int n;
	cin>>n;
	FenwickTree *Tree = new FenwickTree(n); 
	for(int i=1;i<=n;++i)
	{
		T x;
		cin>>x;
		Tree->insert(i,x);
	}
	cout<<"修改之前查询"<<endl; 
	int q1;
	cin>>q1; 
	for(int i=1;i<=q1;++i)
	{
		int x,y;
		cin>>x>>y;
		cout<<Tree->get_sum(x,y)<<endl; 
	}
	int m;
	cout<<"修改："<<endl;
	cin>>m;
	for(int i=1;i<=m;++i)
	{
		int x,y,z;
		cin>>x>>y>>z;
		Tree->range_update(x,y,z);
	}
	cout<<"修改后查询"<<endl; 
	int q2;
	cin>>q2;
	for(int i=1;i<=q2;++i)
	{
		int x,y;
		cin>>x>>y;
		cout<<Tree->get_sum(x,y)<<endl; 
	}
	return 0;
} 
