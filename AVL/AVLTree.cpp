/*
AVL��
֧�ֲ��룬ɾ������������ȹ��� 
����ڵ�ʱͨ���ж�����Ƿ���ҪŤ��
ɾ���ڵ��Ť�������ô���
�������ǽ����ⷴת�������Ǿͱ�ú����� 
ɾ���Ľڵ���Կ����ǲ���һ���ڵ����ɵ�����Ȳ�ƽ��������Ť�� 
�������ܺܺõĽ���ɾ�������� 

�������������Ť������LL��LR��RR��RL
LL�������������ǰ�ԭ���ĸ��׽ڵ����Ҷ��ӽڵ� ������ӽڵ��ɸ��� 
            ԭ������ӵ���������ɣ������Ҷ��ӵ������� 
RR����������ͬ�� 
LR������������������׽ڵ�������������������������LLģʽ��Ȼ�������� 
RL���Ҷ��������������׽ڵ�����������ͬ��
*/ 

#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

typedef int T; 
class AVLTree
{
	private:
		struct node{
			T data;
			node *leftChild=NULL;
			node *rightChild=NULL;
			int height=0;
		}; 
	node *root;
	int size=0;
	
	public:
		AVLTree();
		~AVLTree();
		void clear(node *x);
		
		T showRoot();//�õ����ڵ� 
		int getSize();//�õ����Ĵ�С 
		bool IsEmpty();//�ж��Ƿ�Ϊ�� 
		void insert(T x);//����ڵ� 
		void pop(T x);//ɾ���ڵ� 
		void show();//չʾ 
		
	private:
		//�������ڵķ��� 
		int getHeight(node *tmp);//�õ���ǰ�ڵ����� 
		node* inSert(node *&tmp,T x);//���� 
		void inorderTraversal(node *tmp);//������� 
		//������� 
		node* LL(node *tmp);
		node* LR(node *tmp);
		node* RR(node *tmp);
		node* RL(node *tmp);
		//ɾ���ڵ� 
		node* popNode(node *&tmp,T x);
		T findMaxInLeft(node *tmp);
		//T findMinInRight(node *tmp); 
		
};
AVLTree::AVLTree()
{
	//root = new node();
	root = NULL; 
}
AVLTree::~AVLTree()
{
	clear(root);
}
void AVLTree::clear(node *x)
{
	if(x==NULL) return;
	clear(x->leftChild);
	clear(x->rightChild);
	delete x; 
}
int AVLTree::getSize()
{
	return this->size;
}
bool AVLTree::IsEmpty()
{
	return size==0;
}
T AVLTree::showRoot()
{
	return root->data;
}
int AVLTree::getHeight(node *tmp)
{
	if(tmp==NULL) return -1;
	return tmp->height;
}
AVLTree::node* AVLTree::LL(node *tmp)
{
	node *TT=tmp->leftChild;
	tmp->leftChild=TT->rightChild;
	TT->rightChild=tmp;
	tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
	TT->height = 1+max(getHeight(TT->leftChild),getHeight(tmp->rightChild));

	return TT;
}
AVLTree::node* AVLTree::RR(node *tmp)
{
	node *TT = tmp->rightChild;
	tmp->rightChild=TT->leftChild;
	TT->leftChild=tmp;
	tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
	TT->height = 1+max(getHeight(TT->leftChild),getHeight(tmp->rightChild));
	return TT;
}
AVLTree::node* AVLTree::LR(node *tmp)
{
	tmp->leftChild=RR(tmp->leftChild);
	return LL(tmp);
}

AVLTree::node* AVLTree::RL(node *tmp)
{
	tmp->rightChild=LL(tmp->rightChild);
	return RR(tmp);
}


void AVLTree::insert(T x)
{
	inSert(root,x);
}

void AVLTree::pop(T x)
{
	root = popNode(root,x);
} 
T AVLTree::findMaxInLeft(node *tmp)
{
	if(tmp==NULL) return 0;
	else if(tmp->rightChild==NULL) return tmp->data;
	return findMaxInLeft(tmp->rightChild);
}
AVLTree::node* AVLTree::popNode(node *&tmp,T x)
{
	if (tmp == NULL)
    {
        return NULL;
    }
    else if(x<tmp->data)
    {
    	tmp->leftChild = popNode(tmp->leftChild,x);
    	if(getHeight(tmp->rightChild)-getHeight(tmp->leftChild)>=2)
		{
			if(getHeight(tmp->rightChild->leftChild)>getHeight(tmp->rightChild->leftChild))
			    tmp=RL(tmp);
			else
			    tmp=RR(tmp);
		}
		tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
		return tmp;
	}
	else if(x>tmp->data)
	{
		tmp->rightChild = popNode(tmp->rightChild,x);
		if(getHeight(tmp->rightChild)-getHeight(tmp->leftChild)>=2)
		{
			if(getHeight(tmp->leftChild->leftChild)>getHeight(tmp->leftChild->rightChild))
			    tmp=LL(tmp);
			else
			    tmp=LR(tmp);
		}
		tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
		return tmp;
	}
	else if(x==tmp->data)
	{
		if(tmp->leftChild==NULL&&tmp->rightChild==NULL)
		{
			size--;
			delete tmp;
			tmp=NULL;
			//tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
			return tmp; 
		}
		else if(tmp->leftChild!=NULL&&tmp->rightChild==NULL)
		{
			size--;
			node *TT=tmp->leftChild;
			delete tmp;
			//TT->height=1+max(getHeight(TT->leftChild),getHeight(TT->rightChild));
			return TT;
		}
		else if(tmp->rightChild!=NULL&&tmp->leftChild==NULL)
		{
			size--;
			node *TT=tmp->rightChild;
			delete tmp;
			//TT->height=1+max(getHeight(TT->leftChild),getHeight(TT->rightChild));
			return TT;
		}
		else
		{
			
			int maxData = findMaxInLeft(tmp->leftChild);
			tmp->data=maxData;
			tmp->leftChild = popNode(tmp->leftChild,maxData);
			//tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
			return tmp;
		}
	}
}
AVLTree::node* AVLTree::inSert(node *&tmp,T x)
{
	if(tmp==NULL)
	{
		tmp = new node();
		tmp->data=x;
		tmp->leftChild=NULL;tmp->rightChild=NULL;
		tmp->height=0;
		size++;
	}
	else if(x<tmp->data)
	{
		tmp->leftChild=inSert(tmp->leftChild,x);
		if(getHeight(tmp->leftChild)-getHeight(tmp->rightChild)>=2)
		{
			if(x<tmp->leftChild->data)
			{
				tmp=LL(tmp);
			}
			else 
			{
				tmp=LR(tmp);
			}
		}
	}
	else if(x>=tmp->data)
	{
		tmp->rightChild=inSert(tmp->rightChild,x);
		if(getHeight(tmp->rightChild)-getHeight(tmp->leftChild)>=2)
		{
			if(x>tmp->rightChild->data)
			{
				tmp=RR(tmp);
			}
			else 
			{
				tmp=RL(tmp);
			}
		}
	}
	tmp->height=1+max(getHeight(tmp->leftChild),getHeight(tmp->rightChild));
	return tmp; 
}
void AVLTree::show()
{
	inorderTraversal(root);
	cout<<endl;
}
void AVLTree::inorderTraversal(node *tmp)
{
	if(tmp==NULL)
	{
		return;
	}
	inorderTraversal(tmp->leftChild);
	cout<<tmp->data<<" ";
	inorderTraversal(tmp->rightChild);
}
int main()
{
	AVLTree* Tree=new AVLTree();
	Tree->insert(5);
	Tree->insert(3);
	Tree->insert(8);
	Tree->insert(4); 
	Tree->insert(9);
	Tree->insert(6);
	Tree->insert(1);
	Tree->insert(10);
	//Tree->insert(1);
	//Tree->insert(2);
	//Tree->insert(3);
	//Tree->insert(4);
	//Tree->insert(5);
	//Tree->insert(6);
	//Tree->insert(7);
	//Tree->insert(8);
	//Tree->insert(9);
	//Tree->insert(10);
	
	Tree->show();
	cout<<"The size of Tree is "<<Tree->getSize()<<endl;
	cout<<"The data of the Tree root is "<<Tree->showRoot()<<endl;
	
	
	Tree->pop(8);
	Tree->pop(5);
	Tree->pop(3);
	Tree->show();
	cout<<"The size of Tree is "<<Tree->getSize()<<endl;
	cout<<"The data of the Tree root is "<<Tree->showRoot()<<endl;
	
	return 0;
} 
