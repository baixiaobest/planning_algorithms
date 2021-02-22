#ifndef STATE_SPACE_H
#define STATE_SPACE_H

class StateSpace {
public:
	/** Return successors of this state. */
	virtual std::vector<StateSpace> GetSuccessors() = 0;
	/** Return predecessors of this state. */
	virtual std::vector<StateSpace> GetPredecessors() = 0;
	/** Must implement equality operator. */
	virtual bool StateSpace::operator ==(const StateSpace& other) const = 0;
	/** Must implement inequality operator. */
	virtual bool StateSpace::operator !=(const StateSpace& other) const = 0;
};

#endif