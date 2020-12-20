/*
һά�� FenwickTreeά���������ѯ���� �� �����޸ĵĲ���
�ڴ�����ʹ����vector ��̬���飬���ϲ���Ԫ�أ�Ԫ�ز�����֮������
Ȼ�� ���Խ����޸ĺͲ�ѯ���� 
*/

#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
typedef int T;
class FenwickTree{
	private:
		vector<T> a;//ԭ���� 
		T *b;//��״����
		int size=0;
	
	public:
		FenwickTree();
		~FenwickTree();
		T get_a(int index);//�õ�ԭ���� 
		T get_b(int index);//�õ�Ԥ���������� 
		void insert(T key);//����Ԫ�� 
		void creatTree();//Ԥ������ 
		void update(T key,int index);
		T getSum(int i,int j);
		
		void show(); 
	private:
		T getsum(int index);
		int lowbit(int index);
		
}; 
FenwickTree::FenwickTree()
{
	a.push_back(0);
	 
}
FenwickTree::~FenwickTree()
{
	delete[] b;
}
void FenwickTree::insert(T key)
{
	a.push_back(key);
}
void FenwickTree::creatTree()
{
	delete[] b;
	b=NULL;
	b=new T[a.size()];
	for(int i=0;i<=a.size()-1;i++) b[i]=0;
	for(int i=1;i<=a.size()-1;++i)
	{
		update(a[i],i); 
	}
}
void FenwickTree::show()
{
	for(int i=1;i<=a.size()-1;++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	for(int i=1;i<=a.size()-1;++i)
	{
		cout<<b[i]<<" ";
	}
	cout<<endl;
}

int FenwickTree::lowbit(int index)
{
	return (index&(-index));
} 
T FenwickTree::get_a(int index)
{
	if(index>size)
	{
		cout<<"the index is over the size"<<endl;	
	}
	else
	{
		return a[index];
	}
}

T FenwickTree::get_b(int index)
{
	if(index>size)
	{
		cout<<"the index is over the size"<<endl;	
	}
	else
	{
		return b[index];
	}
}
void FenwickTree::update(T key,int index)
{
	for(;index<=a.size()-1;index += lowbit(index))
	{
		b[index]+=key;
	}
}

T FenwickTree::getsum(int index)
{
	int res = 0;
	for(;index>0;index -=lowbit(index))
	{
		res+= b[index];
	}
	return res;
}
T FenwickTree::getSum(int i,int j)
{
	return getsum(j)-getsum(i-1);
}
int main()
{
	FenwickTree *Tree = new FenwickTree(); 
	Tree->insert(5);
	Tree->insert(8);
	Tree->insert(1);
	Tree->insert(6);
	Tree->insert(4);
	Tree->insert(9);
	Tree->insert(7);
	Tree->insert(5);
	Tree->insert(6);
	Tree->creatTree();
	Tree->show();
	
	cout<<Tree->getSum(2,4)<<endl;
	cout<<Tree->getSum(1,6)<<endl;
	cout<<Tree->getSum(7,8)<<endl;
	cout<<Tree->getSum(8,8)<<endl;
	
	cout<<"���£�"<<endl; 
	Tree->update(6,3);
	Tree->update(2,8);
	cout<<Tree->getSum(2,4)<<endl;
	cout<<Tree->getSum(1,6)<<endl;
	cout<<Tree->getSum(7,8)<<endl;
	cout<<Tree->getSum(8,8)<<endl;
	return 0;
} 
