#include <iostream>
#include "DoubleLink.h"
using namespace std; 
template<class T>
class stack{
    private:
        DoubleLink<T> *link;
    public:
    	stack();
    	~stack();
        int size();
        void push(T x);
        void pop();
        T top();
        bool IsEmpty();
        void clear();
        void show();
};
template<class T>
stack<T>::stack()
{
	link=new DoubleLink<T>();
}
template<class T>
stack<T>::~stack()
{
	delete link;
}

template<class T>
int stack<T>::size()
{
    return link->size();
}
template<class T>
void stack<T>::push(T x)
{
	link->pushBack(x);
}
template<class T>
T stack<T>::top()
{
	return link->getBack();
}
template<class T>
void stack<T>::pop()
{
	link->popBack();
}
template<class T>
bool stack<T>::IsEmpty()
{
	return link->IsEmpty();
}
template<class T>
void stack<T>::clear()
{
	link->clear();
}
template<class T>
void stack<T>::show()
{
	link->show();
}

int main() {
	int n;
	stack<int>* z=new stack<int>();
	cout<<"�ж��Ƿ�Ϊ��"<<endl;
	if(z->IsEmpty())
	{
		cout<<"��ջ"<<endl; 
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
		cout<<"��ջ"<<endl; 
	}
	else
	{
		cout<<"�ǿ�"<<endl; 
	}
	
	cout<<"չʾջ��Ԫ��"<<endl;
	z->show(); 
	
	cout<<"��ȡջ��Ԫ��"<<endl; 
	cout<<z->top()<<endl;
	
	cout<<"��ȡջ��С"<<endl; 
    cout<<z->size()<<endl;
    
    cout<<"ɾ��ջ��Ԫ��"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"ɾ��ջ��Ԫ��"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"����ջ��Ԫ��"<<endl;
	cout<<"����Ԫ��"<<endl;
	cin>>n; 
	z->push(n);
	z->show(); 
	
	cout<<"���ջ"<<endl;
	z->clear(); 
	
	cout<<"�ж��Ƿ�Ϊ��"<<endl;
	if(z->IsEmpty())
	{
		cout<<"��ջ"<<endl; 
	}
	else
	{
		cout<<"�ǿ�"<<endl; 
	}
	
    return 0;
}
