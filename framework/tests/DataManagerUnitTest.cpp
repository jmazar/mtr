#include "gtest/gtest.h"
#include "DataManager.h"

class DataManagerTest : public ::testing:Test 
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
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->PublishSymbol("INTC"));

    std::vector<std::string> symbols;

    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbolNames( symbols );
    EXPECT_EQ(1, symbols.size());
}

