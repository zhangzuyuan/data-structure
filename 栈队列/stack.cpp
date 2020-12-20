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
	cout<<"ÅÐ¶ÏÊÇ·ñÎª¿Õ"<<endl;
	if(z->IsEmpty())
	{
		cout<<"¿ÕÕ»"<<endl; 
	}
	else
	{
		cout<<"·Ç¿Õ"<<endl; 
	}
	cout<<"pushÔªËØ"<<endl; 
	z->push(5);
	z->push(7);
	z->push(6);
	z->push(4);
	z->push(3);
	z->push(9);
	cout<<"ÅÐ¶ÏÊÇ·ñÎª¿Õ"<<endl;
	if(z->IsEmpty())
	{
		cout<<"¿ÕÕ»"<<endl; 
	}
	else
	{
		cout<<"·Ç¿Õ"<<endl; 
	}
	
	cout<<"Õ¹Ê¾Õ»µÄÔªËØ"<<endl;
	z->show(); 
	
	cout<<"»ñÈ¡Õ»¶¥ÔªËØ"<<endl; 
	cout<<z->top()<<endl;
	
	cout<<"»ñÈ¡Õ»´óÐ¡"<<endl; 
    cout<<z->size()<<endl;
    
    cout<<"É¾³ýÕ»¶¥ÔªËØ"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"É¾³ýÕ»¶¥ÔªËØ"<<endl;
	z->pop();
	z->show(); 
	
	cout<<"²åÈëÕ»¶¥ÔªËØ"<<endl;
	cout<<"ÊäÈëÔªËØ"<<endl;
	cin>>n; 
	z->push(n);
	z->show(); 
	
	cout<<"Çå¿ÕÕ»"<<endl;
	z->clear(); 
	
	cout<<"ÅÐ¶ÏÊÇ·ñÎª¿Õ"<<endl;
	if(z->IsEmpty())
	{
		cout<<"¿ÕÕ»"<<endl; 
	}
	else
	{
		cout<<"·Ç¿Õ"<<endl; 
	}
	
    return 0;
}
