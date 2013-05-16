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

TEST_F(SqliteDataProviderTest, ReadYahooCSVTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_FAILURE, provider.ReadYahooCSVFile("ge.csv"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadYahooCSVFile("ge.csv"));
    system("rm test");
}

TEST_F(SqliteDataProviderTest, PublishSymbolTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadYahooCSVFile("ge.csv"));
    provider.PublishData(data_manager_);

    std::vector<std::pair<std::string, SymbolHandle> > symbols;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbols( & symbols ));
    EXPECT_EQ(1, symbols.size());
    if(0 < symbols.size()) {
        EXPECT_EQ("GE", symbols[0].first);
    }
}

TEST_F(SqliteDataProviderTest, PublishAttributeTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadYahooCSVFile("ge.csv"));
    provider.PublishData(data_manager_);

    std::vector<std::pair<std::string, SymbolHandle> > symbols;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbols( & symbols ));
    EXPECT_EQ(1, symbols.size());
    EXPECT_EQ("GE", symbols[0].first);
    std::vector<AttributeHandle> attribute_handles;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbolAttributes( 
        symbols[0].second,
        &attribute_handles ));
    EXPECT_EQ(6, attribute_handles.size());
}

TEST_F(SqliteDataProviderTest, PublishDataDatesTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadYahooCSVFile("ge.csv"));
    provider.PublishData(data_manager_);

    std::vector<std::pair<std::string, SymbolHandle> > symbols;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbols( & symbols ));
    ASSERT_EQ(1, symbols.size());
    EXPECT_EQ("GE", symbols[0].first);
    std::vector<AttributeHandle> attribute_handles;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbolAttributes( 
        symbols[0].second,
        &attribute_handles ));
    ASSERT_EQ(6, attribute_handles.size());
    for(std::vector<AttributeHandle>::const_iterator iter = attribute_handles.begin(); iter != attribute_handles.end(); iter++) {
        std::vector<Timestamp> dates;
        EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetDataDates(symbols[0].second, *iter, &dates));
        ASSERT_NE(0, dates.size());

    }
}

TEST_F(SqliteDataProviderTest, GetDataTest) {
    SqliteDataProvider provider;
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.OpenDatabase("test"));
    EXPECT_EQ(MTR_STATUS_SUCCESS, provider.ReadYahooCSVFile("ge.csv"));
    provider.PublishData(data_manager_);

    std::vector<std::pair<std::string, SymbolHandle> > symbols;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbols( & symbols ));
    ASSERT_EQ(1, symbols.size());
    EXPECT_EQ("GE", symbols[0].first);
    std::vector<AttributeHandle> attribute_handles;
    EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetSymbolAttributes( 
        symbols[0].second,
        &attribute_handles ));
    ASSERT_EQ(6, attribute_handles.size());
    for(std::vector<AttributeHandle>::const_iterator iter = attribute_handles.begin(); iter != attribute_handles.end(); iter++) {
        std::vector<Timestamp> dates;
        EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetDataDates(symbols[0].second, *iter, &dates));
        ASSERT_NE(0, dates.size());
        std::vector<std::pair<Timestamp, double> > data;
        EXPECT_EQ(MTR_STATUS_SUCCESS, data_manager_->GetData( symbols[0].second, *iter, dates, &data ));
        ASSERT_EQ(dates.size(), data.size());
    }
}
