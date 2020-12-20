/*
������д�õĶ������ࡣ
ʵ�������������������������������Ĺ���
�����������������ڵ㣬����������и��ڵ��ڱ�����������֮�����
��������ÿһ�εݹ�ʱ��ȡ������������е�һ��Ϊ���ڵ㣬
Ȼ���ҵ���������ýڵ���Ӧ��λ�ã��ڵ���ߵ�Ϊ���������ұߵ�Ϊ������ 
�����������ұ���ȡ���������������ͬ�����Ľڵ㣬 ��������ȡ��ڵ����ȡ�ұߺ����������ұ���ͬ�Ľڵ㡣
�ٴεݹ顣��⡣
�������ܽ��������������ˡ� 
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
	cout<<"���������Ľڵ���"<<endl;
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
