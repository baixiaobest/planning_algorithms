#include "../include/GridStateSpace.h"

/** Static variable initialization. */
bool GridStateSpace::hasBoundary_ = false;
int GridStateSpace::minX_ = 0;
int GridStateSpace::maxX_ = 0;
int GridStateSpace::minY_ = 0;
int GridStateSpace::maxY_ = 0;

std::vector<std::pair<std::shared_ptr<StateSpace>, double>> GridStateSpace::GetNeighbors() {
	std::vector<std::pair<std::shared_ptr<StateSpace>, double>> neighbors = {
		std::make_pair(std::make_shared<GridStateSpace>(x_ - 1, y_), 1.0),
		std::make_pair(std::make_shared<GridStateSpace>(x_ + 1, y_), 1.0),
		std::make_pair(std::make_shared<GridStateSpace>(x_, y_ - 1), 1.0),
		std::make_pair(std::make_shared<GridStateSpace>(x_, y_ + 1), 1.0) };

	// Remove neighbors that are beyond limit.
	if (hasBoundary_) {
		auto it = neighbors.begin();
		while (it != neighbors.end()) {
			const auto& neighbor = dynamic_cast<GridStateSpace&>(*(it->first));
			if (neighbor.x_ < minX_ || neighbor.x_ > maxX_
				|| neighbor.y_ < minY_ || neighbor.y_ > maxY_)
			{
				it = neighbors.erase(it);
			}
			else {
				it++;
			}
		}
	}
	return neighbors;
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

inline
void GridStateSpace::SetBoundary(int minX, int maxX, int minY, int maxY) {
	minX_ = minX;
	maxX_ = maxX;
	minY_ = minY;
	maxY_ = maxY;
}