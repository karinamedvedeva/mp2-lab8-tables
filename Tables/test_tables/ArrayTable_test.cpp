#include "gtest.h"
#include "../Tables/Tables.h"

TEST(TScanTable, can_create_scan_table)
{
	ASSERT_NO_THROW(TScanTable at);
}

TEST(TScanTable, can_get_current_record)
{
	TScanTable table;
	ASSERT_NO_THROW(table.GetCurr());
}

TEST(TScanTable, can_get_data_count)
{
	TScanTable table;
	ASSERT_NO_THROW(table.GetDataCount());
}

TEST(TScanTable, can_find_the_record)
{
	TRecord rec;
	TScanTable table;
	ASSERT_NO_THROW (table.Find(rec.key));
}

TEST(TScanTable, cant_find_the_unexisting_record)
{
	TRecord rec, rec1;
	TScanTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(!table.Find(rec1.key));
}

TEST(TScanTable, find_increases_efficiency)
{
	TRecord rec, rec1;
	TScanTable* table = new TScanTable;
	table->Insert(rec);
	table->Find(rec1.key);
	EXPECT_NE(0, table->GetEff());
}

TEST(TScanTable, can_delete_the_record)
{
	TRecord rec;
	TScanTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(table.Delete(rec.key));
}

TEST(TScanTable, cant_delete_the_record_in_an_empty_table)
{
	TRecord rec;
	TScanTable table(0);
	ASSERT_ANY_THROW(table.Delete(rec.key));
}

////////////////////////
TEST(TScanTable, cant_delete_the_unexisting_record)
{
	TRecord rec, rec1;
	rec.key = 1;
	rec.val = 5;
	TScanTable table;
	table.Insert(rec);
	table.Delete(rec.key);
	EXPECT_EQ(0, table.GetDataCount());
}

TEST(TScanTable, delete_increases_efficiency)
{
	TRecord rec;
	TScanTable* table = new TScanTable;
	table->Insert(rec);
	table->Delete(rec.key);
	int eff = 0;
	EXPECT_NE(0, table->GetEff());
}

TEST(TScanTable, delete_reduces_DataCount)
{
	TRecord rec;
	TScanTable* table = new TScanTable;
	table->Insert(rec);
	table->Delete(rec.key);
	EXPECT_EQ(0, table->GetDataCount());
}

TEST(TScanTable, can_insert_the_record)
{
	TRecord rec;
	TScanTable table;
	ASSERT_NO_THROW(table.Insert(rec));
}

TEST(TScanTable, cant_insert_the_record_in_a_full_table)
{
	TRecord rec;
	TScanTable table(1);
	table.Insert(rec);
	ASSERT_ANY_THROW(table.Insert(rec));
}

TEST(TScanTable, insert_increases_efficiency)
{
	TRecord rec;
	TScanTable* table=new TScanTable;
	table->Insert(rec);
	int eff = 0;
	EXPECT_NE(0, table->GetEff());
}

TEST(TScanTable, insert_increases_DataCount)
{
	TRecord rec;
	TScanTable* table = new TScanTable;
	table->Insert(rec);
	EXPECT_NE(0, table->GetDataCount());
}

TEST(TScanTable, cant_insert_the_same_record)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	TRecord rec1;
	rec1.key = 1;
	rec1.val = 7;
	TScanTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(!table.Insert(rec1));
}

TEST(TScanTable, can_get_the_end_of_the_table)
{
	TRecord rec;
	TScanTable* table = new TScanTable;
	table->Insert(rec);
	EXPECT_EQ(1, table->GetDataCount());
}

TEST(TSortTable, can_create_sort_table)
{
	ASSERT_NO_THROW(TSortTable at);
}

TEST(TSortTable, can_get_current_record)
{
	TSortTable table;
	ASSERT_NO_THROW(table.GetCurr());
}

TEST(TSortTable, can_get_data_count)
{
	TSortTable table;
	ASSERT_NO_THROW(table.GetDataCount());
}

TEST(TSortTable, can_find_the_record)
{
	TRecord rec;
	TSortTable table;
	ASSERT_NO_THROW(table.Find(rec.key));
}

TEST(TSortTable, cant_find_the_unexisting_record)
{
	TRecord rec, rec1;
	TSortTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(!table.Find(rec1.key));
}

TEST(TSortTable, find_increases_efficiency)
{
	TRecord rec, rec1;
	TSortTable* table = new TSortTable;
	table->Insert(rec);
	table->Find(rec1.key);
	EXPECT_NE(0, table->GetEff());
}

TEST(TSortTable, can_delete_the_record)
{
	TRecord rec;
	TSortTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(table.Delete(rec.key));
}

TEST(TSortTable, cant_delete_the_record_in_an_empty_table)
{
	TRecord rec;
	TSortTable table(0);
	ASSERT_ANY_THROW(table.Delete(rec.key));
}

TEST(TSortTable, cant_delete_the_unexisting_record)
{
	TRecord rec, rec1;
	rec.key = 1;
	rec.val = 5;
	TSortTable table;
	table.Insert(rec);
	table.Delete(rec.key);
	EXPECT_EQ(0, table.GetDataCount());
}

TEST(TSortTable, delete_increases_efficiency)
{
	TRecord rec;
	TSortTable* table = new TSortTable;
	table->Insert(rec);
	table->Delete(rec.key);
	int eff = 0;
	EXPECT_NE(0, table->GetEff());
}

TEST(TSortTable, delete_reduces_DataCount)
{
	TRecord rec;
	TSortTable* table = new TSortTable;
	table->Insert(rec);
	table->Delete(rec.key);
	EXPECT_EQ(0, table->GetDataCount());
}

TEST(TSortTable, can_insert_the_record)
{
	TRecord rec;
	TSortTable table;
	ASSERT_NO_THROW(table.Insert(rec));
}

TEST(TSortTable, insert_increases_DataCount)
{
	TRecord rec;
	TSortTable* table = new TSortTable;
	table->Insert(rec);
	EXPECT_NE(0, table->GetDataCount());
}

TEST(TSortTable, cant_insert_the_record_in_a_full_table)
{
	TRecord rec;
	TSortTable table(1);
	table.Insert(rec);
	ASSERT_ANY_THROW(table.Insert(rec));
}

TEST(TSortTable, insert_increases_efficiency)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	TSortTable* table = new TSortTable;
	table->Insert(rec);
	EXPECT_NE(1, table->GetEff());
}

TEST(TSortTable, cant_insert_the_same_record)
{
	TRecord rec;
	rec.key = 1;
	rec.val = 5;
	TRecord rec1;
	rec1.key = 1;
	rec1.val = 7;
	TSortTable table;
	table.Insert(rec);
	ASSERT_NO_THROW(!table.Insert(rec1));
}

TEST(TSortTable, can_get_the_end_of_the_table)
{
	TRecord rec;
	TSortTable* table = new TSortTable;
	table->Insert(rec);
	EXPECT_EQ(1, table->GetDataCount());
}
