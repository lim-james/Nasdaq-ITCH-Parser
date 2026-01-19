#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] AddOrderMessage {
    MessageType  message_type; // 'A'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    char         buy_sell_indicator; // 'B' = Buy, 'S' = Sell
    NumShares4   shares;
    Stock        stock;
    Price4       price;
};

struct [[gnu::packed]] AddOrderMPIDMessage {
    MessageType  message_type; // 'F'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    char         buy_sell_indicator; // 'B' = Buy, 'S' = Sell
    NumShares4   shares;
    Stock        stock;
    Price4       price;
    MPID         attribution; 
};

}
