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
	cout << "Введите максимальный размер таблицы: ";
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
		cout << endl<<"1. Создать таблицу" << endl << "2. Выбрать вид таблицы и вывести ее на экран" << endl << "3. Вставить запись" << endl << "4. Поиск записи по ключу" << endl<<"5. Удалить запись"<<endl;
		cout << "Выберите номер операции: ";
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "Введите размер таблицы: ";
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
			cout <<endl<< "1. Таблица на основе неупорядоченного массива" << endl << "2. Таблица на основе упорядоченного массива" << endl << "3. Таблица на основе дерева" << endl << "4. Хэш-таблица" << endl;
			cout << "Выберите вид таблицы: ";
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
			cout << "Введите запись для добавления: ";
			cin >> pRec;
			table->Insert(pRec);
			table->Print();
			cout << "Эффективность операции вставки: " << table->GetEff() << endl;
			break;
		case 4:
			table->ClearEff();
			cout << "Введите ключ для поиска записи: ";
			cin >> key;
			if (table->Find(key))
			{
				cout << table->GetCurr() << endl;
				cout << "Эффективность операции поиска: " << table->GetEff() << endl;
			}
			else
			{
				cout << "Данная запись отсутвует" << endl;
				cout << "Эффективность операции поиска: " << table->GetEff() << endl;
			}
			break;
		case 5:
			table->ClearEff();
			cout << "Введите ключ записи для ее удаления: ";
			cin >> key;
			table->Delete(key);
			table->Print();
			cout << "Эффективность операции удаления: " << table->GetEff() << endl;
			break;
		}
	} while (a != 0);
}