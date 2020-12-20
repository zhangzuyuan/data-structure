/*
���Ƕ��������������������������
���Ƚ�����������������
ͨ���ȸ��׽ڵ��ķ����Ҷ�����С�ķ����������
֧�� ɾ�������룬�ж��Ƿ�������У��õ����ֵ����Сֵ�Ĺ���
ɾ���������ҵ� ɾ���ڵ㣬Ȼ���ҵ��������������滻

Ȼ������������������֮��
�������������������������
�Ҽ�¼һ��ǰ��pre�����������ҵ�һ���ڵ���Ҫǰ������ʱ��
������pre����ֵ��Ȼ�����pre
��������ʵ�ֽ���ǰ���ͺ�̵Ĺ���
֧�����ҵ���������һ���ڵ㣬��һ���ڵ����һ���ڵ�ͺ�̵Ĺ���
������Щ���ܾ���ʵ�ֶ����Ĵ�С������ߴӴ�С�ı���
 
*/


#include<cstdio>
#include<iostream>
using namespace std;
typedef int T;
class BST
{
	private:
		struct node{
			T data;
			int deep=0;
			node* left;
			node* right;
			bool boRight=false;
			bool boLeft=false;
			int leftSize=0,rightSize=0; 
		};
		node* root;
		node* pre; 
		
		int size=0;
	
	public:
		BST();
		~BST();
		void dfs_delete(node *x);//����ʱ��ݹ�ɾ�����нڵ� 
		
		//�����Ƕ��������� 
		bool check(T key);//����Ƿ������� 
		T getMax();//�õ����ֵ 
		T getMin();//�õ���Сֵ
		void Pop(T key);
		void pop(T key,node *&x);//ɾ��ֵΪkey�Ľڵ� 
		void insert(T key); //����ڵ� 
		
		//���������������� ���� �����õĶ���������������
		void createInThread(node *current);//�ݹ齨������ 
		void CreateInThread(); //
		node* First(node *x)//�ҵ���һ���ڵ�
		{
	        node* tmp=x;
	        while(tmp->boLeft==false)
	        {
		        tmp=tmp->left;//�������½ǵĽڵ� 
	        }
	        return tmp; 
        } 
		node* Next(node *x)//�ҵ���һ���ڵ�
		{
	        node *tmp=x->right;
	        if(x->boRight==false)
	        {
		        return First(tmp);
	        }
	        else return tmp;
        }
		node* Last(node *x)//�ҵ����һ���ڵ�
		{
	        node *tmp=x;
	        while(tmp->boRight==false)
	        {
		        tmp=tmp->right;
	        }
	        return tmp;
        }
		node* Pre(node *x)//�ҵ�ǰ���ڵ�
		{
	        node *tmp=x->left;
	        if(x->boLeft==0)
	        {
		        return Last(tmp);
	        }
	        else return tmp;
        } 
		
		void show();//������������ 
		 
		
};
BST::BST()
{
	root=NULL; 
}
BST::~BST()
{
	node *tmp=root;
	dfs_delete(tmp);
}

void BST::dfs_delete(node *x)
{
	if(x==NULL) return;
	dfs_delete(x->left);
	dfs_delete(x->right);
	delete x;
} 
 
void BST::insert(T key)
{
	if(size==0) 
	{
		size++;
		root=new node();
		root->data=key;
		return;
	}
	size++;
	node* tmp;
	tmp=root;
	node* leaf;
	bool rl=false;
	while(tmp!=NULL)
	{
		leaf=tmp;
		if(tmp->data>key)
		{
			leaf->leftSize++;
			rl=false;
			tmp=tmp->left;
		}
		else 
		{
			leaf->rightSize++; 
			rl=true;
			tmp=tmp->right;
		}
	}
	if(rl==false)
	{
		leaf->left=new node();
		leaf->left->data=key;
		leaf->left->left=NULL;
		leaf->left->right=NULL; 
	}
	else
	{
		leaf->right=new node();
		leaf->right->data=key;
		leaf->right->left=NULL;
		leaf->right->right=NULL; 
	}
}


T BST::getMax()
{
	if(size==0)
	{
		printf("The tree is empty\n"); return 0;
	}
	node* tmp=root;
	node* leaf;
	while(tmp!=NULL)
	{
		leaf=tmp;
		tmp=tmp->right;
	}
	return leaf->data;
} 
T BST::getMin()
{
	if(size==0)
	{
		printf("The tree is empty\n"); return 0;
	}
	node* tmp=root;
	node* leaf;
	while(tmp!=NULL)
	{
		leaf=tmp;
		tmp=tmp->left;
	}
	return leaf->data;
} 
bool BST::check(T key)
{
	if(size==0)
	{
		cout<<"The key is not in the tree"<<endl;
		return false; 
	} 
	node *tmp=root;
	while(tmp!=NULL)
	{
		if(tmp->data==key)
		{
			cout<<"The key is in the tree"<<endl;
			return true;
		} 
		if(tmp->data>key)
		{
			tmp=tmp->left;
		}
		else 
		{
			tmp=tmp->right;
		}
	} 
	printf("The key is not in the tree\n");
	return false; 
}
////void BST::getSequence()
//{
	
//}
void BST::Pop(T key)
{
	pop(key,root);
}
void BST::pop(T key,node *&x)
{
	if (x == NULL)
    {
        return;
    }
    //only one node
    if (x->left == NULL&&x->right == NULL)
    {
        if (x->data == key)
        {
            delete x;
            x = NULL;
            return;
        }
        else
        {
            return;
        }

    }


    if (x->data > key)
    {
        pop(key,x->left);
    }
    else if (x->data < key)
    {
        pop(key,x->right);
    }
    else
    {
        node* del = NULL;

        if (x->left == NULL)      //just has rightchild
        {
            del = x;
            x = x->right;
            delete del;
            del = NULL;
            return;
        }
        else if (x->right == NULL) //just has leftchild
        {
            del = x;
            x = x->left;
            delete del;
            del = NULL;
            return;
        }
        else
        {
            node* RightFirst = x->right;
            //find the first In order node
            while (RightFirst->left)
            {
                RightFirst = RightFirst->left;
            }

            //swap RightFirst node with cur node
            swap(x->data, RightFirst->data);

            pop(key,x->right);
            return;
        }
    }

}
void BST::CreateInThread()
{
	pre=NULL;
	if(root!=NULL)
	{
		createInThread(root);
		//�������һ���ڵ�
		pre->right=NULL;
		pre->boRight=1; 
	}
}
void BST::createInThread(node* current)
{
	if(current==NULL)
	{
		return;
	}
	createInThread(current->left);//�ݹ�������������
	if(current->left==NULL)//������ǰ�ڵ��ǰ��
	{
		current->left=pre;
		current->boLeft=1;
	} 
	if(pre!=NULL&&pre->right==NULL)//������̽ڵ�
	{
		pre->right=current;
		pre->boRight=1;
	} 
	pre=current;//����ǰ���ڵ�
	createInThread(current->right);//�ݹ������� 
}
//node* BST::First(node *x)


//node* BST::Next(node* x)


//node* BST::Last(node* x)

//node* BST::Pre(node *x)


void BST::show()
{
	for(node *tmp=First(root);tmp!=NULL;tmp=Next(tmp))
	{
		cout<<tmp->data<<" ";
	}
	cout<<endl;
} 
int main()
{
	BST *Tree=new BST();
	Tree->insert(5);
	Tree->insert(3);
	Tree->insert(8);
	Tree->insert(4); 
	Tree->insert(9);
	Tree->insert(1);
	Tree->insert(10);  
	
	cout<<Tree->getMax()<<endl;
	cout<<Tree->getMin()<<endl;
	
	Tree->check(15);
	Tree->check(9);
	
	Tree->Pop(10);
	
	cout<<Tree->getMax()<<endl;
	
	Tree->Pop(3);
	Tree->Pop(5);
	Tree->Pop(1);
	cout<<Tree->getMin()<<endl;
	
	Tree->CreateInThread();
	Tree->show();
	return 0;
} 
