#include "Tables.h"
#include "TreeTable.h"
#include "HashTable.h"
#include <iostream>
#include <locale>
#include <Windows.h>

int main()
{
	setlocale(LC_CTYPE, "Rus");
	int MaxSize,size, a, type; 
	int step=1;
	cout << "������� ������������ ������ �������: ";
	cin >> MaxSize;
	TScanTable* ScanTable=new TScanTable(MaxSize);
	TSortTable* SortTable = new TSortTable(MaxSize);
	TTreeTable* TreeTable = new TTreeTable;
	THashTable* HashTable = new THashTable(MaxSize);
	TTable* table = ScanTable;
	TKey key=0;
	TVal val=0;
	TRecord pRec;
	char fn[] = "C:\\Users\\karina\\OneDrive\\���������\\Projects\\mp2-lab8-tables\\Tables\\tables.txt";
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
			for (int i = 0; i < size; i++)
			{
				pRec.key = rand() % 1000;
				pRec.val = rand() % 1000;
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
				table->Save(fn);
				break;
			case 2: 
				table = SortTable;
				SortTable->Print();
				cout << endl;
				table->Save(fn);
				break;
			case 3:
				table = TreeTable;
				TreeTable->Print();
				cout << endl;
				table->Save(fn);
				break;
			case 4:
				table = HashTable;
				HashTable->Print();
				cout << endl;
				table->Save(fn);
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
			table->Save(fn);
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
			table->Save(fn);
			break;
		case 5:
			table->ClearEff();
			cout << "������� ���� ������ ��� �� ��������: ";
			cin >> key;
			table->Delete(key);
			table->Print();
			cout << "������������� �������� ��������: " << table->GetEff() << endl;
			table->Save(fn);
			break;
		}
	} while (a != 0);
}