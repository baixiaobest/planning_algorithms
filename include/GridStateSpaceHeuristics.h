#ifndef GRID_STATE_SPACE_HEURISTICS_H
#define GRID_STATE_SPACE_HEURISTICS_H

#include "../include/GridStateSpace.h"

class GridStateSpaceHeuristics {
public:
	double operator()(GridStateSpace ss1, GridStateSpace ss2) {
		return std::abs(ss1.GetX() - ss2.GetX()) + std::abs(ss1.GetY() - ss2.GetY());
	}
};

#endif