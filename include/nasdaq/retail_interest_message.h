#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] RetailInterestMessage {
    static constexpr MessageType MESSAGE_TYPE = 'N';
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock;
    char         interest_flag; // 'B' = Buy side, 'S' = Sell side, 'A' = Both sides, 'N' = No RPI orders
};

}
