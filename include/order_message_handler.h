#pragma once 

#include "nasdaq/order_message.h"

class OrderMessageHandler {
public:
    virtual void onOrderExecutedMessage(nasdaq::OrderExecutedMessage*) = 0;
    virtual void onOrderExecutedWithPriceMessage(nasdaq::OrderExecutedWithPriceMessage*) = 0;
};
