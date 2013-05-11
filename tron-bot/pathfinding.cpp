// Matching header
#include "pathfinding.hpp"

// Standard headers
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

// Project headers
#include "world.hpp"


// ============================================================================
//   Implementation details
// ----------------------------------------------------------------------------

namespace
{
    // 'GameWorld::Position' is used a lot in this file. Use
    // a typedef to reduce typing.
    typedef GameWorld::Position Position;


    // A bidimensional structure that maps a position to a
    // given value of an arbitrary type.
    template<typename T>
    class PositionMap
    {
      public:
        PositionMap(std::size_t rows, std::size_t cols, const T& val)
            : map_(rows, std::vector<T>(cols, val)) {}

        PositionMap(std::size_t rows, std::size_t cols)
            : map_(rows, std::vector<T>(cols)) {}

        const T& operator[](const Position& pos) const {
            return map_[pos.first][pos.second];
        }

        T& operator[](const Position& pos) {
            return map_[pos.first][pos.second];
        }

      private:
        std::vector<std::vector<T> > map_;
    };


    // Functor that, for given a costs table represented as a
    // 'PositionMap<int>', compares two positions.
    class PositionComparator
    {
      public:
        PositionComparator(const PositionMap<int>& costs)
            : costs_(costs) {}

        bool operator()(const Position& a, const Position& b) {
            return costs_[a] > costs_[b];
        }

      private:
        const PositionMap<int>& costs_;
    };

    bool isArticulation (const GameWorld &world, Position c) {
        int count = 0;
        for (Move move = MovesBegin; move != MovesEnd; ++move) {
            if (!world.moveValid(c, move)) {
                count ++;
            }
        }
        if (count >= 2) {
            return true;
        } else {
            return false;
        }
    }
}

// ============================================================================
//   Visible declarations
// ----------------------------------------------------------------------------

int manhattanDistance(const Position& a, const Position& b)
{
    return std::abs(a.first - b. first) - std::abs(a.second - b.second);
}

int aStar(const GameWorld& world, const Position& start, const Position& end,
    DistanceHeuristic heuristic, Move& returnMove)
{
    using namespace std;

    // The fringe is the collection of nodes that can potentially be
    // expanded to reach the goal. Initially, it only contains the start.
    vector<Position> fringe;
    fringe.push_back(start);

    // This map indicates what move was made to reach each of the positions
    // it contains. Use 'MovesEnd' to indicate an invalid or uninitialized move.
    PositionMap<Move> from(world.rows(), world.cols(), MovesEnd);

    // G values are the exact distances from the start node to
    // any given node.
    PositionMap<int> gValues(world.rows(), world.cols(), 999999);
    gValues[start] = 0;

    // F values are a lower bound on the distance from start to end,
    // considering the path that goes through a given node.
    PositionMap<int> fValues(world.rows(), world.cols());
    fValues[start] = heuristic(start, end);

    // The fringe will be ordered by F values.
    PositionComparator comp(fValues);
    make_heap(fringe.begin(), fringe.end(), comp);

    while (!fringe.empty())
    {
        Position cell = fringe.front();
        pop_heap(fringe.begin(), fringe.end(), comp);
        fringe.pop_back();

        if (isArticulation (world, cell)) {
            continue;
        }

        if (cell == end)
            break;

        for (Move move = MovesBegin; move != MovesEnd; ++move)
        {
            if (cell + move != end && !world.moveValid(cell, move))
                continue;

            int newGValue = gValues[cell] + 1;
            Position child = cell + move;

            if (newGValue >= gValues[child]) {
                continue;
            }


            from[child] = move;
            gValues[child] = newGValue;
            fValues[child] = newGValue + heuristic(child, end);

            if (find(fringe.begin(), fringe.end(), child) == fringe.end()) {
                fringe.push_back(child);
                push_heap(fringe.begin(), fringe.end(), comp);
            }
        }
    }

    if (from[end] == MovesEnd) {
        returnMove = MovesEnd;
        return -1;
    }

    int pathLength = 0;
    Position node = end;

    while (node != start)
    {
        returnMove = from[node];
        node = node - returnMove;
        pathLength += 1;
    }

    return pathLength;
}
