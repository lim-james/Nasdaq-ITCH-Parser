#pragma once

#include <unordered_map>
#include <functional>

#include "nasdaq/handlers/modify_order_message_handler.h"
#include "order_message_parser.h"

using byte_t = unsigned char;

class OrderMessageDispatcher {
private:

    std::unordered_map<char, std::function<MessageSize(byte_t*)>> dispatchers_;
    std::vector<nasdaq::ModifyOrderMessageHandler*> modify_order_message_handlers_;

public:

    OrderMessageDispatcher() {
        dispatchers_['E'] = std::bind_front(&OrderMessageDispatcher::dispatchExecuteMessage, this);
        dispatchers_['C'] = std::bind_front(
            &OrderMessageDispatcher::dispatchExecuteMessageWithPriceMessage, 
            this
        );
    }

    void subscribe(nasdaq::ModifyOrderMessageHandler& handler) {
        modify_order_message_handlers_.push_back(&handler);
    }

    MessageSize feed(byte_t* buffer) {
        const char message_type = *reinterpret_cast<char*>(buffer + sizeof(MessageSize));
        return dispatchers_[message_type](buffer) + sizeof(MessageSize);
    }

private:

    MessageSize dispatchExecuteMessage(byte_t* buffer) {
        if (auto message = parse<nasdaq::OrderExecutedMessage>(buffer); message.has_value()) {
            for (auto handler: modify_order_message_handlers_) {
                handler->onOrderExecutedMessage(*message);
            }
        }
        return sizeof(nasdaq::OrderExecutedMessage);
    }

    MessageSize dispatchExecuteMessageWithPriceMessage(byte_t* buffer) {
        if (auto message = parse<nasdaq::OrderExecutedWithPriceMessage>(buffer); message.has_value()) {
            for (auto handler: modify_order_message_handlers_) {
                handler->onOrderExecutedWithPriceMessage(*message);
            }
        }
        return sizeof(nasdaq::OrderExecutedWithPriceMessage);
    }

};
