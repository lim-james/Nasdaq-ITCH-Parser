#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] OrderExecutedMessage {
    MessageType  message_type; // 'E'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares4   executed_shares;
    ReferenceNum match_number;
};

struct [[gnu::packed]] OrderExecutedWithPriceMessage {
    MessageType  message_type; // 'C'
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
    MessageType  message_type; // 'X'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares4   cancelled_shares;
};

struct [[gnu::packed]] OrderDeleteMessage {
    MessageType  message_type; // 'D'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
};

struct [[gnu::packed]] OrderReplaceMessage {
    MessageType  message_type; // 'U'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum original_order_reference_number;
    ReferenceNum new_order_reference_number;
    NumShares4   shares;
    Price4       price;
};

}
