#pragma once 

#include <cstdint>

#include "big_endian.h"

struct [[gnu::packed]] OrderExecuteMessage {
    char message_type;
    BigEndian<std::uint16_t> stock_locate;
    BigEndian<std::uint16_t> tracking_number;
    std::uint8_t raw_timestamp[6];
    BigEndian<std::uint64_t> order_reference_number;
    BigEndian<std::uint32_t> executed_shares;
    BigEndian<std::uint64_t> match_number;

    std::uint64_t timestamp() const {
        return (static_cast<std::uint64_t>(raw_timestamp[0]) << 40) 
            |  (static_cast<std::uint64_t>(raw_timestamp[1]) << 32)
            |  (static_cast<std::uint64_t>(raw_timestamp[2]) << 24)
            |  (static_cast<std::uint64_t>(raw_timestamp[3]) << 16)
            |  (static_cast<std::uint64_t>(raw_timestamp[4]) << 8)
            |  (static_cast<std::uint64_t>(raw_timestamp[5]));
    }
};
