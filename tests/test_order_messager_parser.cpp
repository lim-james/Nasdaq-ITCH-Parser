#include <gtest/gtest.h>

#include "nasdaq/modify_order_messages.h"
#include "nasdaq/add_order_messages.h"
#include "nasdaq/stock_related_messages.h"
#include "nasdaq/net_order_balance_indicator_message.h"
#include "nasdaq/system_event_message.h"
#include "nasdaq/dlcr_message.h"
#include "nasdaq/retail_interest_message.h"
#include "nasdaq/trade_messages.h"
#include "order_message_parser.h"

TEST(OrderMessageParser, ValidOrderExecutedMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1F,
        /* message_type           = 'E'   */ 0x45, 
        /* stock_locate           = 42    */ 0x00, 0x2A, 
        /* tracking_number        = 67    */ 0x00, 0x43, 
        /* timestamp              = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* order_reference_number = 43567 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
        /* executed_shares        = 100   */ 0x00, 0x00, 0x00, 0x64, 
        /* match_number           = 6790  */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x86 
    };

    auto result = parse<nasdaq::OrderExecutedMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'E');
    EXPECT_EQ((*result)->stock_locate,           42);
    EXPECT_EQ((*result)->tracking_number,        67);
    EXPECT_EQ((*result)->timestamp,              12345);
    EXPECT_EQ((*result)->order_reference_number, 43567);
    EXPECT_EQ((*result)->executed_shares,        100);
    EXPECT_EQ((*result)->match_number,           6790);
}

TEST(OrderMessageParser, ValidOrderExecutedWithPriceMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1F,
        /* message_type           = 'C'   */ 0x43, 
        /* stock_locate           = 42    */ 0x00, 0x2A, 
        /* tracking_number        = 67    */ 0x00, 0x43, 
        /* timestamp              = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* order_reference_number = 43567 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
        /* executed_shares        = 100   */ 0x00, 0x00, 0x00, 0x64, 
        /* match_number           = 6790  */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x86,
        /* printable              = 'Y'   */ 0x59,
        /* execution_price        = 98765 */ 0x00, 0x01, 0x81, 0xCD 
    };

    auto result = parse<nasdaq::OrderExecutedWithPriceMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'C');
    EXPECT_EQ((*result)->stock_locate,           42);
    EXPECT_EQ((*result)->tracking_number,        67);
    EXPECT_EQ((*result)->timestamp,              12345);
    EXPECT_EQ((*result)->order_reference_number, 43567);
    EXPECT_EQ((*result)->executed_shares,        100);
    EXPECT_EQ((*result)->match_number,           6790);
    EXPECT_EQ((*result)->printable,              'Y');
    EXPECT_EQ((*result)->execution_price,        98765);
}

TEST(OrderMessageParser, ValidOrderCancelMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1F,
        /* message_type           = 'X'   */ 0x58, 
        /* stock_locate           = 42    */ 0x00, 0x2A, 
        /* tracking_number        = 67    */ 0x00, 0x43, 
        /* timestamp              = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* order_reference_number = 43567 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
        /* cancelled_shares       = 100   */ 0x00, 0x00, 0x00, 0x64, 
    };

    auto result = parse<nasdaq::OrderCancelMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'X');
    EXPECT_EQ((*result)->stock_locate,           42);
    EXPECT_EQ((*result)->tracking_number,        67);
    EXPECT_EQ((*result)->timestamp,              12345);
    EXPECT_EQ((*result)->order_reference_number, 43567);
    EXPECT_EQ((*result)->cancelled_shares,       100);
}

TEST(OrderMessageParser, ValidOrderDeleteMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1F,
        /* message_type           = 'D'   */ 0x44, 
        /* stock_locate           = 42    */ 0x00, 0x2A, 
        /* tracking_number        = 67    */ 0x00, 0x43, 
        /* timestamp              = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* order_reference_number = 43567 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
    };

    auto result = parse<nasdaq::OrderDeleteMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'D');
    EXPECT_EQ((*result)->stock_locate,           42);
    EXPECT_EQ((*result)->tracking_number,        67);
    EXPECT_EQ((*result)->timestamp,              12345);
    EXPECT_EQ((*result)->order_reference_number, 43567);
}

TEST(OrderMessageParser, ValidOrderReplaceMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1F,
        /* message_type           = 'U'   */ 0x55, 
        /* stock_locate           = 42    */ 0x00, 0x2A, 
        /* tracking_number        = 67    */ 0x00, 0x43, 
        /* timestamp              = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* original_order_reference_number = 43567 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
        /* new_order_reference_number = 43567 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
        /* shares        = 100   */ 0x00, 0x00, 0x00, 0x64, 
        /* price         = 98765 */ 0x00, 0x01, 0x81, 0xCD 
    };

    auto result = parse<nasdaq::OrderReplaceMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,                    'U');
    EXPECT_EQ((*result)->stock_locate,                    42);
    EXPECT_EQ((*result)->tracking_number,                 67);
    EXPECT_EQ((*result)->timestamp,                       12345);
    EXPECT_EQ((*result)->original_order_reference_number, 43567);
    EXPECT_EQ((*result)->new_order_reference_number,      43567);
    EXPECT_EQ((*result)->shares,                          100);
    EXPECT_EQ((*result)->price,                           98765);
}

TEST(SystemMessageParser, ValidSystemEventMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x0C,
        /* message_type           = 'S'   */ 0x53, 
        /* stock_locate           = 0     */ 0x00, 0x00, 
        /* tracking_number        = 1     */ 0x00, 0x01, 
        /* timestamp              = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* event_code             = 'O'   */ 0x4F
    };

    auto result = parse<nasdaq::SystemEventMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'S');
    EXPECT_EQ((*result)->stock_locate,    0);
    EXPECT_EQ((*result)->tracking_number, 1);
    EXPECT_EQ((*result)->timestamp,       12345);
    EXPECT_EQ((*result)->event_code,      'O');
}

TEST(AddOrderParser, ValidAddOrderMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x24,
        /* message_type           = 'A'   */ 0x41, 
        /* stock_locate           = 100   */ 0x00, 0x64, 
        /* tracking_number        = 200   */ 0x00, 0xC8, 
        /* timestamp              = 34567 */ 0x00, 0x00, 0x00, 0x00, 0x87, 0x07,
        /* order_reference_number = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* buy_sell_indicator     = 'B'   */ 0x42,
        /* shares                 = 500   */ 0x00, 0x00, 0x01, 0xF4,
        /* stock = "AAPL    "             */ 0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20,
        /* price                  = 150000*/ 0x00, 0x02, 0x49, 0xF0
    };

    auto result = parse<nasdaq::AddOrderMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'A');
    EXPECT_EQ((*result)->stock_locate,           100);
    EXPECT_EQ((*result)->tracking_number,        200);
    EXPECT_EQ((*result)->timestamp,              34567);
    EXPECT_EQ((*result)->order_reference_number, 12345);
    EXPECT_EQ((*result)->buy_sell_indicator,     'B');
    EXPECT_EQ((*result)->shares,                 500);
    EXPECT_EQ((*result)->price,                  150000);
}

TEST(AddOrderParser, ValidAddOrderMPIDMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x28,
        /* message_type           = 'F'   */ 0x46, 
        /* stock_locate           = 100   */ 0x00, 0x64, 
        /* tracking_number        = 200   */ 0x00, 0xC8, 
        /* timestamp              = 34567 */ 0x00, 0x00, 0x00, 0x00, 0x87, 0x07,
        /* order_reference_number = 12345 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        /* buy_sell_indicator     = 'S'   */ 0x53,
        /* shares                 = 500   */ 0x00, 0x00, 0x01, 0xF4,
        /* stock = "TSLA    "             */ 0x54, 0x53, 0x4C, 0x41, 0x20, 0x20, 0x20, 0x20,
        /* price                  = 250000*/ 0x00, 0x03, 0xD0, 0x90,
        /* attribution = "NSDQ"           */ 0x4E, 0x53, 0x44, 0x51
    };

    auto result = parse<nasdaq::AddOrderMPIDMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'F');
    EXPECT_EQ((*result)->stock_locate,           100);
    EXPECT_EQ((*result)->tracking_number,        200);
    EXPECT_EQ((*result)->timestamp,              34567);
    EXPECT_EQ((*result)->order_reference_number, 12345);
    EXPECT_EQ((*result)->buy_sell_indicator,     'S');
    EXPECT_EQ((*result)->shares,                 500);
    EXPECT_EQ((*result)->price,                  250000);
    EXPECT_EQ(std::string((*result)->attribution, 4), "NSDQ");
}

TEST(TradeMessageParser, ValidTradeMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x2C,
        /* message_type           = 'P'   */ 0x50, 
        /* stock_locate           = 50    */ 0x00, 0x32, 
        /* tracking_number        = 75    */ 0x00, 0x4B, 
        /* timestamp              = 45678 */ 0x00, 0x00, 0x00, 0x00, 0xB2, 0x6E,
        /* order_reference_number = 0     */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        /* buy_sell_indicator     = 'B'   */ 0x42,
        /* shares                 = 300   */ 0x00, 0x00, 0x01, 0x2C,
        /* stock = "MSFT    "             */ 0x4D, 0x53, 0x46, 0x54, 0x20, 0x20, 0x20, 0x20,
        /* price                  = 320000*/ 0x00, 0x04, 0xE2, 0x00,
        /* match_number           = 99999 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x9F
    };

    auto result = parse<nasdaq::TradeMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'P');
    EXPECT_EQ((*result)->stock_locate,           50);
    EXPECT_EQ((*result)->tracking_number,        75);
    EXPECT_EQ((*result)->timestamp,              45678);
    EXPECT_EQ((*result)->order_reference_number, 0);
    EXPECT_EQ((*result)->buy_sell_indicator,     'B');
    EXPECT_EQ((*result)->shares,                 300);
    EXPECT_EQ((*result)->price,                  320000);
    EXPECT_EQ((*result)->match_number,           99999);
}

TEST(TradeMessageParser, ValidCrossTradeMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x28,
        /* message_type           = 'Q'   */ 0x51, 
        /* stock_locate           = 25    */ 0x00, 0x19, 
        /* tracking_number        = 88    */ 0x00, 0x58, 
        /* timestamp              = 23456 */ 0x00, 0x00, 0x00, 0x00, 0x5B, 0xA0,
        /* shares                 = 10000 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x10,
        /* stock = "GOOG    "             */ 0x47, 0x4F, 0x4F, 0x47, 0x20, 0x20, 0x20, 0x20,
        /* cross_price            = 280128*/ 0x00, 0x04, 0x46, 0x40,
        /* match_number           = 55555 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD9, 0x03,
        /* cross_type             = 'O'   */ 0x4F
    };

    auto result = parse<nasdaq::CrossTradeMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'Q');
    EXPECT_EQ((*result)->stock_locate,    25);
    EXPECT_EQ((*result)->tracking_number, 88);
    EXPECT_EQ((*result)->timestamp,       23456);
    EXPECT_EQ((*result)->shares,          10000);
    EXPECT_EQ((*result)->cross_price,     280128);
    EXPECT_EQ((*result)->match_number,    55555);
    EXPECT_EQ((*result)->cross_type,      'O');
}

TEST(TradeMessageParser, ValidBrokenTradeMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x13,
        /* message_type           = 'B'   */ 0x42, 
        /* stock_locate           = 10    */ 0x00, 0x0A, 
        /* tracking_number        = 20    */ 0x00, 0x14, 
        /* timestamp              = 67890 */ 0x00, 0x00, 0x00, 0x01, 0x09, 0x32,
        /* match_number           = 77777 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2F, 0xD1
    };

    auto result = parse<nasdaq::BrokenTradeMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'B');
    EXPECT_EQ((*result)->stock_locate,    10);
    EXPECT_EQ((*result)->tracking_number, 20);
    EXPECT_EQ((*result)->timestamp,       67890);
    EXPECT_EQ((*result)->match_number,    77777);
}

TEST(NOIIMessageParser, ValidNOIIMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x32,
        /* message_type           = 'I'   */ 0x49, 
        /* stock_locate           = 30    */ 0x00, 0x1E, 
        /* tracking_number        = 40    */ 0x00, 0x28, 
        /* timestamp              = 56789 */ 0x00, 0x00, 0x00, 0x00, 0xDD, 0xD5,
        /* paired_shares          = 5000  */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x88,
        /* imbalance_shares       = 2000  */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xD0,
        /* imbalance_direction    = 'B'   */ 0x42,
        /* stock = "AMZN    "             */ 0x41, 0x4D, 0x5A, 0x4E, 0x20, 0x20, 0x20, 0x20,
        /* far_price              = 330032*/ 0x00, 0x05, 0x09, 0x30,
        /* near_price             = 335032*/ 0x00, 0x05, 0x1C, 0xB8,
        /* current_reference_price= 332532*/ 0x00, 0x05, 0x12, 0xF4,
        /* cross_type             = 'O'   */ 0x4F,
        /* price_variation_ind    = 'L'   */ 0x4C
    };

    auto result = parse<nasdaq::NOIIMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,              'I');
    EXPECT_EQ((*result)->stock_locate,              30);
    EXPECT_EQ((*result)->tracking_number,           40);
    EXPECT_EQ((*result)->timestamp,                 56789);
    EXPECT_EQ((*result)->paired_shares,             5000);
    EXPECT_EQ((*result)->imbalance_shares,          2000);
    EXPECT_EQ((*result)->imbalance_direction,       'B');
    EXPECT_EQ((*result)->far_price,                 330032);
    EXPECT_EQ((*result)->near_price,                335032);
    EXPECT_EQ((*result)->current_reference_price,   332532);
    EXPECT_EQ((*result)->cross_type,                'O');
    EXPECT_EQ((*result)->price_variation_indicator, 'L');
}

TEST(RetailMessageParser, ValidRetailInterestMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x14,
        /* message_type           = 'N'   */ 0x4E, 
        /* stock_locate           = 15    */ 0x00, 0x0F, 
        /* tracking_number        = 25    */ 0x00, 0x19, 
        /* timestamp              = 11111 */ 0x00, 0x00, 0x00, 0x00, 0x2B, 0x67,
        /* stock = "NVDA    "             */ 0x4E, 0x56, 0x44, 0x41, 0x20, 0x20, 0x20, 0x20,
        /* interest_flag          = 'A'   */ 0x41
    };

    auto result = parse<nasdaq::RetailInterestMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'N');
    EXPECT_EQ((*result)->stock_locate,    15);
    EXPECT_EQ((*result)->tracking_number, 25);
    EXPECT_EQ((*result)->timestamp,       11111);
    EXPECT_EQ((*result)->interest_flag,   'A');
}

TEST(DLCRMessageParser, ValidDLCRMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x2F,
        /* message_type           = 'O'   */ 0x4F, 
        /* stock_locate           = 5     */ 0x00, 0x05, 
        /* tracking_number        = 10    */ 0x00, 0x0A, 
        /* timestamp              = 98765 */ 0x00, 0x00, 0x00, 0x01, 0x81, 0xCD,
        /* stock = "COIN    "             */ 0x43, 0x4F, 0x49, 0x4E, 0x20, 0x20, 0x20, 0x20,
        /* open_eligibility       = 'Y'   */ 0x59,
        /* min_allowable_price    = 200000*/ 0x00, 0x03, 0x0D, 0x40,
        /* max_allowable_price    = 800000*/ 0x00, 0x0C, 0x35, 0x00,
        /* near_execution_price   = 500000*/ 0x00, 0x07, 0xA1, 0x20,
        /* near_execution_time    = 345600*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x46, 0x00,
        /* lower_collar           = 450384*/ 0x00, 0x06, 0xDF, 0x50,
        /* upper_collar           = 549616*/ 0x00, 0x08, 0x62, 0xF0
    };

    auto result = parse<nasdaq::DLCRMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,               'O');
    EXPECT_EQ((*result)->stock_locate,               5);
    EXPECT_EQ((*result)->tracking_number,            10);
    EXPECT_EQ((*result)->timestamp,                  98765);
    EXPECT_EQ((*result)->open_eligibility_status,    'Y');
    EXPECT_EQ((*result)->minimum_allowable_price,    200000);
    EXPECT_EQ((*result)->maximum_allowable_price,    800000);
    EXPECT_EQ((*result)->near_execution_price,       500000);
    EXPECT_EQ((*result)->near_execution_time,        345600);
    EXPECT_EQ((*result)->lower_price_range_collar,   450384);
    EXPECT_EQ((*result)->upper_price_range_collar,   549616);
}

TEST(StockRelatedParser, ValidStockDirectoryMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x27,
        /* message_type           = 'R'   */ 0x52, 
        /* stock_locate           = 1     */ 0x00, 0x01, 
        /* tracking_number        = 1     */ 0x00, 0x01, 
        /* timestamp              = 1000  */ 0x00, 0x00, 0x00, 0x00, 0x03, 0xE8,
        /* stock = "META    "             */ 0x4D, 0x45, 0x54, 0x41, 0x20, 0x20, 0x20, 0x20,
        /* market_category        = 'Q'   */ 0x51,
        /* financial_status       = 'N'   */ 0x4E,
        /* round_lot_size         = 100   */ 0x00, 0x00, 0x00, 0x64,
        /* round_lots_only        = 'N'   */ 0x4E,
        /* issue_classification   = 'C'   */ 0x43,
        /* issue_sub_type         = "  "  */ 0x20, 0x20,
        /* authenticity           = 'P'   */ 0x50,
        /* short_sale_threshold   = 'N'   */ 0x4E,
        /* ipo_flag               = 'N'   */ 0x4E,
        /* luld_tier              = '1'   */ 0x31,
        /* etp_flag               = 'N'   */ 0x4E,
        /* etp_leverage           = 1     */ 0x00, 0x00, 0x00, 0x01,
        /* inverse_indicator      = 'N'   */ 0x4E
    };

    auto result = parse<nasdaq::StockDirectory>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,                  'R');
    EXPECT_EQ((*result)->stock_locate,                  1);
    EXPECT_EQ((*result)->tracking_number,               1);
    EXPECT_EQ((*result)->timestamp,                     1000);
    EXPECT_EQ((*result)->market_category,               'Q');
    EXPECT_EQ((*result)->financial_status_indicator,    'N');
    EXPECT_EQ((*result)->round_lot_size,                100);
    EXPECT_EQ((*result)->round_lots_only,               'N');
    EXPECT_EQ((*result)->issue_classification,          'C');
    EXPECT_EQ((*result)->authenticity,                  'P');
    EXPECT_EQ((*result)->short_sale_threshold_indicator, 'N');
    EXPECT_EQ((*result)->ipo_flag,                      'N');
    EXPECT_EQ((*result)->luld_reference_price_tier,     '1');
    EXPECT_EQ((*result)->etp_flag,                      'N');
    EXPECT_EQ((*result)->etp_leverage_factor,           1);
    EXPECT_EQ((*result)->inverse_indicator,             'N');
}

TEST(StockRelatedParser, ValidStockTradingActionMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x19,
        /* message_type           = 'H'   */ 0x48, 
        /* stock_locate           = 50    */ 0x00, 0x32, 
        /* tracking_number        = 100   */ 0x00, 0x64, 
        /* timestamp              = 5555  */ 0x00, 0x00, 0x00, 0x00, 0x15, 0xB3,
        /* stock = "PLTR    "             */ 0x50, 0x4C, 0x54, 0x52, 0x20, 0x20, 0x20, 0x20,
        /* trading_state          = 'H'   */ 0x48,
        /* reserved               = ' '   */ 0x20,
        /* reason = "T1  "                */ 0x54, 0x31, 0x20, 0x20
    };

    auto result = parse<nasdaq::StockTradingAction>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'H');
    EXPECT_EQ((*result)->stock_locate,    50);
    EXPECT_EQ((*result)->tracking_number, 100);
    EXPECT_EQ((*result)->timestamp,       5555);
    EXPECT_EQ((*result)->trading_state,   'H');
    EXPECT_EQ((*result)->reserved,        ' ');
    EXPECT_EQ(std::string((*result)->reason, 4), "T1  ");
}

TEST(StockRelatedParser, ValidRegSHOMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x14,
        /* message_type           = 'Y'   */ 0x59, 
        /* stock_locate           = 33    */ 0x00, 0x21, 
        /* tracking_number        = 44    */ 0x00, 0x2C, 
        /* timestamp              = 7777  */ 0x00, 0x00, 0x00, 0x00, 0x1E, 0x61,
        /* stock = "GME     "             */ 0x47, 0x4D, 0x45, 0x20, 0x20, 0x20, 0x20, 0x20,
        /* reg_sho_action         = '1'   */ 0x31
    };

    auto result = parse<nasdaq::RegSHORestriction>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'Y');
    EXPECT_EQ((*result)->stock_locate,    33);
    EXPECT_EQ((*result)->tracking_number, 44);
    EXPECT_EQ((*result)->timestamp,       7777);
    EXPECT_EQ((*result)->reg_sho_action,  '1');
}

TEST(StockRelatedParser, ValidMarketParticipantPositionMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1A,
        /* message_type           = 'L'   */ 0x4C, 
        /* stock_locate           = 22    */ 0x00, 0x16, 
        /* tracking_number        = 55    */ 0x00, 0x37, 
        /* timestamp              = 8888  */ 0x00, 0x00, 0x00, 0x00, 0x22, 0xB8,
        /* mpid = "NITE"                  */ 0x4E, 0x49, 0x54, 0x45,
        /* stock = "AMD     "             */ 0x41, 0x4D, 0x44, 0x20, 0x20, 0x20, 0x20, 0x20,
        /* primary_market_maker   = 'Y'   */ 0x59,
        /* market_maker_mode      = 'N'   */ 0x4E,
        /* market_participant_state= 'A'  */ 0x41
    };

    auto result = parse<nasdaq::MarketParticipationPosition>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,               'L');
    EXPECT_EQ((*result)->stock_locate,               22);
    EXPECT_EQ((*result)->tracking_number,            55);
    EXPECT_EQ((*result)->timestamp,                  8888);
    EXPECT_EQ(std::string((*result)->mpid, 4),       "NITE");
    EXPECT_EQ((*result)->primary_market_maker,       'Y');
    EXPECT_EQ((*result)->market_maker_mode,          'N');
    EXPECT_EQ((*result)->market_participation_state, 'A');
}

TEST(StockRelatedParser, ValidMWCBDeclineLevelMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x23,
        /* message_type           = 'V'   */ 0x56, 
        /* stock_locate           = 0     */ 0x00, 0x00, 
        /* tracking_number        = 1     */ 0x00, 0x01, 
        /* timestamp              = 9999  */ 0x00, 0x00, 0x00, 0x00, 0x27, 0x0F,
        /* level1                         */ 0x00, 0x00, 0x00, 0x00, 0x05, 0xF5, 0xE1, 0x00,
        /* level2                         */ 0x00, 0x00, 0x00, 0x00, 0x0B, 0xEB, 0xC2, 0x00,
        /* level3                         */ 0x00, 0x00, 0x00, 0x00, 0x17, 0xD7, 0x84, 0x00
    };

    auto result = parse<nasdaq::MWCBDeclineLevelMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'V');
    EXPECT_EQ((*result)->stock_locate,    0);
    EXPECT_EQ((*result)->tracking_number, 1);
    EXPECT_EQ((*result)->timestamp,       9999);
    EXPECT_EQ((*result)->level_1,         100000000);
    EXPECT_EQ((*result)->level_2,         200000000);
    EXPECT_EQ((*result)->level_3,         400000000);
}

TEST(StockRelatedParser, ValidMWCBStatusMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x0C,
        /* message_type           = 'W'   */ 0x57, 
        /* stock_locate           = 0     */ 0x00, 0x00, 
        /* tracking_number        = 2     */ 0x00, 0x02, 
        /* timestamp              = 11111 */ 0x00, 0x00, 0x00, 0x00, 0x2B, 0x67,
        /* breached_level         = '1'   */ 0x31
    };

    auto result = parse<nasdaq::MWCBStatusMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,    'W');
    EXPECT_EQ((*result)->stock_locate,    0);
    EXPECT_EQ((*result)->tracking_number, 2);
    EXPECT_EQ((*result)->timestamp,       11111);
    EXPECT_EQ((*result)->breached_level,  '1');
}

TEST(StockRelatedParser, ValidIPOQuotingPeriodUpdateMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x1C,
        /* message_type           = 'K'   */ 0x4B, 
        /* stock_locate           = 0     */ 0x00, 0x00, 
        /* tracking_number        = 3     */ 0x00, 0x03, 
        /* timestamp              = 22222 */ 0x00, 0x00, 0x00, 0x00, 0x56, 0xCE,
        /* stock = "RBLX    "             */ 0x52, 0x42, 0x4C, 0x58, 0x20, 0x20, 0x20, 0x20,
        /* ipo_quotation_release_time     */ 0x00, 0x00, 0x8C, 0xA0,
        /* ipo_quotation_release_qual= 'A'*/ 0x41,
        /* ipo_price              = 450384*/ 0x00, 0x06, 0xDF, 0x50
    };

    auto result = parse<nasdaq::QuotePeriodUpdate>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,                   'K');
    EXPECT_EQ((*result)->stock_locate,                   0);
    EXPECT_EQ((*result)->tracking_number,                3);
    EXPECT_EQ((*result)->timestamp,                      22222);
    EXPECT_EQ((*result)->ipo_quotation_release_time,     36000);
    EXPECT_EQ((*result)->ipo_quotation_release_qualifier, 'A');
    EXPECT_EQ((*result)->ipo_price,                      450384);
}

TEST(StockRelatedParser, ValidLULDAuctionCollarMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x23,
        /* message_type           = 'J'   */ 0x4A, 
        /* stock_locate           = 77    */ 0x00, 0x4D, 
        /* tracking_number        = 88    */ 0x00, 0x58, 
        /* timestamp              = 33333 */ 0x00, 0x00, 0x00, 0x00, 0x82, 0x35,
        /* stock = "SNAP    "             */ 0x53, 0x4E, 0x41, 0x50, 0x20, 0x20, 0x20, 0x20,
        /* auction_collar_ref     = 120000*/ 0x00, 0x01, 0xD4, 0xC0,
        /* upper_auction_collar   = 132000*/ 0x00, 0x02, 0x03, 0xA0,
        /* lower_auction_collar   = 108000*/ 0x00, 0x01, 0xA5, 0xE0,
        /* auction_collar_ext     = 0     */ 0x00, 0x00, 0x00, 0x00
    };

    auto result = parse<nasdaq::LULDAuctionCollar>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,                  'J');
    EXPECT_EQ((*result)->stock_locate,                  77);
    EXPECT_EQ((*result)->tracking_number,               88);
    EXPECT_EQ((*result)->timestamp,                     33333);
    EXPECT_EQ((*result)->auction_collar_reference_price, 120000);
    EXPECT_EQ((*result)->upper_auction_collar_price,    132000);
    EXPECT_EQ((*result)->lower_auction_collar_price,    108000);
    EXPECT_EQ((*result)->auction_collar_extension,      0);
}

TEST(StockRelatedParser, ValidOperationalHaltMessage) {
    byte_t raw[] = { 
        /* message size                   */ 0x00, 0x15,
        /* message_type           = 'h'   */ 0x68, 
        /* stock_locate           = 99    */ 0x00, 0x63, 
        /* tracking_number        = 111   */ 0x00, 0x6F, 
        /* timestamp              = 44444 */ 0x00, 0x00, 0x00, 0x00, 0xAD, 0x9C,
        /* stock = "HOOD    "             */ 0x48, 0x4F, 0x4F, 0x44, 0x20, 0x20, 0x20, 0x20,
        /* market_code            = 'Q'   */ 0x51,
        /* operational_halt_action= 'H'   */ 0x48
    };

    auto result = parse<nasdaq::OperationHalt>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,            'h');
    EXPECT_EQ((*result)->stock_locate,            99);
    EXPECT_EQ((*result)->tracking_number,         111);
    EXPECT_EQ((*result)->timestamp,               44444);
    EXPECT_EQ((*result)->market_code,             'Q');
    EXPECT_EQ((*result)->operational_halt_action, 'H');
}
