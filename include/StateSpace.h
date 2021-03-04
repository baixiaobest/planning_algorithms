#ifndef STATE_SPACE_H
#define STATE_SPACE_H

#include <memory>
#include <vector>

/** An interface of statespace. Custom statespace class needs 
 *  to inherit from this class and implement the abstrct functions.
 */
class StateSpace {
public:
	using StateSpaceCostPair = std::pair<std::shared_ptr<StateSpace>, double>;
	/** Return successors of this state. This is a vector of a pair of statespace and cost. */
	virtual std::vector<StateSpaceCostPair> GetSuccessors() = 0;
	/** Return predecessors of this state. This is a vector of a pair of statespace and cost. */
	virtual std::vector<StateSpaceCostPair> GetPredecessors() = 0;
	/** Must implement equality operator. */
	virtual bool StateSpace::operator ==(const StateSpace& other) const = 0;
	/** Must implement hash of the statespace. */
	virtual std::size_t Hash() const = 0;

	/** Inequality operator. */
	virtual bool StateSpace::operator !=(const StateSpace& other) const { return !((*this) == other); };
};

#endif