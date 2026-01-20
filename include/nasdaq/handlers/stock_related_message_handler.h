#pragma once

#include "nasdaq/stock_related_messages.h"

namespace nasdaq {

class StockrelatedMessageHandler {
public:
    virtual void onStockDirectory(StockDirectory*) = 0; 
    virtual void onStockTradingAction(StockTradingAction*) = 0; 
    virtual void onRegSHORestriction(RegSHORestriction*) = 0; 
    virtual void onMarketParticipationPosition(MarketParticipationPosition*) = 0; 
    virtual void onMWCBDeclineLevelMessage(MWCBDeclineLevelMessage*) = 0; 
    virtual void onMWCBStatusMessage(MWCBStatusMessage*) = 0; 
    virtual void onQuotePeriodUpdate(QuotePeriodUpdate*) = 0; 
    virtual void onLULDAuctionCollar(LULDAuctionCollar*) = 0; 
    virtual void onOperationHalt(OperationHalt*) = 0; 
};

}
