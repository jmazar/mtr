#include "gtest/gtest.h"
#include "DataManager.h"
#include "sqlite_data_provider.h"
#include <stdlib.h>

using namespace mtr;

class SqliteDataProviderTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        data_manager_ = new DataManager();
    }

    virtual void TearDown() {
        delete data_manager_;
    }

    DataManager *           data_manager_;
};

TEST_F(SqliteDataProviderTest, LoadDBTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    system("rm test");
}

TEST_F(SqliteDataProviderTest, ReadCSVTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadCSVFile("aapl.csv"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadCSVFile("aapl.csv"));
    system("rm test");

}
