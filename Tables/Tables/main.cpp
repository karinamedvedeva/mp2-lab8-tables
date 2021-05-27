#include "Tables.h"
#include "TreeTable.h"
#include "HashTable.h"
#include <iostream>
#include <locale>
#include <Windows.h>

void SetColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int main()
{
	setlocale(LC_CTYPE, "Rus");
	int size, a, type; 
	int step=1;
	cout << "������� ������������ ������ �������: ";
	cin >> size;
	TScanTable* ScanTable=new TScanTable(size);
	TSortTable* SortTable = new TSortTable(size);
	TTreeTable* TreeTable = new TTreeTable;
	THashTable* HashTable = new THashTable(size);
	TTable* table = ScanTable;
	TKey key=0;
	TVal val=0;
	TRecord pRec;
	do
	{
		cout << endl<<"1. ������� �������" << endl << "2. ������� ��� ������� � ������� �� �� �����" << endl << "3. �������� ������" << endl << "4. ����� ������ �� �����" << endl<<"5. ������� ������"<<endl;
		cout << "�������� ����� ��������: ";
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "������� ������ �������: ";
			cin >> size;
			ScanTable = new TScanTable(size);
			SortTable = new TSortTable(size);
			HashTable = new THashTable(size);
			TreeTable = new TTreeTable;
			table = ScanTable;
			for (int i = 0; i < size; i++)
			{
				pRec.key = rand() % 100;
				pRec.val = rand() % 10;
				ScanTable->Insert(pRec);
				SortTable->Insert(pRec);
				HashTable->Insert(pRec);
				TreeTable->Insert(pRec);
			}
			break;
		case 2:
			cout <<endl<< "1. ������� �� ������ ���������������� �������" << endl << "2. ������� �� ������ �������������� �������" << endl << "3. ������� �� ������ ������" << endl << "4. ���-�������" << endl;
			cout << "�������� ��� �������: ";
			cin >> type;
			switch (type)
			{
			case 1:
				table = ScanTable;
				ScanTable->Print();
				cout << endl;
				break;
			case 2: 
				table = SortTable;
				SortTable->Print();
				cout << endl;
				break;
			case 3:
				table = TreeTable;
				TreeTable->Print();
				cout << endl;
				break;
			case 4:
				table = HashTable;
				HashTable->Print();
				cout << endl;
				break;
			}
			break;
		case 3:
			table->ClearEff();
			cout << "������� ������ ��� ����������: ";
			cin >> pRec;
			table->Insert(pRec);
			table->Print();
			cout << "������������� �������� �������: " << table->GetEff() << endl;
			break;
		case 4:
			table->ClearEff();
			cout << "������� ���� ��� ������ ������: ";
			cin >> key;
			if (table->Find(key))
			{
				cout << table->GetCurr() << endl;
				cout << "������������� �������� ������: " << table->GetEff() << endl;
			}
			else
			{
				cout << "������ ������ ���������" << endl;
				cout << "������������� �������� ������: " << table->GetEff() << endl;
			}
			break;
		case 5:
			table->ClearEff();
			cout << "������� ���� ������ ��� �� ��������: ";
			cin >> key;
			table->Delete(key);
			table->Print();
			cout << "������������� �������� ��������: " << table->GetEff() << endl;
			break;
		}
	} while (a != 0);
}