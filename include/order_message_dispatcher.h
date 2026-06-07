#pragma once

#include <unordered_map>
#include <functional>
#include <span>

#include "nasdaq/type.h"
#include "nasdaq/handlers/dlcr_message_handler.h"
#include "nasdaq/handlers/net_order_balance_indicator_message_handler.h"
#include "nasdaq/handlers/net_order_balance_indicator_message_handler.h"
#include "nasdaq/handlers/trade_message_handler.h"
#include "nasdaq/handlers/add_order_message_handler.h"
#include "nasdaq/handlers/system_event_message_handler.h"
#include "nasdaq/handlers/modify_order_message_handler.h"
#include "nasdaq/handlers/stock_related_message_handler.h"
#include "nasdaq/handlers/retail_interest_message_handler.h"
#include "nasdaq/handlers/net_order_balance_indicator_message_handler.h"

#include "order_message_parser.h"

class OrderMessageDispatcher {

    using buffer_t = std::span<std::byte>;

private:

    using DispatcherFn = std::function<buffer_t(buffer_t)>;

    std::unordered_map<char, DispatcherFn> dispatchers_;

    std::vector<nasdaq::DLCRMessageHandler*> dlcr_message_handlers_;
    std::vector<nasdaq::TradeMessageHandler*> trade_message_handlers_;
    std::vector<nasdaq::AddOrderMessageHandler*> add_order_message_handlers_;
    std::vector<nasdaq::SystemEventMessageHandler*> system_event_message_handler_;
    std::vector<nasdaq::ModifyOrderMessageHandler*> modify_order_message_handlers_;
    std::vector<nasdaq::StockRelatedMessageHandler*> stock_related_message_handlers_;
    std::vector<nasdaq::RetailInterestMessageHandler*> retail_interest_message_handlers_;
    std::vector<nasdaq::NOIIMessageHandler*> noii_message_handlers_;

public:

    OrderMessageDispatcher() {
        using namespace nasdaq;

        addDispatcher<'O', &DLCRMessageHandler::onDLCRMessage, &OrderMessageDispatcher::dlcr_message_handlers_>();

        addDispatcher<'P', &TradeMessageHandler::onTradeMessage, &OrderMessageDispatcher::trade_message_handlers_>();
        addDispatcher<'Q', &TradeMessageHandler::onCrossTradeMessage, &OrderMessageDispatcher::trade_message_handlers_>();
        addDispatcher<'B', &TradeMessageHandler::onBrokenTradeMessage, &OrderMessageDispatcher::trade_message_handlers_>();

        addDispatcher<'A', &AddOrderMessageHandler::onAddOrderMessage, &OrderMessageDispatcher::add_order_message_handlers_>();
        addDispatcher<'F', &AddOrderMessageHandler::onAddOrderMPIDMessage, &OrderMessageDispatcher::add_order_message_handlers_>();

        addDispatcher<'S', &SystemEventMessageHandler::onSystemEventMessage, &OrderMessageDispatcher::system_event_message_handler_>();

        addDispatcher<'E', &ModifyOrderMessageHandler::onOrderExecutedMessage, &OrderMessageDispatcher::modify_order_message_handlers_>();
        addDispatcher<'C', &ModifyOrderMessageHandler::onOrderExecutedWithPriceMessage, &OrderMessageDispatcher::modify_order_message_handlers_>();
        addDispatcher<'X', &ModifyOrderMessageHandler::onOrderCancelMessage, &OrderMessageDispatcher::modify_order_message_handlers_>();
        addDispatcher<'D', &ModifyOrderMessageHandler::onOrderDeleteMessage, &OrderMessageDispatcher::modify_order_message_handlers_>();
        addDispatcher<'U', &ModifyOrderMessageHandler::onOrderReplaceMessage, &OrderMessageDispatcher::modify_order_message_handlers_>();

        addDispatcher<'R', &StockRelatedMessageHandler::onStockDirectory, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'H', &StockRelatedMessageHandler::onStockTradingAction, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'Y', &StockRelatedMessageHandler::onRegSHORestriction, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'L', &StockRelatedMessageHandler::onMarketParticipationPosition, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'V', &StockRelatedMessageHandler::onMWCBDeclineLevelMessage, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'W', &StockRelatedMessageHandler::onMWCBStatusMessage, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'K', &StockRelatedMessageHandler::onQuotePeriodUpdate, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'J', &StockRelatedMessageHandler::onLULDAuctionCollar, &OrderMessageDispatcher::stock_related_message_handlers_>();
        addDispatcher<'h', &StockRelatedMessageHandler::onOperationHalt, &OrderMessageDispatcher::stock_related_message_handlers_>();

        addDispatcher<'N', &RetailInterestMessageHandler::onRetailInterestMessage, &OrderMessageDispatcher::retail_interest_message_handlers_>();

        addDispatcher<'I', &nasdaq::NOIIMessageHandler::onNOIIMessage, &OrderMessageDispatcher::noii_message_handlers_>();
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

    void subscribe(nasdaq::NOIIMessageHandler& handler) {
        noii_message_handlers_.push_back(&handler);
    }

    buffer_t feed(buffer_t buffer) {
        static constexpr auto MESSAGE_HEADER_SIZE = sizeof(nasdaq::MessageType);

        const auto message_type = *reinterpret_cast<nasdaq::MessageType*>(buffer.data());
        
        auto it = dispatchers_.find(message_type);
        if (it == dispatchers_.end())
            return buffer;

        auto [_, dispatcher] = *it;
        return dispatcher(buffer.subspan(MESSAGE_HEADER_SIZE));
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

    template<char message_type, auto HandlerFn, auto handlers>
    void addDispatcher() {
        dispatchers_[message_type] = [this](buffer_t buffer) {
            return dispatchMessage<HandlerFn, handlers>(buffer);
        };
    }

    template<auto HandlerFn, auto HandlersPtr>
    buffer_t dispatchMessage(buffer_t buffer) {
        using MessageT = extract_message_type<decltype(HandlerFn)>::type;
        if (auto message = parse<MessageT>(buffer); message.has_value()) 
            for (auto handler: this->*HandlersPtr) ((*handler).*HandlerFn)(*message);
        return buffer.subspan(sizeof(MessageT));
    }
};
