// Matching header
#include "world.hpp"

// Standard libraries
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

// Project headers
#include "player.hpp"


// ============================================================================
//   Constructor
// ----------------------------------------------------------------------------

GameWorld::GameWorld(std::istream& istream)
    : state_(GameRunningState)
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
//   Getters
// ----------------------------------------------------------------------------

std::size_t GameWorld::rows() const { return map_.size(); }
std::size_t GameWorld::cols() const { return map_[0].size(); }

GameWorld::State GameWorld::state() const { return state_; }

const GameWorld::Position& GameWorld::position(Player p) const {
    return p == RedPlayer ? redPos_ : greenPos_;
}

const GameWorld::Cell& GameWorld::cell(const Position& pos) const {
    return map_[pos.first][pos.second];
}


// ============================================================================
//   Predicates
// ----------------------------------------------------------------------------

bool GameWorld::positionValid(const Position& p) const
{
    return 0 <= p.first && static_cast<std::size_t>(p.first) < rows()
        && 0 <= p.second && static_cast<std::size_t>(p.second) < cols();
}

bool GameWorld::moveValid(const Position& p, Move m) const
{
    if (!positionValid(p))
        return false;

    Position pos = p + m;
    return positionValid(pos) && cell(pos) == EmptySymbol;
}


// ============================================================================
//   Move and Undo
// ----------------------------------------------------------------------------

void GameWorld::move(Player p1, Move m1, Player p2, Move m2)
{
    assert(p1 != p2);
    assert(state() == GameRunningState);
    
    Move redMove = (p1 == RedPlayer) ? m1 : m2;
    Move greenMove = (p2 == GreenPlayer) ? m2 : m1;

    history_.push(std::make_pair(redMove, greenMove));
    
    bool redMoveValid = moveValid(redPos_, redMove);
    bool greenMoveValid = moveValid(greenPos_, greenMove);

    map_[redPos_.first][redPos_.second] = GameWorld::RedSymbol;
    map_[greenPos_.first][greenPos_.second] = GameWorld::GreenSymbol;
    
    redPos_ = redPos_ + redMove;
    greenPos_ = greenPos_ + greenMove;
    
    if (!redMoveValid && !greenMoveValid) {
        state_ = DrawState;
        return;
    }

    if (!redMoveValid) {
        state_ = GreenWonState;
        return;
    }

    if (!greenMoveValid) {
        state_ = RedWonState;
        return;
    }
    
    if (redPos_ == greenPos_) {
        state_ = DrawState;
        return;
    }
}

void GameWorld::undo()
{
    assert(!history_.empty());

    std::pair<Move, Move> top = history_.top();
    history_.pop();

    map_[redPos_.first][redPos_.second] = EmptySymbol;
    map_[greenPos_.first][greenPos_.second] = EmptySymbol;

    redPos_ = redPos_ - top.first;
    greenPos_ = greenPos_ - top.second;

    state_ = GameRunningState;
}


// ============================================================================
//   Non-member Operators
// ----------------------------------------------------------------------------

Move operator++(Move& m)
{
    return m = static_cast<Move>(static_cast<int>(m) + 1);
}

GameWorld::Position operator+(const GameWorld::Position& p, Move m)
{
    static const int drow[] = { 0, 0, -1, 1 };
    static const int dcol[] = { -1, 1, 0, 0 };
    return GameWorld::Position(p.first + drow[m], p.second + dcol[m]);
}

GameWorld::Position operator-(const GameWorld::Position& p, Move m)
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

std::istream& operator>>(std::istream& istream, Player& p)
{
    char symbol;
    istream >> symbol;

    if (symbol == GameWorld::RedSymbol) p = RedPlayer;
    else if (symbol == GameWorld::GreenSymbol) p = GreenPlayer;

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, Move m)
{
    static const char* moves[] = { "LEFT", "RIGHT", "UP", "DOWN" };
    return ostream << moves[m];
}