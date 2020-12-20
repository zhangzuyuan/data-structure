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
        void push(T x);//�ڶ�βѹ����Ԫ�� ��XΪҪѹ���Ԫ��
        void pop();//ɾ��������Ԫ�ص���������ֵ 
        T front();// ���ض���Ԫ�ص�ֵ������ɾ����Ԫ��  
        T back(); //���ض���βԪ�ص�ֵ������ɾ����Ԫ�� 
        
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
	cout<<"�ж��Ƿ�Ϊ��"<<endl;
	if(z->IsEmpty())
	{
		cout<<"�ն���"<<endl; 
	}
	else
	{
		cout<<"�ǿ�"<<endl; 
	}
	cout<<"pushԪ��"<<endl; 
	z->push(5);
	z->push(7);
	z->push(6);
	z->push(4);
	z->push(3);
	z->push(9);
	cout<<"�ж��Ƿ�Ϊ��"<<endl;
	if(z->IsEmpty())
	{
		cout<<"�ն���"<<endl; 
	}
	else
	{
		cout<<"�ǿ�"<<endl; 
	}
	
	cout<<"չʾ���е�Ԫ��"<<endl;
	z->show(); 
	
	cout<<"��ȡ����Ԫ��"<<endl; 
	cout<<z->front()<<endl;
	
	cout<<"��ȡ���д�С"<<endl; 
    cout<<z->size()<<endl;
    
    cout<<"ɾ������Ԫ��"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"ɾ������Ԫ��"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"�����βԪ��"<<endl;
	cout<<"����Ԫ��"<<endl;
	cin>>n; 
	z->push(n);
	z->show(); 
	
	cout<<"��ն���"<<endl;
	z->clear(); 
	
	cout<<"�ж��Ƿ�Ϊ��"<<endl;
	if(z->IsEmpty())
	{
		cout<<"�ն���"<<endl; 
	}
	else
	{
		cout<<"�ǿ�"<<endl; 
	}
	
    return 0;
}
