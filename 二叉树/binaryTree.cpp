/*
建立一棵二叉树满足：插入，清除，得到树大小，得到节点father和child，得到先，后和中序遍历作用。
实现方法 设置结构体node作为节点，记录father，leftChild和rightChild,和自身编号数 
每次插入树的节点建立树插入节点信息包括节点编号，左右儿子编号，father编号
我们使用手写动态数组存储，如果输入的节点编号信息比当前存储节点大那么就用倍增开辟储存空间
开辟完储存空间后，把新加入的点给迁移。
这样就能完成对树的存储。

遍历：使用手工栈来进行模拟递归遍历。分别实现了三种遍历方式 
*/


#include<cstdio>
#include<iostream>
#include<stack>
using namespace std;
typedef int T;
class binaryTree{
	private:
		struct node{
	        T data;
	        int leftChild;
	        int rightChild;
	        int father;
	        int num;
        };
    
	node* nodeList;    
    int root=0;
    int size;
    int len;
    
    public:
    	binaryTree();
    	~binaryTree();
    	void insert(int index,int left,int right,int father);
    	void clearTree();
    	int getSize();
    	
    	int getFather(int x);
    	int getLeftChild(int x);
    	int getRightChild(int x);
    	
    	void show();
    	
    	void preorderTraversal();//先序遍历
		void postordeTraversal();//后序遍历
		void inorderTraversal();//中序遍历 
    	
};

binaryTree::binaryTree()
{
	nodeList=NULL;

	size=0; 
	len=0;
}
binaryTree::~binaryTree()
{
	delete []nodeList;
}
void binaryTree::insert(int index,int left,int right,int father)
{
	if(father==-1)
	{
		root=size;
	}
	int tmp=len;bool bo=false;
	while(max(max(left,index),max(right,father))>tmp)
	{
		tmp=tmp*2+1;
		bo=true;
	}
	while(size>tmp) 
	{
		tmp=tmp*2+1;
		bo=true;
	}
	if(bo)
	{
		node *newNodeList=new node[tmp];
		//for(int i=0;i<len;i++)
		//{
		//	newNodeList[i]=nodeList[i];
		//} 
		memcpy(newNodeList,nodeList,len*sizeof(node));
		delete []nodeList;
		nodeList=newNodeList;
		len=tmp;
	}
	nodeList[index].leftChild=left;
	nodeList[index].rightChild=right;
	nodeList[index].father=father;
	nodeList[index].num=index;
	size=max(index,++size);
}
void binaryTree::clearTree()
{
	delete []nodeList;
}

int binaryTree::getSize()
{
	return size;
}
int binaryTree::getFather(int x)
{
	return nodeList[x].father;
}
int binaryTree::getLeftChild(int x)
{
	return nodeList[x].leftChild;
}
int binaryTree::getRightChild(int x)
{
	return nodeList[x].rightChild;
}

void binaryTree::show()
{
	for(int i=0;i<size;i++)
	{
		cout<<i<<" "<<getFather(i)<<" "<<getLeftChild(i)<<" "<<getRightChild(i)<<endl;
	}
	cout<<root<<endl;
}

void binaryTree::preorderTraversal()
{
	stack<node> s;
	s.push(nodeList[root]);
	while(!s.empty())
	{
		node tmp=s.top();
		s.pop();
		cout<<tmp.num<<" ";
		if(tmp.rightChild!=-1)
		    s.push(nodeList[tmp.rightChild]);
		if(tmp.leftChild!=-1)
		    s.push(nodeList[tmp.leftChild]);
	}
	cout<<endl;
} 

void binaryTree::postordeTraversal()
{
	stack<node> s;
	bool b[size]={false};
	s.push(nodeList[root]);
	while(!s.empty())
	{
		node tmp=s.top();
		if(tmp.rightChild!=-1&&b[tmp.num]==false)
		    s.push(nodeList[tmp.rightChild]);
		if(tmp.leftChild!=-1&&b[tmp.num]==false)
		    s.push(nodeList[tmp.leftChild]);
		    
		b[tmp.num]=true;
		if(b[s.top().num]==true)
		{
			cout<<tmp.num<<" ";
			s.pop();
		}
	}
	cout<<endl;
}

void binaryTree::inorderTraversal()
{
	stack<node> s;
	bool b[size]={false};
	s.push(nodeList[root]);
	while(!s.empty())
	{
		node tmp=s.top();
		if(tmp.leftChild!=-1&&b[tmp.num]==false)
		{
		    s.push(nodeList[tmp.leftChild]);
	    }    
		b[tmp.num]=true;
		if(b[s.top().num])
		{
			cout<<tmp.num<<" ";
			s.pop();
			if(tmp.rightChild!=-1)
			    s.push(nodeList[tmp.rightChild]);
		}
	}
	cout<<endl;
}

int main()
{
	binaryTree *Tree=new binaryTree();
	//Tree->insert(1,2,-1);
	//Tree->insert(3,4,0);
	//Tree->insert(5,-1,0);
	//Tree->insert(-1,-1,1);
	//Tree->insert(-1,-1,1);
	//Tree->insert(-1,-1,2);
	
	Tree->insert(0,-1,-1,3);
	Tree->insert(1,-1,-1,6);
	Tree->insert(2,-1,-1,6);
	Tree->insert(3,5,0,4);
	Tree->insert(4,3,6,-1);
	Tree->insert(5,7,-1,3);
	Tree->insert(6,1,2,4);
	Tree->insert(7,-1,-1,5);
	Tree->show();
	Tree->preorderTraversal();
	Tree->postordeTraversal();
	Tree->inorderTraversal();
	return 0;
} 
