#ifndef GRID_STATE_SPACE_H
#define GRID_STATE_SPACE_H

#include "StateSpace.h"
#include <vector>

/** Custom statespace, which is 4 connected grid state space. */
class GridStateSpace : public StateSpace {
public:
	GridStateSpace() : x_(0), y_(0) {};
	GridStateSpace(int x, int y) : x_(x), y_(y) {};
	virtual std::vector<StateSpaceCostPair> GetSuccessors() override { return GetNeighbors(); };
	virtual std::vector<StateSpaceCostPair> GetPredecessors() override { return GetNeighbors(); };
	virtual bool GridStateSpace::operator ==(const StateSpace& other) const override;
	virtual std::size_t Hash() const;
	int GetX() { return x_; };
	int GetY() { return y_; };
	/** Set the boundary of the statespace. */
	static void SetBoundary(int minX, int maxX, int minY, int maxY);
private:
	std::vector<std::pair<std::shared_ptr<StateSpace>, double>> GetNeighbors();
	int x_;
	int y_;
	/** Boundary of the statespace. */
	static int minX_;
	static int maxX_;
	static int minY_;
	static int maxY_;
	static bool hasBoundary_;
};

#endif