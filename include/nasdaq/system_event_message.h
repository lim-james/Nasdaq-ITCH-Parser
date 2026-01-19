#pragma once

#include "type.h"

namespace nasdaq {

struct [[gnu::packed]] SystemEventMessage {
    MessageType message_type; // 'S'
    LocateCode  stock_locate;
    TrackingNum tracking_number;
    Timestamp   timestamp;
    char        event_code; // 'O', 'S', 'Q', 'M', 'E', 'C'
};

}
