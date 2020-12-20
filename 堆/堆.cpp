/*
封装priorityQueue堆 对象
支持操作：
支持泛型：如果用泛型的话请重载运算符。 
int size();返回堆大小 
void push(T key);插入元素 
void pop();删除堆顶元素 
T top();返回堆顶元素 
bool isEmpty();判空 
void clear();清空 
void show();展示debug用 
*/ 

#include<cstdio>
#include<vector>
#include<iostream>
using namespace std;
template<class T>
class priorityQueue
{
	private:
		vector<T> v;
		int len;
	public:
		priorityQueue();
		~priorityQueue();
		int size();
		void push(T key);
		void pop();
		T top();
		bool isEmpty();
		void clear();
		void show();
};

template<class T>
priorityQueue<T>::priorityQueue()
{
	len=0;
}
template<class T>
priorityQueue<T>::~priorityQueue()
{
	while(!isEmpty())
	    pop();
}
template<class T>
T priorityQueue<T>::top()
{
	return v[0];
}
template<class T>
bool priorityQueue<T>::isEmpty()
{
	return len==0;
}
template<class T>
void priorityQueue<T>::clear()
{
	while(!isEmpty())
	    pop();
}

template<class T>
int priorityQueue<T>::size()
{
	return len;
}

template<class T>
void priorityQueue<T>::push(T key)
{
	
	if(isEmpty())
	{
		v.push_back(key);
		len++;
		return;
	}
	int i;
	len++;
	for(i=len-1;v[(i-1)/2]>key;(--i)/=2)
	{
		//cout<<v[i]<<" ";
		v[i]=v[(i-1)/2];
		if(i==0) break;
	} 
	v[i]=key;
	//cout<<endl;
}
template<class T>
void priorityQueue<T>::pop()
{
	int i,child;
	T last;
	T min;
	if(isEmpty())
	{
		cout<<"Empty!"<<endl;
		return;
	}
	v[0] = v[len-1];
	len--;
	for(i=0;i*2+1<len;i = child)
	{
		child = i*2+1;
		if(child+1!=len&&v[child+1]<v[child])
		{
			child++;
		}
		if(v[i]>v[child])
		{
			T tmp=v[i];
			v[i]=v[child];
			v[child]=tmp;
		}
		else
		{
			break;
		}
	}
}
template<class T>
void priorityQueue<T>::show()
{
	for(int i=0;i<len;++i)
	    cout<<v[i]<<" ";
	cout<<endl;

}
int main()
{
	priorityQueue<int> z;
	z.push(100);
	z.push(80);
	z.push(12);
	z.push(5);
	z.push(6);
	z.push(77);
	z.push(52);
	z.push(54);
	z.push(44);
	z.push(72);
	z.push(63);
	cout<<z.size()<<endl;
	z.show();
	int n=z.size();
	for(int i=1;i<=n;++i)
	{
		cout<<z.top()<<" ";
		z.pop();
	}
	return 0;
}
