#pragma once 

#include "nasdaq/modify_order_messages.h"

namespace nasdaq {

class ModifyOrderMessageHandler {
public:
    virtual void onOrderExecutedMessage(OrderExecutedMessage*) = 0;
    virtual void onOrderExecutedWithPriceMessage(OrderExecutedWithPriceMessage*) = 0;
    virtual void onOrderCancelMessage(OrderCancelMessage*) = 0;
    virtual void onOrderDeleteMessage(OrderDeleteMessage*) = 0;
    virtual void onOrderReplaceMessage(OrderReplaceMessage*) = 0;
};

}
