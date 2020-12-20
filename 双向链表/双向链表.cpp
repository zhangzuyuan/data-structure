/*
���ܣ�
1.��С 
2.�жϿ�����
3.��λ�ã�ĩλ�ã��κ�λ����� 
4.��λ�ã�ĩλ�ã��κ�λ��ɾ��
5.��ѯ
6.չʾ����Ԫ��
7.�������
8.�������������� 

*/

#include<iostream>
#include<cstdio>
using namespace std;
template<class T>

class DoubleLink//the class of Double link
{
	
		
	private:	
        class node{//the class of node
            public:
	            T data;
	            node *prev;
	            node *next;
        };
    public:
	    class Iterator { //�򵥰������
	    private: 
            node *prv;
            
        public:
            Iterator(node* p = nullptr) {
                prv = p; 
            }
            
            ~Iterator(){
            	if(prv!=NULL)
            	 delete prv;
			}
            
            Iterator& operator ++ () { //����ǰ����������
                prv = prv->next;
                return *this;
            }
            
            Iterator& operator = (Iterator x){
            	prv=x.prv;
            	return *this;
			}
            
            Iterator& operator -- () { //����ǰ����������
                prv = prv->prev;
                return *this;
            }
            
			T operator *() const{
				return prv->data;
			}
            
            bool operator != (const Iterator& rhs) const{
                return (rhs.prv != this->prv);
            }
            bool operator == (const Iterator& rhs) const{
                return (rhs.prv == this-> prv);
            }
        };    
    

 
	private:
		node *head;//the pointer point to the head;
		node *tail;//the pointer point to the tail;
		int len;//the length of link
	
	public:
	    DoubleLink();
	    DoubleLink(const DoubleLink &l);
		~DoubleLink();
		
		Iterator begin()
		{
			return Iterator(head);
		}
		Iterator end()
		{
			return Iterator(tail->next);
		}
		
		int size();//get the size of link 
		
		bool IsEmpty();//judge whether the link is empty
		
		void push(int index,T data);
		void pushBack(T data);
		void pushHead(T data);
		
		T get(int index);//find a node
		
		void popBack();//delete the end of link
		void pop(int index);//delete a node
		void popHead();//delete the head of link
		
		void show();//print all nodes
		
		void clear();//delete all of the Link
		
};


template<class T>
DoubleLink<T>::DoubleLink()
{
	head = NULL;
	tail =NULL;
	len =0;
}

template<class T>
DoubleLink<T>::DoubleLink(const DoubleLink &l)
{
	if(l.head!=NULL)
	{
		node *tmp=l.head;
		head = new node();
		head ->data=tmp->data;
		len++;
		tmp=tmp->next;
		node *temp = head;
		while(tmp!=l.tail)
		{
			temp->next = new node();
			len++;
			temp->data = tmp->data;
			tmp = tmp->next;
		} 
	}
	else
	{
		head=tail=NULL;
		len = 0;
	}
}

template<class T>
DoubleLink<T>::~DoubleLink()
{
	node *tmp=head;
	while(head!=tail)
	{
		head=head->next;
		delete tmp;
		tmp = head;
	}
	len = 0;
}

template<class T>
int DoubleLink<T>::size()
{
	return len;
}

template<class T>
bool DoubleLink<T>::IsEmpty()
{
	return len==0;
}

template<class T>
void DoubleLink<T>::push(int index,T data)
{
	node *p,*q;
	p= head;
	q=head->next;
    if(index>len||index<0)
	   cout<<"you can't add the node,because the index you entered is wrong"<<endl;
	else
	{
		for(int i=2;i<index;++i)
		{
			p=p->next;
			q=q->next;
		}
		p->next = new node();
		p->next->data= data;
		p->next->prev=p;
		
		q->prev=p->next;
		q->prev->next=q;
	}   

}

template<class T>
void DoubleLink<T>::pushBack(T data)
{
	if(head==NULL)
	{
		head = new node();
		head->data = data;
		len++;
		tail=head;
	}
	else
	{
		tail->next=new node();
		tail->next->data= data;
		len++;
		tail->next->prev=tail;
		tail=tail->next; 
		tail->next=NULL;
	}
}

template<class T>
void DoubleLink<T>::pushHead(T data)
{
	if(head==NULL)
	{
		head = new node();
		head->data = data;
		len++;
		tail=head;
	}
	else
	{
		head->prev=new node();
		head->prev->data= data;
		len++;
		head->prev->next=head;
		head=head->prev; 
	}
}

template<class T>
T DoubleLink<T>::get(int index)
{
	node *p;
	p=head;
	if(index<0||index>len)
	{
	   cout<<"you can't get it.because you enter a wrong index"<<endl;
	   return NULL;
    }
	else
	{
		for(int i=1;i<index;++i)
		{
			p=p->next;
		}
		return p->data;
    }
}

template<class T>
void DoubleLink<T>::pop(int index)
{
	node *p,*q;
	p=head;
	q=head->next;
	if(index==1)
	{
		head=head->next;
		delete head->prev;
		return;
	}
	if(index==len)
	{
		tail=tail->prev;
		delete tail->next;
		return;
	}
	if(index>len||index<0)
	   cout<<"you can't delete the node,because the index you entered is wrong"<<endl;
	else
	{
		for(int i=2;i<index;++i)
		{
			p=p->next;
			q=q->next;
		}
		p->next= q->next;
		q->next->prev=p;
		delete q;
	}   
}

template<class T>
void DoubleLink<T>::popBack()
{
	if(len==0) 
	  cout<<"the link is empty"<<endl;
	else
	{
		tail=tail->prev;
		delete tail->next;
		tail->next=NULL; 
	}  
}

template<class T>
void DoubleLink<T>::popHead()
{
	if(len==0) 
	  cout<<"the link is empty"<<endl;
	else
	{
		head=head->next;
		delete head->prev;
	}  

}


template<class T>
void DoubleLink<T>::show()
{   
	node *p;
	p= head;
	if(p==NULL)
	{
		cout<<"Link is empty"<<endl;
	}
	else
	{
		while(p!=tail->next)
		{
			cout<<p->data<<" ";
			p=p->next;
		}
		cout<<endl;
	} 
}

template<class T>
void DoubleLink<T>::clear()
{
	node *p;
	p=head->next;
	while(p!=tail)
	{
		p=p->next;
		delete p->prev;
	}
	delete head;
	delete tail;
	tail=NULL;
	head=NULL;
	len=0;
}

int main()
{
    int n,m;
    DoubleLink<int>* lin=new DoubleLink<int>();
    
    if(lin->IsEmpty())
    {
    	cout<<"������"<<endl;
	}
	else
	{
		cout<<"����ǿ�"<<endl;
	} 
    cout<<"����ڵ�:"<<endl;
    lin->pushBack(5);
    lin->pushBack(8);
    lin->pushBack(7);
    lin->pushBack(4);
    lin->pushBack(3);
    lin->pushBack(4);
    lin->pushBack(1);
    lin->pushBack(0);
    
    cout<<"�����С"<<endl;
    cout<<lin->size()<<endl; 
    
    cout<<"������нڵ�:"<<endl;
    lin->show();
    
    if(lin->IsEmpty())
    {
    	cout<<"������"<<endl;
	}
	else
	{
		cout<<"����ǿ�"<<endl;
	} 
	
    
    cout<<"����Ҫ���ҵڼ����ڵ㣺"<<endl;
    cin>>n;
    cout<<lin->get(n)<<endl;
    
    cout<<"����Ҫɾ���ڼ����ڵ㣺"<<endl;
    cin>>n;
    lin->pop(n);
    lin->show();
    
    cout<<"ͷ����ӽڵ㣺"<<endl;
    cin>>n;
	lin->pushHead(n); 
	lin->show();
	
	cout<<"������λ����ӽ�㣺"<<endl;
	cout<<"λ�ã�"<<endl;
	cin>>m;
	cout<<"�ڵ㣺"<<endl;
	cin>>n;
	lin->push(m,n);
	lin->show();
	
	cout<<"ͷ��ɾ���ڵ㣺"<<endl;
	lin->popHead(); 
	lin->show(); 
	
	cout<<"β��ɾ���ڵ㣺"<<endl;
	lin->popBack(); 
	lin->show();
	cout<<"�����������һ��"<<endl; 
	DoubleLink<int>::Iterator it=lin->begin();
	
	cout<<"����������"<<endl; 
	for(DoubleLink<int>::Iterator it=lin->begin();it!=lin->end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl; 
	cout<<"��սڵ㣺"<<endl;
	lin->clear(); 
	lin->show();
	
	if(lin->IsEmpty())
    {
    	cout<<"������"<<endl;
	}
	else
	{
		cout<<"����ǿ�"<<endl;
	} 
	 
    return 0;
}
