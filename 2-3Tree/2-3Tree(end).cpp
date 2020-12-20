#include<cstdio>
#include<iostream>
using namespace std;
typedef int T;
class twoThreeTree
{
	private:
		struct node{
			T k1,k2;
			node *left=NULL,*middle=NULL,*right=NULL;
			int num=0; 
		};
		node *root;
		struct tmpData{//ɾ���Ͳ���ʱ����Ҫ�м��ݴ������ 
			T midValue;
			node *child;
			//���ֹ��캯�� 
			tmpData()
			{
				child=NULL;
			} 
			tmpData(node *p)
			{
				child=p;
			}
			tmpData(node *p,T x)
			{
				child=p;
				midValue=x;
			}
			tmpData operator = (tmpData & other)
			{
				if(&other !=this)
				{
					child = other.child;
					midValue = other.midValue;
				}
				return *this;
			}
			//���ƹ��캯��
			tmpData(tmpData &other)
			{
				child = other.child;
				midValue = other.midValue;
			} 
		};
	
	public:
		//�����͹��캯��
		twoThreeTree();
		~twoThreeTree();
		//չʾ��
		void show();
		//���ҽڵ�
		bool search(T x);
		//����
		void insert(T x); 
		//ɾ�� 
		void deleteNode(T x);
	
	//------����һЩ�ڲ��Ĳ���
	private:
		void destory(node *p);//ɾ���� 
		void Show(node *p);//չʾ��
		T searchFor(node *p,T x); //���� 
		tmpData* insertNode(node * &p,node *parent,T x);//����ڵ�
		tmpData* Delete(node *p,T x,node *parent);//ɾ���ڵ� 
		bool isleaf(node *p);//�ж��Ƿ���Ҷ�ӽڵ� 
		bool isfull(node *p);//�жϽڵ��Ƿ�Ϊ���ڵ� 
		tmpData* split(node *p,T x,node *child);//����ڵ�
		tmpData* merge(node *p,node *&r,node *child); 
};
//--------�����͹��캯��
twoThreeTree::twoThreeTree()
{
	root=NULL;
} 
twoThreeTree::~twoThreeTree()
{
	if(root!=NULL) destory(root);
}
void twoThreeTree::destory(node *p)
{
	if(p!=NULL)
	{
		destory(p->left);
		destory(p->middle);
		destory(p->right);
		delete p;
	}
}
//չʾ�� 
void twoThreeTree::show()
{
	cout<<"չʾ������"<<endl; 
	Show(root);
	cout<<endl;
}
void twoThreeTree::Show(node *p)
{
	if(p!=NULL)
	{
		if(p->num==1)
		{
			Show(p->left);
			cout<<p->k1<<" ";
			Show(p->middle);
		}
		if(p->num==2)
		{
			Show(p->left);
			cout<<p->k1<<" ";
			Show(p->middle);
			cout<<p->k2<<" ";
			Show(p->right);
		}
	}
}
//����
bool twoThreeTree::search(T x)
{
	if(root==NULL) false;
	return searchFor(root,x)==x;
} 
T twoThreeTree::searchFor(node *p,T x)
{
	if(p==NULL)
	{
		return -99999999;
	} 
	else 
	{
		if(p->num==1)
		{
			if(p->k1==x) return x;
			else if(x<p->k1) return searchFor(p->left,x);
			else if(x>p->k1) return searchFor(p->middle,x); 
		}
		if(p->num==2)
		{
			if(p->k1==x) return x;
			else if(p->k2==x) return x;
			else if(x<p->k1) return searchFor(p->left,x);
			else if(x<p->k2) return searchFor(p->middle,x);
			else if(x>p->k2) return searchFor(p->right,x);
			 
		}
	}
	
}
//���� 
void twoThreeTree::insert(T x)
{
	if(search(x))
	{
		cout<<"�ýڵ��Ѿ���������"<<endl; 
		return;
	}
	else 
	{
		node *p = root;
		tmpData *s = insertNode(root,p,x);
		if(s->child!=NULL)
		{
			node *tmp = new node;
			tmp->k1 =s->midValue;
			tmp->num=1;
			tmp->left = root;
			tmp->middle =s->child;
			tmp->right =NULL;
			root=tmp;
		}
	}
}
twoThreeTree::tmpData* twoThreeTree::insertNode(node * &p,node *parent,T x)
{
	//���һ �������ڸ���������������ֻ��һ�� 
	if(p==NULL)
	{
		node *tmp = new node;
		tmp->k1=x;
		tmp->left=tmp->right=tmp->middle=NULL;
		tmp->num=1;
		p=tmp;
		tmpData *s =new tmpData(NULL);
		return s; 
	}
	//���2 �ýڵ�ΪҶ�ӽڵ� 
	else if(p->left==NULL)
	{
		//���Ҷ�ӽڵ�δ��ֱ�Ӳ��� 
		if(p->num==1)
		{
			if(x<p->k1)
			{
				p->k2=p->k1;
				p->k1=x;
			}
			else 
			{
				p->k2=x;
			}
			p->num=2;
			 
	    }
	    //���Ҷ��������Ҫ��� 
	    else if(p->num==2)
	    {
	    	tmpData *s=split(p,x,NULL);
	    	return s;
		}
	}
	//����Ҷ�ӽڵ� 
	else 
	{
		if(p->num==1)
		{
			if(x<p->k1) 
			{
				tmpData* s=insertNode(p->left,p,x);
				if(s->child!=NULL)
				{
					p->k2=p->k1;
					p->k1=s->midValue;
					
					p->right=p->middle;
					p->middle=s->child;
					p->num=2;
				}
			}
			else if(x>p->k1)
			{
				tmpData* s=insertNode(p->middle,p,x);
				if(s->child!=NULL)
				{
					p->k2=s->midValue;
					p->right=s->child;
					p->num=2;
				}
			}
			tmpData *s =new tmpData(NULL);
		    return s; 
		}
		else if(p->num==2)
		{
			tmpData *s;
			if(x<p->k1) s=insertNode(p->left,p,x);
			else if(x<p->k2) s=insertNode(p->middle,p,x);
			else if(x>p->k2) s=insertNode(p->right,p,x);
			
			if(s->child!=NULL)
			{
				s=split(p,s->midValue,s->child);
				return s;
			}
			
			tmpData *q =new tmpData(NULL);
		    return q; 
		}
    }
}
twoThreeTree::tmpData* twoThreeTree::split(node *p,T x,node *child)
{
	T mid;
	node *tmp = new node();
	tmp->num=1;
	tmp->left=tmp->middle=tmp->right=NULL;
	//�������ֵС�ڸý������ֵʱ�� 
	if(x<p->k1)
	{
		mid=p->k1;
		tmp->k1=p->k2;
		p->k1=x; 
		//����ýڵ㲻��Ҷ�ӽڵ�ʱ�� 
		if(!isleaf(p))
		{
			tmp->left=p->middle;
			tmp->middle = p->right;
			p->middle = child;
		}
	}
	//�������ֵ���м�ʱ�� 
	else if(x<p->k2)
	{
		mid=x;
		tmp->k1=p->k2;
		if(!isleaf(p))
		{
			tmp->left=child;
			tmp->middle=p->right;
		}
	}
	//�������ֵ�����ұ�ʱ�� 
	else 
	{
		mid = p->k2;
		tmp->k1=x;
		if(!isleaf(p))
		{
			tmp->left=p->right;
			tmp->middle=child;
		}
	} 
	p->right=NULL;
	p->num=1;
	tmpData *s=new tmpData(tmp,mid);
	return s;
}
//---------ɾ��
void twoThreeTree::deleteNode(T x)
{
	node * p= root;
	Delete(root,x,p);
} 

twoThreeTree::tmpData* twoThreeTree::Delete(node *p,T x,node *parent)
{
	if(p==NULL)
	{
		cout<<"�Ѿ�����"<<endl;
		tmpData *s =new tmpData(NULL);
		return s;  
	}
	else if(p!=NULL)
	{
		//���м�ڵ㱻ɾ��ʱ��
		if(p->left!=NULL)
		{
			tmpData *s=new tmpData(NULL);
			//��Ϊ��������ʱ 
			if(p->num==1)
			{
				if(x!=p->k1) 
				{
					if(x<p->k1) s=Delete(p->left,x,p);
					else s=Delete(p->middle,x,p);
					
					if(s->child==NULL)
					{
						return s;
					}
				}
			}
			//�������ӽڵ�ʱ�� 
			else 
			{
				if((x!=p->k1)&&(x!=p->k2))
				{
					if(x<p->k1) s=Delete(p->left,x,p);
					else if(x<p->k2) s=Delete(p->middle,x,p);
					else if(x>p->k2) s=Delete(p->right,x,p);
					
					if(s->child==NULL) return s;
				}
			} 
			
			if(root->num==0)//������ɾ��֮��
			{
				root->left=root->middle=root->right=NULL;
				delete root;
				root=s->child;
				p= root;
				tmpData *q =new tmpData(NULL);
	 	        return q; 
			} 
			if(s->child!=NULL) 
			{
				s= merge(parent,p,s->child);
				return s;
			}
			//��ǰ��������ɾ����Ҷ�ӽڵ�
			node *current;
			T temp;
			if((p->num==2)&&(p->k2==x))
			{
				temp = p->k2;
				current = p->middle;
				parent=p;
				while(current->left!=NULL)
				{
					parent=current;
					if(current->num==1) current=current->middle;
					else if(current->num==2) current=current->right;
				}
				if(current->num==1)
				{
					p->k2 = current->k1;
					current->k1=temp;
				}
				else
				{
					p->k2 = current->k2;
					current->k2 = temp;
				}
			} 
			else
			{
				temp=p->k1;
				current = p->left;
				parent=p;
				while(current->left!=NULL)
				{
					parent=current;
					if(current->num==1) current=current->middle;
					else current=current->right;
				}
				if(current->num==1)
				{
					p->k1=current->k1;
					current->k1=temp;
				}
				else if(current->num==2)
				{
					p->k1 = current ->k2;
					current->k2=temp;
				}
			}
			current ->num--;
			p=current;
		}
		//��Ҷ�ӽڵ㱻ɾ��ʱ�� 
		else if((p->left==NULL)&&((p->k1==x)||(p->k2==x)))
		{
			if(p->num==2)
			{
				if(p->k1==x)
				{
					p->k1=p->k2;
				}
			}
			p->num--;
		}
		
		//��ɾ����鿴�ýڵ��Ƿ�û�� 
		if((p->num==0)&&(p==parent))
		{
			delete p;
			root=NULL;
		} 
		else if(p->num==0)
		{
			tmpData *s;
			s=merge(parent,p,NULL);
			return s;
		}
	}
} 
twoThreeTree::tmpData* twoThreeTree::merge(node *p,node *&r,node *child)
{
	//�������Ϊ����� 
	if((p->num==2)&&(p->right==r))
	{
		p->middle->k2=p->k2;
		p->middle->num=2;
		p->middle->right=child;
		child=NULL;
	} 
	else
	{
		if(p->left==r)
		{
			p->middle->k2=p->middle->k1;
			p->middle->k1=p->k1;
			p->middle->num=2;
			
			p->middle->right=p->middle->middle;
			p->middle->middle=p->middle->left;
			p->middle->left=child;
			
			child=p->middle;
			p->left=p->middle;
			p->middle=p->right;
		}
		else
		{
			p->left->k2=p->k1;
			p->left->num=2;
			p->left->right=child;
			child=p->left;
			p->middle=p->right;
		}
		if(p->num==2)
		{
			p->k1=p->k2;
			child=NULL;
		}
	}
	p->right=NULL;
	p->num--;
	
	r->left=r->middle=r->right=NULL;
	delete r;
	r=NULL;
	
	tmpData *s = new tmpData(child);
	return s;
} 
//---------��ز���
bool twoThreeTree::isleaf(node *p)
{
	if(p&&p->left==NULL&&p->middle==NULL&&p->right==NULL) return true;
	else return false;
} 
bool twoThreeTree::isfull(node *p)
{
	return p->num==2;
} 
int main()
{
	twoThreeTree *Tree = new twoThreeTree();
	Tree->insert(2);
	Tree->show();
	Tree->insert(8);
	Tree->show();
	Tree->insert(7); 
	Tree->show();
	Tree->insert(7); 
	Tree->show();
	Tree->insert(3); 
	Tree->show();
	Tree->insert(1); 
	Tree->show();
	Tree->insert(9); 
	Tree->show();
	Tree->insert(5); 
	Tree->show();
	Tree->insert(11); 
	Tree->show();
	Tree->insert(13); 
	Tree->show();
	Tree->insert(15);
	Tree->show();
	Tree->insert(4);
	Tree->show();
	
	cout<<"������ɾ������"<<endl; 
	Tree->deleteNode(13);
	Tree->show();
	Tree->deleteNode(5);
	Tree->show();
	return 0;
} 
