#include "gtest.h"
#include "../Tables/Tables.h"

TEST(TRecord, can_create_a_record)
{
	ASSERT_NO_THROW(TRecord rec);
}

TEST(TRecord, can_assign_records)
{
	TRecord rec1, rec2;
	ASSERT_NO_THROW(rec1 = rec2);
}

TEST(TRecord, can_assign_record_to_itself)
{
	TRecord rec;
	ASSERT_NO_THROW(rec = rec);
}