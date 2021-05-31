#include "gtest.h"
#include "../Tables/HashTable.h"

TEST(THashTable, can_create_hash_table)
{
	ASSERT_NO_THROW(THashTable at);
}

TEST(THashTable, can_get_current_record)
{
	THashTable table;
	ASSERT_NO_THROW(table.GetCurr());
}

TEST(THashTable, can_get_data_count)
{
	THashTable table;
	ASSERT_NO_THROW(table.GetDataCount());
}

TEST(THashTable, can_find_the_record)
{
	TRecord rec;
	THashTable table;
	ASSERT_NO_THROW(table.Find(rec.key));
}

TEST(THashTable, cant_find_the_unexisting_record)
{
	TRecord rec;
	THashTable table;
	ASSERT_NO_THROW(!table.Find(rec.key));
}

TEST(THashTable, find_increases_efficiency)
{
	TRecord rec, rec1;
	THashTable* table = new THashTable;
	table->Insert(rec);
	table->Find(rec1.key);
	EXPECT_NE(0, table->GetEff());
}

TEST(THashTable, can_delete_the_record)
{
	TRecord rec, rec1;
	rec.key = 1;
	rec.val = 5;
	THashTable* table = new THashTable;
	table->Insert(rec);
	ASSERT_NO_THROW(table->Delete(rec.key));
}

TEST(THashTable, cant_delete_the_record_in_an_empty_table)
{
	TRecord rec;
	THashTable table(0);
	ASSERT_ANY_THROW(table.Delete(rec.key));
}

TEST(THashTable, cant_delete_the_unexisting_record)
{
	TRecord rec, rec1;
	rec.key = 1;
	rec.val = 5;
	THashTable* table = new THashTable;
	table->Insert(rec);
	table->Delete(rec.key);
	EXPECT_EQ(0, table->GetDataCount());
}

TEST(THashTable, delete_increases_efficiency)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	THashTable* table = new THashTable;
	table->Insert(rec);
	table->Delete(rec.key);
	int eff = 0;
	EXPECT_NE(0, table->GetEff());
}

TEST(THashTable, delete_reduces_DataCount)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	THashTable* table = new THashTable;
	table->Insert(rec);
	table->Delete(rec.key);
	EXPECT_EQ(0, table->GetDataCount());
}

TEST(THashTable, can_insert_the_record)
{
	TRecord rec;
	THashTable table;
	ASSERT_NO_THROW(table.Insert(rec));
}

TEST(THashTable, insert_increases_efficiency)
{
	TRecord rec;
	THashTable* table = new THashTable;
	table->Insert(rec);
	EXPECT_NE(0, table->GetEff());
}

TEST(THashTable, insert_increases_DataCount)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	THashTable* table = new THashTable;
	table->Insert(rec);
	EXPECT_NE(0, table->GetDataCount());
}

TEST(THashTable, cant_insert_the_same_record)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	TRecord rec1;
	rec1.key = 1;
	rec1.val = 7;
	THashTable* table=new THashTable;
	table->Insert(rec);
	ASSERT_NO_THROW(!table->Insert(rec1));
}

TEST(THashTable, cant_insert_the_record_in_a_full_table)
{
	TRecord rec, rec1;
	rec.val = 1;
	rec.key = 5;
	THashTable table(1);
	table.Insert(rec);
	ASSERT_ANY_THROW(table.Insert(rec1));
}

TEST(THashTable, can_get_the_end_of_the_table)
{
	TRecord rec;
	THashTable table(1);
	table.Insert(rec);
	EXPECT_EQ(1, table.GetMaxSize());
}