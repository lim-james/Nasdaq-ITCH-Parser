#pragma once 

#include "nasdaq/trade_messages.h"

namespace nasdaq {
class TradeMessageHandler {
public:
    virtual void onTradeMessage(TradeMessage*) = 0; 
    virtual void onCrossTradeMessage(CrossTradeMessage*) = 0; 
    virtual void onBrokenTradeMessage(BrokenTradeMessage*) = 0; 
};
}
