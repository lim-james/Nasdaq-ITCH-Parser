#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] OrderExecutedMessage {
    MessageType  message_type; // 'E'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares    executed_shares;
    ReferenceNum match_number;
};

struct [[gnu::packed]] OrderExecutedWithPriceMessage {
    MessageType  message_type; // 'C'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    NumShares    executed_shares;
    ReferenceNum match_number;
    char         printable;
    Price4       execution_price;
};

}
