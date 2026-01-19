#pragma once

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] StockDirectory {
    MessageType message_type; // 'R'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Stock       stock; 
    char        marketCategory; 
    char        financialStatusIndicator; 
    NumShares4  roundLotSize;
    char        roundLotsOnly;
    char        issueClarification;
    char        issueSubType[2];
    char        authenticity;
    char        shortSaleThresholdIndicator;
    char        IPOFlag;
    char        LULDReferencePriceTier;
    char        ETPFlag;
    Int4        ETPLeverageFactor;
    char        reverseIndicator;
};

struct [[gnu::packed]] StockTradingAction {
    MessageType message_type; // 'H'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Stock       stock; 
    char        tradingState; 
    char        reversed; 
    char        reason[4];
};

struct [[gnu::packed]] RegSHORestriction {
    MessageType message_type; // 'Y'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Stock       stock; 
    char        regSHOAction; 
};

struct [[gnu::packed]] MarketParticipationPosition {
    MessageType message_type; // 'L'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    MPID        mpid; 
    Stock       stock; 
    char        primaryMarketMaker; 
    char        marketMakerMode; 
    char        marketParticipationState; 
};

struct [[gnu::packed]] MWCBDeclineLevelMessage {
    MessageType message_type; // 'V'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Price8      level1;
    Price8      level2;
    Price8      level3;
};

struct [[gnu::packed]] MWCBStatusMessage {
    MessageType message_type; // 'W'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    char        breadedLevel;
};

struct [[gnu::packed]] QuotePeriodUpdate {
    MessageType message_type; // 'K'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Stock       stock;
    ReleaseTime IPOQuotationReleaseTime;
    char        IPOQuotationReleaseQualifier;
    Price4      IPOPrice;
};

struct [[gnu::packed]] LULDAuctionCollar {
    MessageType message_type; // 'J'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Stock       stock;
    Price4      auctionCollarReferencePrice;
    Price4      upperAuctionCollarPrice;
    Price4      lowerAuctionCollarPrice;
    Int4        auctionCollarExtension;
};

struct [[gnu::packed]] OperationHalt {
    MessageType message_type; // 'h'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    Stock       stock;
    char        marketCode;
    char        operationalHaltAction;
};

}
