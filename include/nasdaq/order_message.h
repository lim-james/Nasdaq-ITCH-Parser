#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] OrderExecuteMessage {
    MessageType  message_type;
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    std::uint8_t raw_timestamp[6];
    ReferenceNum order_reference_number;
    NumShares    executed_shares;
    ReferenceNum match_number;

    Timestamp timestamp() const {
        return (static_cast<std::uint64_t>(raw_timestamp[0]) << 40) 
            |  (static_cast<std::uint64_t>(raw_timestamp[1]) << 32)
            |  (static_cast<std::uint64_t>(raw_timestamp[2]) << 24)
            |  (static_cast<std::uint64_t>(raw_timestamp[3]) << 16)
            |  (static_cast<std::uint64_t>(raw_timestamp[4]) << 8)
            |  (static_cast<std::uint64_t>(raw_timestamp[5]));
    }
};

}
