#pragma once

#include <unordered_map>
#include <functional>

#include "nasdaq/handlers/modify_order_message_handler.h"
#include "nasdaq/handlers/trade_message_handler.h"
#include "nasdaq/modify_order_messages.h"
#include "order_message_parser.h"

using byte_t = unsigned char;

class OrderMessageDispatcher {
private:

    using DispatcherFn = std::function<MessageSize(byte_t*)>;

    std::unordered_map<char, DispatcherFn> dispatchers_;
    std::vector<nasdaq::ModifyOrderMessageHandler*> modify_order_message_handlers_;
    std::vector<nasdaq::TradeMessageHandler*> trade_message_handlers_;

public:

    OrderMessageDispatcher() {
        dispatchers_['E'] = [this](byte_t* buffer) -> MessageSize { 
            return dispatch<
                nasdaq::OrderExecutedMessage, 
                nasdaq::ModifyOrderMessageHandler,
                &nasdaq::ModifyOrderMessageHandler::onOrderExecutedMessage
            >(buffer, modify_order_message_handlers_);
        };

        dispatchers_['C'] = [this](byte_t* buffer) -> MessageSize { 
            return dispatch<
                nasdaq::OrderExecutedWithPriceMessage, 
                nasdaq::ModifyOrderMessageHandler,
                &nasdaq::ModifyOrderMessageHandler::onOrderExecutedWithPriceMessage
            >(buffer, modify_order_message_handlers_);
        };
    }

    void subscribe(nasdaq::ModifyOrderMessageHandler& handler) {
        modify_order_message_handlers_.push_back(&handler);
    }

    MessageSize feed(byte_t* buffer) {
        const char message_type = *reinterpret_cast<char*>(buffer + sizeof(MessageSize));
        return dispatchers_[message_type](buffer) + sizeof(MessageSize);
    }

private:

    template<
        typename MessageT, 
        typename HandlerT,
        void (HandlerT::*HandlerFn)(MessageT*)
    >
    MessageSize dispatch(byte_t* buffer, const std::vector<HandlerT*>& handlers) {
        if (auto message = parse<MessageT>(buffer); message.has_value()) 
            for (auto handler: handlers) ((*handler).*HandlerFn)(*message);
        return sizeof(MessageT);
    }

};
