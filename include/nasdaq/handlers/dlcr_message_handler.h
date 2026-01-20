#pragma once 

#include "nasdaq/dlcr_message.h"

namespace nasdaq {

class DLCRMessageHandler {
public:
    virtual void onDLCRMessage(DLCRMessage*) = 0;
};

}
