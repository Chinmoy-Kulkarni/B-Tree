#include "BTree.h"

BTreeNode::BTreeNode(int t1, bool IsLeaf1)
{
	MinDegree = t1;
	IsLeaf = IsLeaf1;

	Keys = new int[2 * MinDegree - 1];
	ChildPointer = new BTreeNode * [2 * MinDegree];

	NumOfKeys = 0;
}

int BTreeNode::findKey(int k)
{
	int idx = 0;
	while (idx < NumOfKeys && Keys[idx] < k)
	{
		++idx;
	}
	return idx;
}

void BTreeNode::remove(int k)
{
	int idx = findKey(k);

	if (idx < NumOfKeys && Keys[idx] == k)
	{

		if (IsLeaf) 
		{
			removeFromIsLeaf(idx);
		}
		else
		{
			removeFromNonIsLeaf(idx);
		}
	}
	else
	{
		if (IsLeaf)
		{
			cout << "The key " << k << " is does not exist in the tree " << endl;;
			return;
		}

		bool flag = ((idx == NumOfKeys) ? true : false);

		if (ChildPointer[idx]->NumOfKeys < MinDegree)
		{
			fill(idx);
		}

		if (flag && idx > NumOfKeys)
		{
			ChildPointer[idx - 1]->remove(k);
		}
		else
		{
			ChildPointer[idx]->remove(k);
		}
	}
	return;
}

void BTreeNode::removeFromIsLeaf(int idx)
{

	for (int i = idx + 1; i < NumOfKeys; ++i)
	{
		Keys[i - 1] = Keys[i];
	}

	NumOfKeys--;

	return;
}

void BTreeNode::removeFromNonIsLeaf(int idx)
{

	int k = Keys[idx];

	if (ChildPointer[idx]->NumOfKeys >= MinDegree)
	{
		int pred = getPred(idx);
		Keys[idx] = pred;
		ChildPointer[idx]->remove(pred);
	}
	else if (ChildPointer[idx + 1]->NumOfKeys >= MinDegree)
	{
		int succ = getSucc(idx);
		Keys[idx] = succ;
		ChildPointer[idx + 1]->remove(succ);
	}
	else
	{
		merge(idx);
		ChildPointer[idx]->remove(k);
	}
	return;
}

int BTreeNode::getPred(int idx)
{
	BTreeNode* cur = ChildPointer[idx];
	while (!cur->IsLeaf)
	{
		cur = cur->ChildPointer[cur->NumOfKeys];
	}

	return cur->Keys[cur->NumOfKeys - 1];
}

int BTreeNode::getSucc(int idx)
{
	BTreeNode* cur = ChildPointer[idx + 1];
	while (!cur->IsLeaf)
	{
		cur = cur->ChildPointer[0];
	}

	return cur->Keys[0];
}

void BTreeNode::fill(int idx)
{
	if (idx != 0 && ChildPointer[idx - 1]->NumOfKeys >= MinDegree)
	{
		borrowFromPrev(idx);
	}
	else if (idx != NumOfKeys && ChildPointer[idx + 1]->NumOfKeys >= MinDegree)
	{
		borrowFromNext(idx);
	}
	else
	{
		if (idx != NumOfKeys)
		{
			merge(idx);
		}
		else
		{
			merge(idx - 1);
		}
	}
	return;
}

void BTreeNode::borrowFromPrev(int idx)
{

	BTreeNode* child = ChildPointer[idx];
	BTreeNode* sibling = ChildPointer[idx - 1];

	for (int i = child->NumOfKeys - 1; i >= 0; --i)
	{
		child->Keys[i + 1] = child->Keys[i];
	}

	if (!child->IsLeaf)
	{
		for (int i = child->NumOfKeys; i >= 0; --i)
		{
			child->ChildPointer[i + 1] = child->ChildPointer[i];
		}
	}

	child->Keys[0] = Keys[idx - 1];

	if (!child->IsLeaf)
	{
		child->ChildPointer[0] = sibling->ChildPointer[sibling->NumOfKeys];
	}

	Keys[idx - 1] = sibling->Keys[sibling->NumOfKeys - 1];

	child->NumOfKeys += 1;
	sibling->NumOfKeys -= 1;

	return;
}

void BTreeNode::insertNonFull(int k)
{
	int i = NumOfKeys - 1;

	if (IsLeaf == true)
	{
		while (i >= 0 && Keys[i] > k)
		{
			Keys[i + 1] = Keys[i];
			i--;
		}

		Keys[i + 1] = k;
		NumOfKeys = NumOfKeys + 1;
	}
	else
	{
		while (i >= 0 && Keys[i] > k)
		{
			i--;
		}

		if (ChildPointer[i + 1]->NumOfKeys == 2 * MinDegree - 1)
		{
			splitChild(i + 1, ChildPointer[i + 1]);

			if (Keys[i + 1] < k)
			{
				i++;
			}
		}
		ChildPointer[i + 1]->insertNonFull(k);
	}
}

void BTreeNode::splitChild(int i, BTreeNode* y)
{
	BTreeNode* z = new BTreeNode(y->MinDegree, y->IsLeaf);
	z->NumOfKeys = MinDegree - 1;

	for (int j = 0; j < MinDegree - 1; j++)
	{
		z->Keys[j] = y->Keys[j + MinDegree];
	}

	if (y->IsLeaf == false)
	{
		for (int j = 0; j < MinDegree; j++)
		{
			z->ChildPointer[j] = y->ChildPointer[j + MinDegree];
		}
	}

	y->NumOfKeys = MinDegree - 1;

	for (int j = NumOfKeys; j >= i + 1; j--)
	{
		ChildPointer[j + 1] = ChildPointer[j];
	}

	ChildPointer[i + 1] = z;

	for (int j = NumOfKeys - 1; j >= i; j--)
	{
		Keys[j + 1] = Keys[j];
	}

	Keys[i] = y->Keys[MinDegree - 1];

	NumOfKeys = NumOfKeys + 1;
}

void BTreeNode::borrowFromNext(int idx)
{

	BTreeNode* child = ChildPointer[idx];
	BTreeNode* sibling = ChildPointer[idx + 1];

	child->Keys[(child->NumOfKeys)] = Keys[idx];

	if (!(child->IsLeaf))
	{
		child->ChildPointer[(child->NumOfKeys) + 1] = sibling->ChildPointer[0];
	}

	Keys[idx] = sibling->Keys[0];

	for (int i = 1; i < sibling->NumOfKeys; ++i)
	{
		sibling->Keys[i - 1] = sibling->Keys[i];
	}

	if (!sibling->IsLeaf)
	{
		for (int i = 1; i <= sibling->NumOfKeys; ++i)
		{
			sibling->ChildPointer[i - 1] = sibling->ChildPointer[i];
		}
	}

	child->NumOfKeys += 1;
	sibling->NumOfKeys -= 1;

	return;
}

void BTreeNode::merge(int idx)
{
	BTreeNode* child = ChildPointer[idx];
	BTreeNode* sibling = ChildPointer[idx + 1];

	child->Keys[MinDegree - 1] = Keys[idx];

	for (int i = 0; i < sibling->NumOfKeys; ++i)
	{
		child->Keys[i + MinDegree] = sibling->Keys[i];
	}

	if (!child->IsLeaf)
	{
		for (int i = 0; i <= sibling->NumOfKeys; ++i)
		{
			child->ChildPointer[i + MinDegree] = sibling->ChildPointer[i];
		}
	}

	for (int i = idx + 1; i < NumOfKeys; ++i)
	{
		Keys[i - 1] = Keys[i];
	}

	for (int i = idx + 2; i <= NumOfKeys; ++i)
	{
		ChildPointer[i - 1] = ChildPointer[i];
	}

	child->NumOfKeys += sibling->NumOfKeys + 1;
	NumOfKeys--;

	delete(sibling);
	return;
}

void BTree::insert(int k)
{
	if (root == NULL)
	{
		root = new BTreeNode(MinDegree, true);
		root->Keys[0] = k;
		root->NumOfKeys = 1;
	}
	else
	{
		if (root->NumOfKeys == 2 * MinDegree - 1)
		{
			BTreeNode* s = new BTreeNode(MinDegree, false);

			s->ChildPointer[0] = root;

			s->splitChild(0, root);

			int i = 0;
			if (s->Keys[0] < k)
			{
				i++;
			}
			s->ChildPointer[i]->insertNonFull(k);

			root = s;
		}
		else
		{
			root->insertNonFull(k);
		}
	}
}

void BTreeNode::traverse()
{
	int i;
	for (i = 0; i < NumOfKeys; i++)
	{
		if (IsLeaf == false)
		{
			ChildPointer[i]->traverse();
		}

		cout << " " << Keys[i];
	}

	if (IsLeaf == false)
	{
		ChildPointer[i]->traverse();
	}
}

BTreeNode* BTreeNode::search(int k)
{
	int i = 0;
	while (i < NumOfKeys && k > Keys[i])
	{
		i++;
	}
	if (Keys[i] == k)
	{
		return this;
	}
	if (IsLeaf == true)
	{
		return NULL;
	}

	return ChildPointer[i]->search(k);
}

void BTree::remove(int k)
{
	if (!root)
	{
		cout << "The tree is empty " << endl;;
		return;
	}

	root->remove(k);

	if (root->NumOfKeys == 0)
	{
		BTreeNode* tmp = root;
		if (root->IsLeaf)
		{
			root = NULL;
		}
		else
		{
			root = root->ChildPointer[0];
		}

		delete tmp;
	}
	return;
}
