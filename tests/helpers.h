#pragma once

#include <array>
#include <cstddef>

template <typename... Ts>
constexpr auto make_bytes(Ts... vals) {
    return std::array<std::byte, sizeof...(vals)>{ std::byte(vals)... };
}
