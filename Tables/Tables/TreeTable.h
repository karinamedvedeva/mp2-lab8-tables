#pragma once
#include "Tables.h"
#include <stack>

struct TNode : public TRecord
{
public:
	TNode* pLeft, * pRight;
	TRecord rec;
	TNode()
	{
		pLeft = pRight = NULL;
		rec.key = 0;
		rec.val = 0;
	}
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
	stack<TNode*> st;
	int pos;
public:

	TTreeTable()
	{
		pRoot = NULL;
		pCurr = NULL;
		pPrev = NULL;
		pos = 0;
	}

	bool Find(TKey key)
	{
		pCurr = pRoot;
		pPrev = NULL;
		while (pCurr)
		{
			eff++;
			if (pCurr->rec.key == key)
				return true;
			else
			{
				pPrev = pCurr;
				if (pCurr->rec.key > key)
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
		if (IsFull())
			throw 0;
		if (Find(rec.key))
		{	
			return false;
		}
		else
		{
			eff++;
			DataCount++;
			TNode* tmp = new TNode(rec);
			if (pRoot == NULL)
				pRoot = tmp;
			else
			{
				if (pCurr->rec.key > rec.key)
					pCurr->pLeft = tmp;
				else
					pCurr->pRight = tmp;
			}
			return true;
		}
	}
	
	////////////////////////////////////////////
	/*void Delete(TKey key)
	{
		if (IsEmpty())
			throw 0;
		if (Find(key))
		{
		DataCount--;
		eff++;
			if (!pCurr->pLeft && !pCurr->pRight)
			{
			if (pPrev!=NULL)
			{
				if (pPrev->pLeft == pCurr)
					pPrev->pLeft = NULL;
				else
					pPrev->pRight = NULL;
			}
			else 
			pRoot=NULL;
				delete pCurr;
			}
			else
			{
				if (pCurr->pLeft && !pCurr->pRight)
				{
				if (pPrev!=NULL)
				{
					if (pPrev->pLeft == pCurr)
						pPrev->pLeft = pCurr->pLeft;
					else
						pPrev->pRight = pCurr->pLeft;
				}
				else 
				pRoot =NULL;
					delete pCurr;
				}
				else
				{
					if (!pCurr->pLeft && pCurr->pRight)
					{
                        if (pPrev!=NULL)
						{
						if (pPrev->pRight == pCurr)
							pPrev->pRight = pCurr->pRight;
						else
							pPrev->pLeft = pCurr->pRight;
							}
							else
							pRoot=NULL;
						delete pCurr;
					}
					else
					

					//if (pCurr->pLeft && pCurr->pRight)
					{
						TNode* tmp = pCurr->pLeft;
						pPrev = pCurr;
						while (tmp->pRight != NULL)
						{
						eff++;
							pPrev = tmp;
							tmp = tmp->pRight;
						}
						pCurr->val = tmp->val;
						pCurr->key = tmp->key;
						//if (pPrev->pLeft == tmp)
						if (pPrev!=pCurr)
							pPrev->pLeft = tmp->pLeft;
						else
							pPrev->pRight = tmp->pLeft;
						delete tmp;
					
					}
					}
			}
		}
	}*/

	void Delete(TKey key)
	{
		if (IsEmpty())
			throw 0;
		if (Find(key))
		{
			DataCount--;
			eff++;
			if (!pCurr->pLeft && !pCurr->pRight)
			{
				TNode* tmp = pCurr;
				if (pPrev)
				{
					if (pPrev->pLeft == pCurr)
						pPrev->pLeft = NULL;
					else
						pPrev->pRight = NULL;
				}
				else
					pRoot = NULL;
				delete tmp;
			}
			else
			{
				if (pCurr->pLeft && !pCurr->pRight)
				{
					TNode* tmp = pCurr;
					if (pPrev)
					{
						if (pPrev->pLeft == pCurr)
							pPrev->pLeft = pCurr->pLeft;
						else
							pPrev->pRight = pCurr->pLeft;
					}
					else
						pRoot = NULL;
					delete tmp;
				}
				else
				{
					if (!pCurr->pLeft && pCurr->pRight)
					{
						TNode* tmp = pCurr;
						if (pPrev)
						{
							if (pPrev->pLeft == pCurr)
								pPrev->pLeft = pCurr->pRight;
							else
								pPrev->pRight = pCurr->pRight;
						}
						else
							pRoot = NULL;
						delete tmp;
					}

					else 
					{
						TNode* tmp = pCurr->pLeft;
						pPrev = pCurr;
						while (tmp->pRight != NULL)
						{
							eff++;
							pPrev = tmp;
							tmp = tmp->pRight;
						}
						pCurr->rec = tmp->rec;
						if (pPrev != pCurr)
							pPrev->pRight = tmp->pLeft;
						else
							pPrev->pLeft = tmp->pLeft;
						delete tmp;
					}
				}
			}
		}
		else
			throw 0;
	}


	void Reset()
	{
		while (!st.empty())
			st.pop();
		pCurr = pRoot;
		pos = 0;
		if (pCurr!=NULL) {
			while (pCurr->pLeft!=NULL)
			{
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
		st.push(pCurr);
	}

	void GoNext()
	{
		/*if (!st.empty())
			st.pop();
		pos++;
		if (pCurr->pRight != NULL)
		{
			pCurr = pCurr->pRight;
			while (pCurr->pLeft != NULL)
			{
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			st.push(pCurr);
		}
		else
			if (!st.empty())
			{
				pCurr = st.top();
				//st.pop();
			}
			*/
		if (pCurr) {
			TNode* tmp = pCurr = pCurr->pRight;
			if (!st.empty())
				st.pop();
			while (tmp)
			{
				st.push(tmp);
				pCurr = tmp;
				tmp = tmp->pLeft;
			}
			if (!pCurr && !st.empty())
			{
				pCurr = st.top();
				//st.pop();
			}
			pos++;
		}
	}

	bool IsEnd()
	{
		return (pos == DataCount);
	}

	bool IsFull()
	{
	 return false;
	}

	TRecord GetCurr()
	{
		return pCurr->rec;
	}

};