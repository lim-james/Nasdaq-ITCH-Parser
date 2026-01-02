#pragma once 

#include <cstdint>
#include <expected>

enum class OrderMessageParseError: char {
    INVALID_BUFFER_LENGTH
};

using byte_t = unsigned char;

template<typename OrderMessage>
auto parse(byte_t* buffer) -> std::expected<OrderMessage*, OrderMessageParseError> {
    constexpr std::size_t MESSAGE_SIZE  = sizeof(OrderMessage); 
    constexpr std::size_t BUFFER_OFFSET = sizeof(std::uint16_t);

    const std::uint16_t buffer_length = *reinterpret_cast<std::uint16_t*>(buffer);
    if (buffer_length < MESSAGE_SIZE) 
        return std::unexpected(OrderMessageParseError::INVALID_BUFFER_LENGTH);
    
    return reinterpret_cast<OrderMessage*>(buffer + BUFFER_OFFSET);
}
