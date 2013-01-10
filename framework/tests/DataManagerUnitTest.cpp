#include "gtest/gtest.h"
#include "DataManager.h"

using namespace mtr; 

class DataManagerTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        data_manager_ = new DataManager();
    }

    virtual void TearDown() {
        delete data_manager_;
    }

    DataManager * data_manager_;
};

TEST_F(DataManagerTest, PublishSymbolTest)
{
    SymbolHandle first_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbol("INTC", & first_handle));
    EXPECT_NE(0, first_handle);

    SymbolHandle second_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbol("AAPL", & second_handle));
    EXPECT_NE(0, second_handle);

    // Different symbols should have different handles.
    EXPECT_NE(first_handle, second_handle);

    SymbolHandle third_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbol("INTC", & third_handle));
    EXPECT_NE(0, third_handle);

    // The same symbol should get the same handle.
    EXPECT_EQ(first_handle, third_handle);
}

TEST_F(DataManagerTest, PublishSymbolAttributeTest)
{
    SymbolHandle first_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbolAttribute("Avg", & first_handle));
    EXPECT_NE(0, first_handle);

    SymbolHandle second_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbolAttribute("High", & second_handle));
    EXPECT_NE(0, second_handle);

    // Different symbols should have different handles.
    EXPECT_NE(first_handle, second_handle);

    SymbolHandle third_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbolAttribute("Avg", & third_handle));
    EXPECT_NE(0, third_handle);

    // The same symbol should get the same handle.
    EXPECT_EQ(first_handle, third_handle);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
