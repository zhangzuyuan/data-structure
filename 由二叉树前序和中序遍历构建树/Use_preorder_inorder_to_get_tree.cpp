/*
调用了写好的二叉树类。
实现了由先序遍历和中序遍历来生成树的过程
先序遍历中先输出根节点，而中序遍历中根节点在遍历完左子树之后输出
所以我们每一次递归时都取先序遍历序列中第一个为根节点，
然后找到中序遍历该节点相应的位置，节点左边的为左子树，右边的为右子树 
在先序序列右边中取和中序序列左边相同数量的节点， 先序序列取完节点后再取右边和中序序列右边相同的节点。
再次递归。求解。
这样就能建立起来二叉树了。 
*/ 

#include<cstdio>
#include<iostream>
#include"binaryTree.h"
using namespace std;
int rebuild(binaryTree *Tree,int father,int preorder[],int prestart,int preend,int inorder[],int instart,int inend)
{
	if(prestart>=preend)
	{
		return preorder[prestart];
	}
	int index;
	for(int i=instart;i<=inend;++i)
	{
		if(inorder[i]==preorder[prestart])
		{
			index=i;break;
		}
	}
	int length=index-instart;
	int left,right;
	
	left = rebuild(Tree,preorder[prestart],preorder,prestart+1,prestart+length,inorder,instart,index-1);
	right = rebuild(Tree,preorder[prestart],preorder,prestart+length+1,preend,inorder,index+1,inend);
	
	Tree->insert(preorder[prestart],left,right,father);
	return preorder[prestart];
}
int main()
{
	int n;
	binaryTree *Tree=new binaryTree();
	int *preorder;
	int *inorder;
	cout<<"请输入树的节点数"<<endl;
	cin>>n;
	preorder=new int[n];
	inorder=new int[n];
	for(int i=0;i<n;++i)
	{
		cin>>preorder[i];
	} 
	for(int i=0;i<n;++i)
	{
		cin>>inorder[i];
	}
	rebuild(Tree,-1,preorder,0,n-1,inorder,0,n-1);
	Tree->show();
	return 0;
}
