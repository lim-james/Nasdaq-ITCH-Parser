#include <gtest/gtest.h>

#include "nasdaq/order_message.h"
#include "order_message_parser.h"

#include <bit>

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

TEST(OrderMessageParser, ValidMessage) {
    byte_t raw[] = { 
        0x00, 0x1F,
        0x45, 
        0x00, 0x2A, 
        0x00, 0x43, 
        0x00, 0x00, 0x00, 0x00, 0x30, 0x39,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x2F, 
        0x00, 0x00, 0x00, 0x64, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x86 
    };

    auto result = parse<nasdaq::OrderExecuteMessage>(raw);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)->message_type,           'E');
    EXPECT_EQ((*result)->stock_locate,           42);
    EXPECT_EQ((*result)->tracking_number,        67);
    EXPECT_EQ((*result)->timestamp(),            12345);
    EXPECT_EQ((*result)->order_reference_number, 43567);
    EXPECT_EQ((*result)->executed_shares,        100);
    EXPECT_EQ((*result)->match_number,           6790);
}
