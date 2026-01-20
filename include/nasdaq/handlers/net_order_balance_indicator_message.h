#pragma once 

#include "nasdaq/net_order_balance_indicator_message.h"

namespace nasdaq {
class NOIIMessageHandler {
public:
    virtual void onNOIIMessage(NOIIMessage*) = 0; 
};

}
