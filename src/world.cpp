#include "world.hpp"
#include <cassert>
#include <iostream>
#include <vector>

// ============================================================================
//   Constructors and Destructors
// ----------------------------------------------------------------------------

GameWorld::GameWorld(std::istream& istream)
{
    istream >> redPos_;
    istream >> greenPos_;

    std::size_t rows, cols;
    istream >> rows >> cols;

    map_.resize(rows, std::vector<Cell>(cols));

    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c) {
            istream >> map_[r][c];
        }
    }
}


// ============================================================================
//   Getters, Setters, Predicates
// ----------------------------------------------------------------------------

std::size_t GameWorld::rows() const { return map_.size(); }
std::size_t GameWorld::cols() const { return map_[0].size(); }

const GameWorld::Position& GameWorld::position(Player p) const {
    return p == RedPlayer ? redPos_ : greenPos_;
}

const GameWorld::Cell& GameWorld::cell(const Position& pos) const {
    return map_[pos.first][pos.second];
}


// ============================================================================
//   Move and Undo
// ----------------------------------------------------------------------------

void GameWorld::move(Move redMove, Move greenMove)
{
    assert(moveValid(*this, RedPlayer, redMove));
    assert(moveValid(*this, GreenPlayer, greenMove));
    // TODO: Implement
}

//void GameWorld::undo()
//{
//}

// ============================================================================
//   Non-member functions
// ----------------------------------------------------------------------------

bool positionValid(const GameWorld& w, const GameWorld::Position& p)
{
    return 0 <= p.first && static_cast<std::size_t>(p.first) < w.rows()
        && 0 <= p.second && static_cast<std::size_t>(p.second) < w.cols();
}

bool moveValid(const GameWorld& w, GameWorld::Player p, GameWorld::Move m)
{
    GameWorld::Position pos = w.position(p) + m;
    return positionValid(w, pos) && w.cell(pos) == GameWorld::EmptySymbol;
}


// ============================================================================
//   Non-member operators
// ----------------------------------------------------------------------------

GameWorld::Move operator++(GameWorld::Move& m)
{
    typedef GameWorld::Move Move;
    return m = static_cast<Move>(static_cast<int>(m) + 1);
}

GameWorld::Position operator+(const GameWorld::Position& p, GameWorld::Move m)
{
    static const int drow[] = { 0, 0, -1, 1 };
    static const int dcol[] = { -1, 1, 0, 0 };
    return GameWorld::Position(p.first + drow[m], p.second + dcol[m]);
}

GameWorld::Position operator-(const GameWorld::Position& p, GameWorld::Move m)
{
    static const int drow[] = { 0, 0, 1, -1 };
    static const int dcol[] = { 1, -1, 0, 0 };
    return GameWorld::Position(p.first + drow[m], p.second + dcol[m]);
}

std::istream& operator>>(std::istream& istream, GameWorld::Position& p)
{
    istream >> p.first >> p.second;
    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const GameWorld::Position& p)
{
    ostream << p.first << " " << p.second;
    return ostream;
}
