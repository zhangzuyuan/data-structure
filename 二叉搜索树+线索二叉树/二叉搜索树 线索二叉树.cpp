/*
这是二叉搜索树和线索二叉树的组合
我先建立起来二叉搜索树
通过比父亲节点大的放在右儿子上小的放在左儿子上
支持 删除，插入，判断是否存在树中，得到最大值和最小值的功能
删除就是先找到 删除节点，然后找到左子树中最大的替换

然后建立起来二叉搜索书之后，
用中序遍历来建立线索二叉树
我记录一个前驱pre这样，我在找到一个节点需要前驱或后继时候
就利用pre来赋值，然后更新pre
这样就能实现建立前驱和后继的功能
支持了找到该子树第一个节点，下一个节点和上一个节点和后继的功能
利用这些功能就能实现对树的从小到大或者从大到小的遍历
 
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
		void dfs_delete(node *x);//析构时候递归删除所有节点 
		
		//下面是二叉搜索树 
		bool check(T key);//检查是否在树中 
		T getMax();//得到最大值 
		T getMin();//得到最小值
		void Pop(T key);
		void pop(T key,node *&x);//删除值为key的节点 
		void insert(T key); //插入节点 
		
		//下面是线索二叉树 ，对 创建好的二叉搜索树线索化
		void createInThread(node *current);//递归建立线索 
		void CreateInThread(); //
		node* First(node *x)//找到第一个节点
		{
	        node* tmp=x;
	        while(tmp->boLeft==false)
	        {
		        tmp=tmp->left;//找最左下角的节点 
	        }
	        return tmp; 
        } 
		node* Next(node *x)//找到下一个节点
		{
	        node *tmp=x->right;
	        if(x->boRight==false)
	        {
		        return First(tmp);
	        }
	        else return tmp;
        }
		node* Last(node *x)//找到最后一个节点
		{
	        node *tmp=x;
	        while(tmp->boRight==false)
	        {
		        tmp=tmp->right;
	        }
	        return tmp;
        }
		node* Pre(node *x)//找到前驱节点
		{
	        node *tmp=x->left;
	        if(x->boLeft==0)
	        {
		        return Last(tmp);
	        }
	        else return tmp;
        } 
		
		void show();//中序线索遍历 
		 
		
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
		//处理最后一个节点
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
	createInThread(current->left);//递归左子树的线索
	if(current->left==NULL)//建立当前节点的前驱
	{
		current->left=pre;
		current->boLeft=1;
	} 
	if(pre!=NULL&&pre->right==NULL)//建立后继节点
	{
		pre->right=current;
		pre->boRight=1;
	} 
	pre=current;//更换前驱节点
	createInThread(current->right);//递归右子树 
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
