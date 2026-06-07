#pragma once 

#include <cstdint>
#include <expected>
#include <span>

enum class OrderMessageParseError: char {
    INVALID_BUFFER_LENGTH,
    NULL_BUFFER
};

using buffer_t = std::span<std::byte>;

template<typename OrderMessage>
auto parse(buffer_t buffer) -> std::expected<OrderMessage*, OrderMessageParseError> {
    if (buffer.empty()) 
        return std::unexpected(OrderMessageParseError::NULL_BUFFER);

    static constexpr auto MESSAGE_SIZE  = sizeof(OrderMessage); 

    if (buffer.size() < MESSAGE_SIZE) 
        return std::unexpected(OrderMessageParseError::INVALID_BUFFER_LENGTH);
    
    return reinterpret_cast<OrderMessage*>(buffer.data());
}
