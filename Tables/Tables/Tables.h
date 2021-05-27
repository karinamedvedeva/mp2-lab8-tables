#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef int TKey;
typedef int TVal;

struct TRecord
{
	TKey key;
	TVal val;
public:

	TRecord(TKey k = -1, TVal v = -1) 
	{
		key = k;
		val = v;
	};

	TRecord& operator=( TRecord& rec)
	{
		this->key = rec.key;
		this->val = rec.val;
		return *this;
	}

	friend istream& operator>>(istream& istr, TRecord& rec)
	{
		int _key, _val;
		istr >> _key;
		istr >> _val;
		rec.key = _key;
		rec.val = _val;
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TRecord& rec)
	{
		int k = rec.key;
		int v = rec.val;
		ostr << " | " << " " << k << " "  << " | " <<" " << v << " " << " | " <<endl;
		return ostr;
	}
};

class TTable
{
protected:
	int eff;
public:
	int DataCount;

	TTable()
	{
		DataCount = 0;
		eff = 0;
	}

	bool IsEmpty()
	{
		return DataCount == 0;
	}

	int GetEff()
	{
		return eff;
	}

	void ClearEff()
	{
		eff = 0;
	}

	virtual bool IsFull() = 0;
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TRecord rec) = 0;
	virtual void Delete(TKey key) = 0;
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual TRecord GetCurr() = 0;

	void Print()
	{
		//TRecord pCurr;
		cout << "----------------" << endl;
		for (Reset(); !IsEnd(); GoNext())
		{
			/*pCurr = GetCurr();
			cout << pCurr.val << endl;*/
		
			cout << GetCurr();
		}
		cout << "----------------";
	}
};

template<class TRecord>
class TArrayTable:public TTable
{
protected:
	TRecord* pRec;
	int Curr;
public:
	int size;

	TArrayTable(int _size = 1000) : TTable()
	{
		pRec = new TRecord[_size];
		size = _size;
		Curr = -1;
	}

	~TArrayTable()
	{
		delete[]pRec;
	}

	TArrayTable(const TArrayTable<TRecord>& nt)
	{
		size = nt.size;
		Curr = nt.Curr;
		pRec = new TRecord[size];
		for (int i = 0; i < size; i++)
		{
			pRec[i] = nt.pRec[i];
		}
	}

	TRecord& operator=(const TRecord& nt)
	{
		if (size != nt.size)
		{
			delete[]pRec;
			size = nt.size;
			pRec = new TRecord[nt.size];
		}
		for (int i = 0; i < size; i++)
		{
			pRec[i] = nt.pRec[i];
		}
		return *this;
	}

	bool IsFull()
	{
		return size == DataCount;
	}

	int GetSize()
	{
		return size;
	}

	TRecord GetCurr()
	{
		return pRec[Curr];
	}

	void Reset()
	{
		Curr = 0;
	}

	void GoNext()
	{
		Curr++;
	}

	bool IsEnd()
	{
		return Curr == DataCount;
	}
};

class TScanTable : public TArrayTable<TRecord>
{
public:
	TScanTable(int _size = 1000) : TArrayTable(_size) {}

	bool Find(TKey k)
	{
		bool flag = false;
		for (int i = 0; i < DataCount; i++)
		{
			if (pRec[i].key == k)
			{
				flag = true;
				Curr = i;
				break;
			}
			eff++;
		}
		if (!flag)
			Curr = DataCount;
		return flag;
	}
	  
	void Delete(TKey k)
	{
		if (Find(k))
		{
			pRec[Curr] = pRec[DataCount - 1];
			DataCount--;
			eff++;
		}
	}

	bool Insert(TRecord rec)
	{
		if (!Find(rec.key))
		{
			pRec[Curr] = rec;
			DataCount++;
			eff++;
			return true;
		}
		return false;
	}
};

class TSortTable : public TScanTable
{
private:
	void QuickSort(int left, int right)
	{
		int x, l = left, r = right, tmp;
		x = (left + right) / 2;
		TKey key = pRec[x].key;
		while (l < r)
		{
			while (pRec[l].key < key)
			{
				l++; 
				eff++;
			}
			while (pRec[r].key > key)
			{
				r--;
				eff++;
			}
			if (l <= r)
			{
				tmp = pRec[r].key;
				pRec[r].key = pRec[l].key;
				pRec[l].key = tmp;
			}
			eff++;
		}
		if (left < r)
			QuickSort(left, r);
		if (right > l)
			QuickSort(l, right);
	}
public:
	TSortTable(int _size = 1000) : TScanTable(_size) {}

	bool Find(TKey k)
	{
		bool flag = false;
		int first = 0, last = DataCount - 1, mid;
		while (first <= last)
		{
			eff++;
			mid = (first + last) / 2;
			if (pRec[mid].key == k)
			{
				Curr = mid;
				flag = true;
				break;
			}
			else
			{
				if (pRec[mid].key > k)
					last = mid - 1;
				else
					first = mid + 1;
			}
		}
		if (flag == false)
			Curr = first;
		return flag;
	}

	bool Insert(TRecord rec)
	{
		if (Find(rec.key))
			return false;
		else
		{
			for (int i = DataCount - 1; i >= Curr; i--)
			{
				pRec[i + 1] = pRec[i];
				eff++;
			}
			pRec[Curr] = rec;
			DataCount++;
			return true;
		}
	}

	void Delete(TKey k)
	{
		if (Find(k))
		{
			for (int i = Curr; i < DataCount; i++)
			{
				pRec[i] = pRec[i + 1];
				eff++;
			}
			DataCount--; 
		}
	}

	/*void operator=(const TScanTable& st)
	{
		if (size != st.size)
		{
			delete[]pRec;
			pRec = new TRecord[st.size];
			size = st.size;
			DataCount = st.DataCount;
		}
		for ()
	}*/

};