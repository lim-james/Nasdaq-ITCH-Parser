#pragma once 

#include "nasdaq/retail_interest_message.h"

namespace nasdaq {
class RetailInterestMessageHandler {
public:
    virtual void onRetailInterestMessage(RetailInterestMessage*) = 0; 
};

}
