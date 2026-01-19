#include <gtest/gtest.h>

#include "nasdaq/modify_order_messages.h"
#include "order_message_parser.h"

// message_type           : 8  = 'E'   = 01000101
// stock_locate           : 16 = 42    = 0000000000101010
// tracking_number        : 16 = 67    = 0000000001000011
// timestamp              : 48 = 12345 = 000000000000000000000000000000000011000000111001
// order_reference_number : 64 = 43567 = 0000000000000000000000000000000000000000000000001010101000101111
// executed_shares        : 32 = 100   = 00000000000000000000000001100100
// match_number           : 64 = 6790  = 0000000000000000000000000000000000000000000000000001101010000110
//
// 01000101000000000010101000000000010000110000000000000000000000000000000000110000001110010000000000000000000000000000000000000000000000001010101000101111000000000000000000000000011001000000000000000000000000000000000000000000000000000001101010000110
// 00 1F 45 00 2A 00 43 00 00 00 00 30 39 00 00 00 00 00 00 AA 2F 00 00 00 64 00 00 00 00 00 00 1A 86

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
        /* price        = 98765 */ 0x00, 0x01, 0x81, 0xCD 
    };

    auto result = parse<nasdaq::OrderReplaceMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'U');
    EXPECT_EQ((*result)->stock_locate,           42);
    EXPECT_EQ((*result)->tracking_number,        67);
    EXPECT_EQ((*result)->timestamp,              12345);
    EXPECT_EQ((*result)->original_order_reference_number, 43567);
    EXPECT_EQ((*result)->new_order_reference_number,      43567);
    EXPECT_EQ((*result)->shares,                 100);
    EXPECT_EQ((*result)->price,                  98765);
}
