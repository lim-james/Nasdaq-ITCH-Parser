#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] NOIIMessage {
    MessageType  message_type; // 'I'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    NumShares8   paired_shares;
    NumShares8   imbalance_shares;
    char         imbalance_direction; // 'B' = Buy, 'S' = Sell, 'N' = No imbalance, 'O' = Insufficient, 'P' = Paused
    Stock        stock;
    Price4       far_price;
    Price4       near_price;
    Price4       current_reference_price;
    char         cross_type; // 'O' = Opening, 'C' = Closing, 'H' = IPO/Halted, 'A' = Extended Trading Close
    char         price_variation_indicator; // 'L', '1'-'9', 'A'-'C', or ' ' (space)
};

}
