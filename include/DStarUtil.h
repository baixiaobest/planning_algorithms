#ifndef DSTAR_UTIL_H
#define DSTAR_UTIL_H

#include <utility>

template<typename StateSpaceType>
class StateSpacePairHash {
public:
	std::size_t operator()(std::pair<StateSpaceType, StateSpaceType> const& ss) const {
		return ss.first.Hash() ^ ss.second.Hash();
	}
};

#endif