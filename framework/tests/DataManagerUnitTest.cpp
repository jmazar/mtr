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

TEST_F(DataManagerTest, PublishAttributeTest)
{
    AttributeHandle first_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishAttribute("Avg", & first_handle));
    EXPECT_NE(0, first_handle);

    AttributeHandle second_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishAttribute("High", & second_handle));
    EXPECT_NE(0, second_handle);

    // Different symbols should have different handles.
    EXPECT_NE(first_handle, second_handle);

    AttributeHandle third_handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishAttribute("Avg", & third_handle));
    EXPECT_NE(0, third_handle);

    // The same symbol should get the same handle.
    EXPECT_EQ(first_handle, third_handle);
}

TEST_F(DataManagerTest, GetSymbolsTest)
{
    SymbolHandle handle = 0;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbol( "INTC", & handle ));

    std::vector<std::string> symbols;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbols( & symbols ));
    EXPECT_EQ(1, symbols.size());
    EXPECT_EQ("INTC", symbols[0]);
}

TEST_F(DataManagerTest, PublishSymbolAttributeTest)
{
    SymbolHandle    symbol_handle = 0;
    AttributeHandle attribute_handle = 0;

    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbol( "INTC", & symbol_handle));
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishAttribute("Avg", & attribute_handle));
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbolAttribute( symbol_handle, attribute_handle ));

    std::vector<AttributeHandle> attribute_handles;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbolAttributes( symbol_handle, & attribute_handles ));
    EXPECT_EQ(1, attribute_handles.size());

    EXPECT_EQ(MTR_STATUS_FAILURE, data_manager_->GetSymbolAttributes( symbol_handle, NULL ));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
