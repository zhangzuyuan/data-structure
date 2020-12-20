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
		struct tmpData{//删除和插入时候需要中间暂存的数据 
			T midValue;
			node *child;
			//几种构造函数 
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
			//复制构造函数
			tmpData(tmpData &other)
			{
				child = other.child;
				midValue = other.midValue;
			} 
		};
	
	public:
		//析构和构造函数
		twoThreeTree();
		~twoThreeTree();
		//展示树
		void show();
		//查找节点
		bool search(T x);
		//插入
		void insert(T x); 
		//删除 
		void deleteNode(T x);
	
	//------其他一些内部的操作
	private:
		void destory(node *p);//删除树 
		void Show(node *p);//展示树
		T searchFor(node *p,T x); //查找 
		tmpData* insertNode(node * &p,node *parent,T x);//插入节点
		tmpData* Delete(node *p,T x,node *parent);//删除节点 
		bool isleaf(node *p);//判断是否是叶子节点 
		bool isfull(node *p);//判断节点是否为满节点 
		tmpData* split(node *p,T x,node *child);//分离节点
		tmpData* merge(node *p,node *&r,node *child); 
};
//--------析构和构造函数
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
//展示树 
void twoThreeTree::show()
{
	cout<<"展示树如下"<<endl; 
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
//查找
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
//插入 
void twoThreeTree::insert(T x)
{
	if(search(x))
	{
		cout<<"该节点已经在树中了"<<endl; 
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
	//情况一 空树，在该树的生命周期内只有一次 
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
	//情况2 该节点为叶子节点 
	else if(p->left==NULL)
	{
		//如果叶子节点未满直接插入 
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
	    //如果叶子满了需要拆分 
	    else if(p->num==2)
	    {
	    	tmpData *s=split(p,x,NULL);
	    	return s;
		}
	}
	//不是叶子节点 
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
	//当插入的值小于该结点的左边值时候 
	if(x<p->k1)
	{
		mid=p->k1;
		tmp->k1=p->k2;
		p->k1=x; 
		//如果该节点不是叶子节点时候 
		if(!isleaf(p))
		{
			tmp->left=p->middle;
			tmp->middle = p->right;
			p->middle = child;
		}
	}
	//当插入的值在中间时候 
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
	//当插入的值在最右边时候 
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
//---------删除
void twoThreeTree::deleteNode(T x)
{
	node * p= root;
	Delete(root,x,p);
} 

twoThreeTree::tmpData* twoThreeTree::Delete(node *p,T x,node *parent)
{
	if(p==NULL)
	{
		cout<<"已经空了"<<endl;
		tmpData *s =new tmpData(NULL);
		return s;  
	}
	else if(p!=NULL)
	{
		//当中间节点被删除时候
		if(p->left!=NULL)
		{
			tmpData *s=new tmpData(NULL);
			//当为两个孩子时 
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
			//三个孩子节点时候 
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
			
			if(root->num==0)//当根被删除之后
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
			//与前驱交换并删除非叶子节点
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
		//当叶子节点被删除时候 
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
		
		//在删除后查看该节点是否没有 
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
	//如果父亲为三结点 
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
//---------相关操作
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
	
	cout<<"下面是删除操作"<<endl; 
	Tree->deleteNode(13);
	Tree->show();
	Tree->deleteNode(5);
	Tree->show();
	return 0;
} 
