#include "gtest.h"
#include "../Tables/TreeTable.h"

TEST(TTreeTable, can_create_tree_table)
{
	ASSERT_NO_THROW(TTreeTable at);
}

TEST(TTreeTable, can_get_data_count)
{
	TTreeTable table;
	ASSERT_NO_THROW(table.GetDataCount());
}

TEST(TTreeTable, can_find_the_record)
{
	TRecord rec;
	TTreeTable table;
	ASSERT_NO_THROW(table.Find(rec.key));
}

TEST(TTreeTable, cant_find_the_unexisting_record)
{
	TRecord rec;
	TTreeTable table;
	ASSERT_NO_THROW(!table.Find(rec.key));
}

TEST(TTreeTable, find_increases_efficiency)
{
	TRecord rec, rec1;
	TTreeTable* table = new TTreeTable;
	table->Insert(rec);
	table->Find(rec1.key);
	EXPECT_NE(0, table->GetEff());
}

TEST(TTreeTable, can_delete_the_record)
{
	TRecord rec;
	TTreeTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(table.Delete(rec.key));
}

TEST(TTreeTable, cant_delete_the_record_in_an_empty_table)
{
	TRecord rec;
	TTreeTable table;
	ASSERT_ANY_THROW(table.Delete(rec.key));
}

TEST(TTreeTable, cant_delete_the_unexisting_record)
{
	TRecord rec, rec1;
	rec.key = 1;
	rec.val = 5;
	TTreeTable table;
	table.Insert(rec);
	ASSERT_ANY_THROW(table.Delete(rec1.key));
}

TEST(TTreeTable, delete_increases_efficiency)
{
	TRecord rec;
	TTreeTable* table = new TTreeTable;
	table->Insert(rec);
	table->Delete(rec.key);
	EXPECT_NE(0, table->GetEff());
}

TEST(TTreeTable, delete_reduces_DataCount)
{
	TRecord rec, rec1;
	rec.key = 1; rec1.key = 11;
	rec.val = 5; rec1.val = 15;
	TTreeTable* table = new TTreeTable;
	table->Insert(rec);
	table->Insert(rec1);
	table->Delete(rec.key);
	EXPECT_EQ(1, table->GetDataCount());
}

TEST(TTreeTable, can_insert_the_record)
{
	TRecord rec;
	TTreeTable table;
	ASSERT_NO_THROW(table.Insert(rec));
}

TEST(TTreeTable, insert_increases_efficiency)
{
	TRecord rec;
	TTreeTable* table = new TTreeTable;
	table->Insert(rec);
	int eff = 0;
	EXPECT_NE(0, table->GetEff());
}

TEST(TTreeTable, insert_increases_DataCount)
{
	TRecord rec;
	TTreeTable* table = new TTreeTable;
	table->Insert(rec);
	EXPECT_NE(0, table->GetDataCount());
}

TEST(TTreeTable, cant_insert_the_same_record)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	TRecord rec1;
	rec1.key = 1;
	rec1.val = 7;
	TTreeTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(!table.Insert(rec1));
}

TEST(TTreeTable, can_get_the_end_of_the_table)
{
	TRecord rec;
	TTreeTable* table = new TTreeTable;
	table->Insert(rec);
	EXPECT_EQ(1, table->GetDataCount());
}