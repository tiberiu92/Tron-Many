#ifndef TRON_MANY_PATHFINDING_HPP
#define TRON_MANY_PATHFINDING_HPP

// Project headers
#include "world.hpp"

typedef int (*DistanceHeuristic)(const GameWorld::Position&,
    const GameWorld::Position&);

int manhattanDistance(const GameWorld::Position& a,
    const GameWorld::Position& b);
    
int aStar(const GameWorld&, const GameWorld::Position& start,
    const GameWorld::Position& end, DistanceHeuristic heuristic, Move& move);

#endif // TRON_MANY_PATHFINDING_HPP