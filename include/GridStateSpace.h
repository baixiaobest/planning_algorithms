#ifndef GRID_STATE_SPACE_H
#define GRID_STATE_SPACE_H

#include "StateSpace.h"
#include <vector>

class GridStateSpace : public StateSpace {
public:
	GridStateSpace(int x, int y) : x_(x), y_(y) {};
	virtual std::vector<StateSpace> GetSuccessors() override { return GetNeighbors(); };
	virtual std::vector<StateSpace> GetPredecessors() override { return GetNeighbors(); };
	virtual bool StateSpace::operator ==(const StateSpace& other) const override { return x_ == other.x_ && y_ == other.y_; };
	virtual bool StateSpace::operator !=(const StateSpace& other) const override { return x_ != other.x_ || y_ != other.y_; };
	int GetX() { return x_; };
	int GetY() { return y_; };
private:
	std::vector<GridStateSpace> GetNeighbors();
	int x_;
	int y_;
};

inline
std::vector<GridStateSpace> GridStateSpace::GetNeighbors() {
	return {GridStateSpace(x_ - 1, y_), GridStateSpace(x_ + 1, y_), 
			GridStateSpace(x_, y_ - 1), GridStateSpace(x_, y_ + 1)};
}

#endif