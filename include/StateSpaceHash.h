#ifndef STATESPACE_HASH_H
#define STATESPACE_HASH_H

template<typename StateSpaceType>
class StateSpaceHash {
public:
	std::size_t operator()(StateSpaceType const& ss) const {
		return ss.Hash();
	}
};

#endif