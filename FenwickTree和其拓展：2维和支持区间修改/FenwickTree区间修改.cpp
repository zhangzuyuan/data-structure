/*

֧�������޸���Ҫά�����ǲ�������b[i]=a[i]-a[i-1];
��a[i]=sum(b[1]...b[i]);
ͬ��sum(a[1]..a[n])=n*sum(b[1]..b[i])-sum(b[i]*(i-1)) 
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
		void update(int index,T key);//�����޸�
		void range_update(int left,int right,T key);//�����޸�
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
		sum1[i]+=key;//ά��ǰ׺��b[i] 
		sum2[i]+=key*(index-1);//ά��ǰ׺�� b[i]*(n-1);
	}
}
void FenwickTree::range_update(int left,int right,T key)
{
	update(left,key);//�������ֻҪ������߼��ϾͿ��Ը�������� 
	update(right+1,-key);//�����ұߵ���Ҫ��ȥ 
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
	cout<<"�޸�֮ǰ��ѯ"<<endl; 
	int q1;
	cin>>q1; 
	for(int i=1;i<=q1;++i)
	{
		int x,y;
		cin>>x>>y;
		cout<<Tree->get_sum(x,y)<<endl; 
	}
	int m;
	cout<<"�޸ģ�"<<endl;
	cin>>m;
	for(int i=1;i<=m;++i)
	{
		int x,y,z;
		cin>>x>>y>>z;
		Tree->range_update(x,y,z);
	}
	cout<<"�޸ĺ��ѯ"<<endl; 
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
