#ifndef STATE_SPACE_H
#define STATE_SPACE_H

#include <memory>

class StateSpace {
public:
	/** Return successors of this state. */
	virtual std::vector<std::shared_ptr<StateSpace>> GetSuccessors() = 0;
	/** Return predecessors of this state. */
	virtual std::vector<std::shared_ptr<StateSpace>> GetPredecessors() = 0;
	/** Must implement equality operator. */
	virtual bool StateSpace::operator ==(const StateSpace& other) const = 0;
	/** Must implement hash of the statespace. */
	virtual std::size_t Hash() const = 0;

	/** Inequality operator. */
	virtual bool StateSpace::operator !=(const StateSpace& other) const { return !((*this) == other); };
};

#endif