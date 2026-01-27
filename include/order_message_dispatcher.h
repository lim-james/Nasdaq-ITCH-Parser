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
        using namespace nasdaq;

        addModifyDispatcher<&ModifyOrderMessageHandler::onOrderExecutedMessage>('E');
        addModifyDispatcher<&ModifyOrderMessageHandler::onOrderExecutedWithPriceMessage>('C');
        addModifyDispatcher<&ModifyOrderMessageHandler::onOrderCancelMessage>('X');
        addModifyDispatcher<&ModifyOrderMessageHandler::onOrderDeleteMessage>('D');
    }

    void subscribe(nasdaq::ModifyOrderMessageHandler& handler) {
        modify_order_message_handlers_.push_back(&handler);
    }

    MessageSize feed(byte_t* buffer) {
        const char message_type = *reinterpret_cast<char*>(buffer + sizeof(MessageSize));
        return dispatchers_[message_type](buffer) + sizeof(MessageSize);
    }

private:

    template<typename T>
    struct extract_message_type;

    template<
        typename HandlerInterface,
        typename MessageT
    >
    struct extract_message_type<void (HandlerInterface::*)(MessageT*)> {
        using type = MessageT;
    };

    template<auto HandlerFn>
    void addModifyDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchModifyOrderMessage<HandlerFn>(buffer);
        };
    }

    template<auto HandlerFn>
    MessageSize dispatchModifyOrderMessage(byte_t* buffer) {
        using MessageT = extract_message_type<decltype(HandlerFn)>::type;
        if (auto message = parse<MessageT>(buffer); message.has_value()) 
            for (auto handler: modify_order_message_handlers_) ((*handler).*HandlerFn)(*message);
        return sizeof(MessageT);
    }

};
