#pragma once 

#include <cstdint>

#include "big_endian.h"

namespace nasdaq {

using MessageType   = char;
using LocateCode    = BigEndian<std::uint16_t>;
using TrackingNum   = BigEndian<std::uint16_t>;
using ReferenceNum  = BigEndian<std::uint64_t>;
using NumShares     = BigEndian<std::uint32_t>;
using Price4        = BigEndian<std::uint32_t>;

struct [[gnu::packed]] Timestamp {
    std::uint8_t raw_timestamp[6];

    operator std::uint64_t() const noexcept {
        return (static_cast<std::uint64_t>(raw_timestamp[0]) << 40) 
        |      (static_cast<std::uint64_t>(raw_timestamp[1]) << 32)
        |      (static_cast<std::uint64_t>(raw_timestamp[2]) << 24)
        |      (static_cast<std::uint64_t>(raw_timestamp[3]) << 16)
        |      (static_cast<std::uint64_t>(raw_timestamp[4]) << 8)
        |      (static_cast<std::uint64_t>(raw_timestamp[5]));
    }
};

}
