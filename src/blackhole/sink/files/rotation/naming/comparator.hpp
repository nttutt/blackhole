#pragma once

#include <string>

#include "blackhole/config.hpp"

BLACKHOLE_BEG_NS

namespace sink {

namespace rotation {

namespace naming {

namespace comparator {

namespace time {

template<typename Backend>
struct descending {
    Backend& backend;

    descending(Backend& backend) : backend(backend) {}

    bool operator ()(const std::string& lhs, const std::string& rhs) const {
        return backend.changed(lhs) > backend.changed(rhs);
    }
};

} // namespace time

} // namespace comparator

} // namespace naming

} // namespace rotation

} // namespace sink

BLACKHOLE_END_NS
