#ifndef GRID_STATE_SPACE_H
#define GRID_STATE_SPACE_H

#include "StateSpace.h"
#include <vector>

class GridStateSpace : public StateSpace {
public:
	GridStateSpace() : x_(0), y_(0) {};
	GridStateSpace(int x, int y) : x_(x), y_(y) {};
	virtual std::vector<std::shared_ptr<StateSpace>> GetSuccessors() override { return GetNeighbors(); };
	virtual std::vector<std::shared_ptr<StateSpace>> GetPredecessors() override { return GetNeighbors(); };
	virtual bool GridStateSpace::operator ==(const StateSpace& other) const override;
	virtual std::size_t Hash() const;
	int GetX() { return x_; };
	int GetY() { return y_; };
private:
	std::vector<std::shared_ptr<StateSpace>> GetNeighbors();
	int x_;
	int y_;
};

inline
std::vector<std::shared_ptr<StateSpace>> GridStateSpace::GetNeighbors() {
	return {std::make_shared<GridStateSpace>(x_ - 1, y_), std::make_shared<GridStateSpace>(x_ + 1, y_),
			std::make_shared<GridStateSpace>(x_, y_ - 1), std::make_shared<GridStateSpace>(x_, y_ + 1)};
}

inline
bool GridStateSpace::operator ==(const StateSpace& other) const {
	const auto& otherSS = dynamic_cast<const GridStateSpace&>(other);
	return x_ == otherSS.x_ && y_ == otherSS.y_;
}

inline
std::size_t GridStateSpace::Hash() const {
	return x_ | y_;
}

#endif