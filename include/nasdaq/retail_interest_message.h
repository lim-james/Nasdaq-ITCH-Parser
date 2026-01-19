#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] RetailInterestMessage {
    MessageType  message_type; // 'N'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock;
    char         interest_flag; // 'B' = Buy side, 'S' = Sell side, 'A' = Both sides, 'N' = No RPI orders
};

}
