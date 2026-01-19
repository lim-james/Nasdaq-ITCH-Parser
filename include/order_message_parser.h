#pragma once 

#include <cstdint>
#include <expected>

enum class OrderMessageParseError: char {
    INVALID_BUFFER_LENGTH
};

using byte_t = unsigned char;
using MessageSize = std::uint16_t;

template<typename OrderMessage>
auto parse(byte_t* buffer) -> std::expected<OrderMessage*, OrderMessageParseError> {
    constexpr MessageSize MESSAGE_SIZE  = sizeof(OrderMessage); 
    constexpr std::size_t BUFFER_OFFSET = sizeof(MessageSize);

    const MessageSize buffer_length = *reinterpret_cast<MessageSize*>(buffer);
    if (buffer_length < MESSAGE_SIZE) 
        return std::unexpected(OrderMessageParseError::INVALID_BUFFER_LENGTH);
    
    return reinterpret_cast<OrderMessage*>(buffer + BUFFER_OFFSET);
}
