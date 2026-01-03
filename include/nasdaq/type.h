#pragma once 

#include <cstdint>

#include "big_endian.h"

namespace nasdaq {
    using MessageType   = char;
    using LocateCode    = BigEndian<std::uint16_t>;
    using TrackingNum   = BigEndian<std::uint16_t>;
    using Timestamp     = std::uint64_t;
    using ReferenceNum  = BigEndian<std::uint64_t>;
    using NumShares     = BigEndian<std::uint32_t>;
}
