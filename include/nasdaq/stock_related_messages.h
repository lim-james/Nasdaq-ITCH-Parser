#pragma once

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] StockDirectory {
    MessageType  message_type; // 'R'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock; 
    char         market_category; 
    char         financial_status_indicator; 
    NumShares4   round_lot_size;
    char         round_lots_only;
    char         issue_classification;
    char         issue_sub_type[2];
    char         authenticity;
    char         short_sale_threshold_indicator;
    char         ipo_flag;
    char         luld_reference_price_tier;
    char         etp_flag;
    Int4         etp_leverage_factor;
    char         inverse_indicator;
};

struct [[gnu::packed]] StockTradingAction {
    MessageType  message_type; // 'H'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock; 
    char         trading_state; 
    char         reserved; 
    char         reason[4];
};

struct [[gnu::packed]] RegSHORestriction {
    MessageType  message_type; // 'Y'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock; 
    char         reg_sho_action; 
};

struct [[gnu::packed]] MarketParticipationPosition {
    MessageType  message_type; // 'L'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    MPID         mpid; 
    Stock        stock; 
    char         primary_market_maker; 
    char         market_maker_mode; 
    char         market_participation_state; 
};

struct [[gnu::packed]] MWCBDeclineLevelMessage {
    MessageType  message_type; // 'V'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Price8       level_1;
    Price8       level_2;
    Price8       level_3;
};

struct [[gnu::packed]] MWCBStatusMessage {
    MessageType  message_type; // 'W'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    char         breached_level;
};

struct [[gnu::packed]] QuotePeriodUpdate {
    MessageType  message_type; // 'K'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock;
    ReleaseTime  ipo_quotation_release_time;
    char         ipo_quotation_release_qualifier;
    Price4       ipo_price;
};

struct [[gnu::packed]] LULDAuctionCollar {
    MessageType  message_type; // 'J'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock;
    Price4       auction_collar_reference_price;
    Price4       upper_auction_collar_price;
    Price4       lower_auction_collar_price;
    Int4         auction_collar_extension;
};

struct [[gnu::packed]] OperationHalt {
    MessageType  message_type; // 'h'
    LocateCode   stock_locate;
    TrackingNum  tracking_number;
    Timestamp    timestamp;
    Stock        stock;
    char         market_code;
    char         operational_halt_action;
};

} 
