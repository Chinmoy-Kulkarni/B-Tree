#pragma once

#include <iostream>
using namespace std;


class BTreeNode
{
	int* Keys;
	int MinDegree;
	BTreeNode** ChildPointer;
	int NumOfKeys;
	bool IsLeaf;
public:
	BTreeNode(int _t, bool _IsLeaf);   // ChildPointeronstructor 

	void traverse();

	BTreeNode* search(int key);

	int findKey(int k);

	void insertNonFull(int k);

	void splitChild(int i, BTreeNode* y);

	void remove(int k);

	void removeFromIsLeaf(int idx);

	void removeFromNonIsLeaf(int idx);

	int getPred(int idx);

	int getSucc(int idx);

	void fill(int idx);

	void borrowFromPrev(int idx);

	void borrowFromNext(int idx);

	void merge(int idx);

	// To access private data of BTreeNode class
	friend class BTree;
};

class BTree
{
	BTreeNode* root;
	int MinDegree;
public:
	BTree(int _MinDegree)
	{
		root = NULL;
		MinDegree = _MinDegree;
	}

	void traverse()
	{
		if (root != NULL)
		{
			root->traverse();
		}
	}

	BTreeNode* search(int key)
	{
		if (NULL == root)
		{
			return NULL;
		}
		else
		{
			return root->search(key);
		}
	}

	void insert(int k);

	void remove(int k);
};
