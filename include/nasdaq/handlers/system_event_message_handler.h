#pragma once

#include "nasdaq/system_event_message.h"

namespace nasdaq {

class SystemEventMessageHandler {
public:
    virtual void onSystemEventMessage(SystemEventMessage*) = 0; 
};

}
