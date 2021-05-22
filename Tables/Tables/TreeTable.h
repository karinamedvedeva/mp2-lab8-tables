#pragma once
#include "Tables.h"
#include <stack>

struct TNode : public TRecord
{
	TNode* pLeft, * pRight;
	TRecord rec;
	TNode(TRecord _rec, TNode* _pLeft = NULL, TNode* _pRight = NULL)
	{
		rec = _rec;
		pLeft = _pLeft;
		pRight = _pRight;
	}
};

class TTreeTable : public TTable
{
protected:
	TNode* pRoot, * pCurr, * pPrev;
	stack<TNode> st;
public:
	bool Find(TKey k)
	{
		pCurr = pRoot;
		pPrev = NULL;
		while (pCurr)
		{
			eff++;
			if (pCurr->key == k)
				break;
			else
			{
				pPrev = pCurr;
				if (pCurr->key > k)
					pCurr = pCurr->pLeft;
				else
					pCurr = pCurr->pRight;
			}
		}
		if (pCurr)
			return true;
		else
		{
			pCurr = pPrev;
			return false;
		}
	}

	bool Insert(TRecord rec)
	{
		if (Find(rec.key))
			return false;
		eff++;
		DataCount++;
		TNode* tmp = new TNode(rec);
		if (pRoot == NULL)
			pRoot = tmp;
		else
		{
			if (pCurr->key > rec.key)
				pCurr->pLeft = tmp;
			else
				pCurr->pRight = tmp;
			return true;
		}
	}

	void Delete(TKey k)
	{
		if (Find(k))
		{
			if (!pCurr->pLeft && !pCurr->pRight)
			{
				if (pPrev->pLeft == pCurr)
					pPrev->pLeft = NULL;
				else
					pPrev->pRight = NULL;
				delete pCurr;
			}
			else
			{
				if (pCurr->pLeft && !pCurr->pRight)
				{
					if (pPrev->pLeft == pCurr)
						pPrev->pLeft = pCurr->pLeft;
					else
						pPrev->pRight = pCurr->pLeft;
					delete pCurr;
				}
				else
				{
					TNode* tmp = pCurr->pLeft;
					pPrev = pCurr;
					while (tmp->pRight != NULL)
					{
						pPrev = tmp;
						tmp = tmp->pRight;
					}
					pCurr->val = tmp->val;
					pCurr->key = tmp->key;
					if (pPrev->pLeft == tmp)
						pPrev->pLeft = tmp->pLeft;
					else
						pPrev->pRight = tmp->pLeft;
					delete tmp;
				}
				DataCount--;
			}
		}
	}
};