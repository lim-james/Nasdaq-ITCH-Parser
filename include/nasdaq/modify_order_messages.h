#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] OrderExecutedMessage {
    static constexpr MessageType MESSAGE_TYPE = 'E';
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares4   executed_shares;
    ReferenceNum match_number;
};

struct [[gnu::packed]] OrderExecutedWithPriceMessage {
    static constexpr MessageType MESSAGE_TYPE = 'C';
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares4   executed_shares;
    ReferenceNum match_number;
    char         printable;
    Price4       execution_price;
};

struct [[gnu::packed]] OrderCancelMessage {
    static constexpr MessageType MESSAGE_TYPE = 'X';
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares4   cancelled_shares;
};

struct [[gnu::packed]] OrderDeleteMessage {
    static constexpr MessageType MESSAGE_TYPE = 'D';
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
};

struct [[gnu::packed]] OrderReplaceMessage {
    static constexpr MessageType MESSAGE_TYPE = 'U';
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum original_order_reference_number;
    ReferenceNum new_order_reference_number;
    NumShares4   shares;
    Price4       price;
};

}
