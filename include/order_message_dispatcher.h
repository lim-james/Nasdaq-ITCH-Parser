#pragma once

#include <unordered_map>
#include <functional>

#include "nasdaq/handlers/dlcr_message_handler.h"
#include "nasdaq/handlers/trade_message_handler.h"
#include "nasdaq/handlers/add_order_message_handler.h"
#include "nasdaq/handlers/system_event_message_handler.h"
#include "nasdaq/handlers/modify_order_message_handler.h"
#include "nasdaq/handlers/stock_related_message_handler.h"
#include "nasdaq/handlers/retail_interest_message_handler.h"

#include "order_message_parser.h"

using byte_t = unsigned char;

class OrderMessageDispatcher {
private:

    using DispatcherFn = std::function<MessageSize(byte_t*)>;

    std::unordered_map<char, DispatcherFn> dispatchers_;

    std::vector<nasdaq::DLCRMessageHandler*> dlcr_message_handlers_;
    std::vector<nasdaq::TradeMessageHandler*> trade_message_handlers_;
    std::vector<nasdaq::AddOrderMessageHandler*> add_order_message_handlers_;
    std::vector<nasdaq::SystemEventMessageHandler*> system_event_message_handler_;
    std::vector<nasdaq::ModifyOrderMessageHandler*> modify_order_message_handlers_;
    std::vector<nasdaq::StockRelatedMessageHandler*> stock_related_message_handlers_;
    std::vector<nasdaq::RetailInterestMessageHandler*> retail_interest_message_handlers_;

public:

    OrderMessageDispatcher() {
        using namespace nasdaq;

        addDLCRDispatcher<&DLCRMessageHandler::onDLCRMessage>('E');

        addTradeDispatcher<&TradeMessageHandler::onTradeMessage>('P');
        addTradeDispatcher<&TradeMessageHandler::onCrossTradeMessage>('Q');
        addTradeDispatcher<&TradeMessageHandler::onBrokenTradeMessage>('B');

        addAddOrderDispatcher<&AddOrderMessageHandler::onAddOrderMessage>('A');
        addAddOrderDispatcher<&AddOrderMessageHandler::onAddOrderMPIDMessage>('F');

        addSystemEventDispatcher<&SystemEventMessageHandler::onSystemEventMessage>('S');

        addModifyOrderDispatcher<&ModifyOrderMessageHandler::onOrderExecutedMessage>('E');
        addModifyOrderDispatcher<&ModifyOrderMessageHandler::onOrderExecutedWithPriceMessage>('C');
        addModifyOrderDispatcher<&ModifyOrderMessageHandler::onOrderCancelMessage>('X');
        addModifyOrderDispatcher<&ModifyOrderMessageHandler::onOrderDeleteMessage>('D');
        addModifyOrderDispatcher<&ModifyOrderMessageHandler::onOrderReplaceMessage>('U');

        addStockRelatedDispatcher<&StockRelatedMessageHandler::onStockDirectory>('R');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onStockTradingAction>('H');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onRegSHORestriction>('Y');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onMarketParticipationPosition>('L');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onMWCBDeclineLevelMessage>('V');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onMWCBStatusMessage>('W');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onQuotePeriodUpdate>('K');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onLULDAuctionCollar>('J');
        addStockRelatedDispatcher<&StockRelatedMessageHandler::onOperationHalt>('h');

        addRetailInterestDispatcher<&RetailInterestMessageHandler::onRetailInterestMessage>('N');
    }

    void subscribe(nasdaq::DLCRMessageHandler& handler) {
        dlcr_message_handlers_.push_back(&handler);
    }

    void subscribe(nasdaq::TradeMessageHandler& handler) {
        trade_message_handlers_.push_back(&handler);
    }

    void subscribe(nasdaq::AddOrderMessageHandler& handler) {
        add_order_message_handlers_.push_back(&handler);
    }

    void subscribe(nasdaq::SystemEventMessageHandler& handler) {
        system_event_message_handler_.push_back(&handler);
    }

    void subscribe(nasdaq::ModifyOrderMessageHandler& handler) {
        modify_order_message_handlers_.push_back(&handler);
    }

    void subscribe(nasdaq::StockRelatedMessageHandler& handler) {
        stock_related_message_handlers_.push_back(&handler);
    }

    void subscribe(nasdaq::RetailInterestMessageHandler& handler) {
        retail_interest_message_handlers_.push_back(&handler);
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
    void addDLCRDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::dlcr_message_handlers_
            >(buffer);
        };
    }

    template<auto HandlerFn>
    void addTradeDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::trade_message_handlers_
            >(buffer);
        };
    }

    template<auto HandlerFn>
    void addAddOrderDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::add_order_message_handlers_
            >(buffer);
        };
    }

    template<auto HandlerFn>
    void addSystemEventDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::system_event_message_handler_
            >(buffer);
        };
    }

    template<auto HandlerFn>
    void addModifyOrderDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::modify_order_message_handlers_
            >(buffer);
        };
    }

    template<auto HandlerFn>
    void addStockRelatedDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::stock_related_message_handlers_
            >(buffer);
        };
    }

    template<auto HandlerFn>
    void addRetailInterestDispatcher(char message_type) {
        dispatchers_[message_type] = [this](byte_t* buffer) {
            return this->dispatchMessage<
                HandlerFn,
                &OrderMessageDispatcher::retail_interest_message_handlers_
            >(buffer);
        };
    }

    template<auto HandlerFn, auto HandlersPtr>
    MessageSize dispatchMessage(byte_t* buffer) {
        using MessageT = extract_message_type<decltype(HandlerFn)>::type;
        if (auto message = parse<MessageT>(buffer); message.has_value()) 
            for (auto handler: this->*HandlersPtr) ((*handler).*HandlerFn)(*message);
        return sizeof(MessageT);
    }
};
