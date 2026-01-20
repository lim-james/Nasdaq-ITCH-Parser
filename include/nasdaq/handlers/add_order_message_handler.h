#pragma once 

#include "nasdaq/add_order_messages.h"

namespace nasdaq {

class AddOrderMessageHandler {
public:
    virtual void onAddOrderMessage(AddOrderMessage*) = 0; 
    virtual void onAddOrderMPIDMessage(AddOrderMPIDMessage*) = 0; 
};

}
