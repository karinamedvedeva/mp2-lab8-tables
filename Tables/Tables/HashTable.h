#pragma once
#include "Tables.h"
#include <string>

class THashTable : public TTable
{
protected:
	int MaxSize, Curr, DellPos, step;
	TRecord* mas;
	const int free = -1;
	const int del = -2;

	int HashFunc(TKey k)
	{
		return k % MaxSize;
	}

public:
	THashTable(int s=1000)
	{
		MaxSize = s;
		step = 1;
		Curr = NULL;
		mas = new TRecord[s];
		for (int i = 0; i < MaxSize; i++)
			mas[i].key = -1;
		DellPos = -1;
	}

	bool Find(TKey k)
	{
		DellPos = -1;
		Curr = HashFunc(k);
		for (int i = 0; i < MaxSize; i++)
		{
			eff++;
			if (mas[Curr].key == k)
				return true;
			else
				if (mas[Curr].key == del && DellPos == -1)
					DellPos = Curr;
				else
					if (mas[Curr].key == free)
						break;
			Curr = (Curr + step) % MaxSize;
		}
		if (DellPos != -1)
			Curr = DellPos;
		return false;
	}

	bool Insert(TRecord rec)
	{
		if (IsFull())
			throw 0;
		if (!Find(rec.key))
		{
			mas[Curr] = rec;
			DataCount++;
			eff++;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Delete(TKey k)
	{
		if (IsEmpty())
			throw 0;
		if (Find(k))
		{
			DataCount--;
			mas[Curr].key = del;
			eff++;
		}
	}

	void Reset()
	{
		for (Curr = 0; Curr < MaxSize; Curr++)
		{
			if (mas[Curr].key != free && mas[Curr].key != del)
				break;
		}
	}

	void GoNext()
	{
		for (Curr++; Curr < MaxSize; Curr++)
		{
			if (mas[Curr].key != free && mas[Curr].key != del)
				break;
		}
	}

	bool IsEnd()
	{
		return Curr == MaxSize;
	}

	TRecord GetCurr()
	{
		return mas[Curr];
	}

	bool IsFull()
	{
		return MaxSize == DataCount;
	}

	int GetMaxSize()
	{
		return MaxSize;
	}
};