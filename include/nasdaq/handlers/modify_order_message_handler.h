#pragma once 

#include "nasdaq/modify_order_messages.h"

class OrderMessageHandler {
public:
    virtual void onOrderExecutedMessage(nasdaq::OrderExecutedMessage*) = 0;
    virtual void onOrderExecutedWithPriceMessage(nasdaq::OrderExecutedWithPriceMessage*) = 0;
    virtual void onOrderCancelMessage(nasdaq::OrderCancelMessage*) = 0;
    virtual void onOrderDeleteMessage(nasdaq::OrderDeleteMessage*) = 0;
    virtual void onOrderReplaceMessage(nasdaq::OrderReplaceMessage*) = 0;
};
