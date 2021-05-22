#include "Tables.h"
#include <iostream>
#include <locale>

int main()
{
	setlocale(LC_CTYPE, "Rus");
	int size, a, type; 
	cout << "������� ������ �������: ";
	cin >> size;
	TScanTable* ScanTable=new TScanTable(size);
	TSortTable* SortTable = new TSortTable(size);
	TTable* table = ScanTable;
	TKey key=0;
	TVal val=0;
	TRecord pRec;
	do
	{
		cout << "1. ������� ��� �������" << endl << "2. ������� ������� �� �����" << endl;
		cout << "�������� ����� ��������: ";
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "1. ������� �� ������ ���������������� �������" << endl << "2. ������� �� ������ �������������� �������" << endl;
			cin >> type;
			switch (type)
			{
			case 1: 
				table = ScanTable;
				break;
			case 2: 
				table = SortTable;
				break;
			}
		case 2:
			switch (type)
			{
			case 1:
				ScanTable = new TScanTable(size);
				for (int i = 0; i < size; i++)
				{
					key += (rand() % 10);
					val += (rand() % 10);
					pRec.key = key;
					pRec.val = val;
					ScanTable->Insert(pRec);
				}
				ScanTable->Print();
				break;
			}
		}
	} while (a != 0);
}