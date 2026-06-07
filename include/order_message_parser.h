#pragma once 

#include <cstdint>
#include <expected>
#include <span>

enum class OrderMessageParseError: char {
    INVALID_BUFFER_LENGTH,
    NULL_BUFFER
};

using buffer_t = std::span<std::byte>;
using MessageSize = std::uint16_t;

template<typename OrderMessage>
auto parse(buffer_t buffer) -> std::expected<OrderMessage*, OrderMessageParseError> {
    if (buffer.empty()) 
        return std::unexpected(OrderMessageParseError::NULL_BUFFER);

    constexpr MessageSize MESSAGE_SIZE  = sizeof(OrderMessage); 
    constexpr std::size_t BUFFER_OFFSET = sizeof(MessageSize);

    const MessageSize buffer_length = *reinterpret_cast<MessageSize*>(buffer.data());
    if (buffer_length < MESSAGE_SIZE) 
        return std::unexpected(OrderMessageParseError::INVALID_BUFFER_LENGTH);
    
    return reinterpret_cast<OrderMessage*>(buffer.data() + BUFFER_OFFSET);
}
