/*
二维FenwickTree
测试数据：
5
7 4 5 8 1
1 2 1 3 8
4 5 1 1 6
6 3 2 8 1
1 0 2 2 4
3
2 3 4 4
1 1 5 5
3 2 5 4

二维的FenwickTree沿用了一维的算法，只是添加了一维而已
计算时候用二维的前缀和公式计算即可 
*/

#include<cstdio>
#include<iostream>
using namespace std;
typedef int T;
class FenwickTree2D
{
	private:
		int size;
		T **a;
		T **b;
	public:
		FenwickTree2D(int size);
		~FenwickTree2D();
		
		void insert(int x,int y,T key);
		void update(int x,int y,T key);
		T getSum(int x1,int y1,int x2,int y2);
		void show();
	private:
		int lowbit(int x);
		T getsum(int x,int y);
};
FenwickTree2D::FenwickTree2D(int size)
{
	this->size=size;
	a = new T*[size+1];
	for(int i=0;i<=size;++i)
	{
		a[i] = new T[size+1];
	} 
	b = new T*[size+1];
	for(int i=0;i<=size;++i)
	{
		b[i] = new T[size+1];
	} 
	for(int i=0;i<=size;++i)
	{
		for(int j=0;j<=size;++j)
		{
			a[i][j]=0;b[i][j]=0;
		}
	}
}
FenwickTree2D::~FenwickTree2D()
{
	for (int i=0;i<=size;i++)
    {
        delete[] a[i]; 
    }                    
    delete[] a;
    for (int i=0;i<=size;i++)
    {
        delete[] b[i]; 
    }                    
    delete[] b;
}
void FenwickTree2D::show()
{
	for(int i=1;i<=size;++i)
	{
		for(int j=1;j<=size;++j)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}
int FenwickTree2D::lowbit(int x)
{
	return x&(-x);
}
void FenwickTree2D::insert(int x,int y,T key)
{
	a[x][y]=key;
	update(x,y,key);
}
void FenwickTree2D::update(int x,int y,T key)
{
	for(;x<=size;x+=lowbit(x))
	{
		int tmpy = y;
		for(;tmpy<=size;tmpy+=lowbit(y))
		{
			b[x][tmpy]+=key;
		}
	}
}
T FenwickTree2D::getsum(int x,int y)
{
	int res=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		for(int j=y;j>0;j-=lowbit(j))
		{
			res+=b[i][j];
		}
	}
	return res;
}
T FenwickTree2D::getSum(int x1,int y1,int x2,int y2)
{
	return getsum(x2,y2)-getsum(x2,y1-1)-getsum(x1-1,y2)+getsum(x1-1,y1-1);
}
int main()
{
	int n;
	cin>>n;
	FenwickTree2D *Tree = new FenwickTree2D(n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			int x;
			cin>>x;
			Tree->insert(i,j,x);
		}
	}
	cout<<endl;
	Tree->show();
	cout<<"输入查询次数"<<endl;
	int m;
	cin>>m;
	for(int i=1;i<=m;++i)
	{
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		cout<<Tree->getSum(x1,y1,x2,y2)<<endl;
	} 
	return 0;
} 
