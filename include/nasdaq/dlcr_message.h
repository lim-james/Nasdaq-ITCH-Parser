#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] DLCRMessage {
    MessageType  message_type; // 'O'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock;
    char         open_eligibility_status; // 'N' = Not Eligible, 'Y' = Eligible
    Price4       minimum_allowable_price;
    Price4       maximum_allowable_price;
    Price4       near_execution_price;
    Int8         near_execution_time;
    Price4       lower_price_range_collar;
    Price4       upper_price_range_collar;
};

}
