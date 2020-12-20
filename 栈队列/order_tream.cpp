#include <iostream>
#include "DoubleLink.h"
using namespace std; 
template<class T>
class order_team{
    private:
        DoubleLink<T> *link;
    public:
    	order_team();
    	~order_team();
        int size();
        void push(T x);//在队尾压入新元素 ，X为要压入的元素
        void pop();//删除队列首元素但不返回其值 
        T front();// 返回队首元素的值，但不删除该元素  
        T back(); //返回队列尾元素的值，但不删除该元素 
        
        bool IsEmpty();
        void clear();
        void show();
};
template<class T>
order_team<T>::order_team()
{
	link=new DoubleLink<T>();
}
template<class T>
order_team<T>::~order_team()
{
	delete link;
}

template<class T>
int order_team<T>::size()
{
    return link->size();
}
template<class T>
void order_team<T>::push(T x)
{
	link->pushBack(x);
}
template<class T>
T order_team<T>::front()
{
	return link->getHead();
}
template<class T>
T order_team<T>::back()
{
	return link->getBack();
}
template<class T>
void order_team<T>::pop()
{
	link->popHead();
}
template<class T>
bool order_team<T>::IsEmpty()
{
	return link->IsEmpty();
}
template<class T>
void order_team<T>::clear()
{
	link->clear();
}
template<class T>
void order_team<T>::show()
{
	link->show();
}

int main() {
	int n;
	order_team<int>* z=new order_team<int>();
	cout<<"判断是否为空"<<endl;
	if(z->IsEmpty())
	{
		cout<<"空队列"<<endl; 
	}
	else
	{
		cout<<"非空"<<endl; 
	}
	cout<<"push元素"<<endl; 
	z->push(5);
	z->push(7);
	z->push(6);
	z->push(4);
	z->push(3);
	z->push(9);
	cout<<"判断是否为空"<<endl;
	if(z->IsEmpty())
	{
		cout<<"空队列"<<endl; 
	}
	else
	{
		cout<<"非空"<<endl; 
	}
	
	cout<<"展示队列的元素"<<endl;
	z->show(); 
	
	cout<<"获取队首元素"<<endl; 
	cout<<z->front()<<endl;
	
	cout<<"获取队列大小"<<endl; 
    cout<<z->size()<<endl;
    
    cout<<"删除队首元素"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"删除队首元素"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"插入队尾元素"<<endl;
	cout<<"输入元素"<<endl;
	cin>>n; 
	z->push(n);
	z->show(); 
	
	cout<<"清空队列"<<endl;
	z->clear(); 
	
	cout<<"判断是否为空"<<endl;
	if(z->IsEmpty())
	{
		cout<<"空队列"<<endl; 
	}
	else
	{
		cout<<"非空"<<endl; 
	}
	
    return 0;
}
