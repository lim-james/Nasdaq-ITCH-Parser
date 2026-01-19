#pragma once 

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] TradeMessage {
    MessageType  message_type; // 'P'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum order_reference_number;
    char         buy_sell_indicator; // 'B' = Buy, 'S' = Sell (always 'B' as of 07/14/2014)
    NumShares4   shares;
    Stock        stock;
    Price4       price;
    ReferenceNum match_number;
};

struct [[gnu::packed]] CrossTradeMessage {
    MessageType  message_type; // 'Q'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    NumShares8   shares;
    Stock        stock;
    Price4       cross_price;
    ReferenceNum match_number;
    char         cross_type; // 'O' = Opening, 'C' = Closing, 'H' = IPO/Halted
};

struct [[gnu::packed]] BrokenTradeMessage {
    MessageType  message_type; // 'B'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    ReferenceNum match_number;
};

}
