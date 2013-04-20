#include "world.hpp"
#include <cassert>
#include <iostream>
#include <vector>


// ============================================================================
//   GameWorld Declarations
// ----------------------------------------------------------------------------

class GameWorld
{
  public:
    typedef char Cell;
    typedef int Coordinate;
    typedef std::pair<Coordinate, Coordinate> Position;

    enum Move {
        Left = 0, Right = 1, Up = 2, Down = 3,
        MovesBegin = Left, MovesEnd = 4
    };

    enum Player {
        RedPlayer, GreenPlayer
    };

    enum State {
        GameRunningState, RedWonState, GreenWonState, DrawState
    };

    static const Cell WallSymbol  = '#';
    static const Cell EmptySymbol = '-';
    static const Cell RedSymbol   = 'r';
    static const Cell GreenSymbol = 'g';

    GameWorld(std::istream& istream);

    std::size_t rows() const;
    std::size_t cols() const;

    State state() const;

    const Position& position(Player p) const;
    const Cell& cell(const Position& pos) const;

    void move(Move redMove, Move greenMove);
    // void undo();

  private:
    std::vector<std::vector<Cell> > map_;
    Position redPos_, greenPos_;
    State state_;
};


bool positionValid(const GameWorld& w, const GameWorld::Position& p);
bool moveValid(const GameWorld& w, GameWorld::Player p, GameWorld::Move m);

GameWorld::Move operator++(GameWorld::Move& m);

GameWorld::Position operator+(const GameWorld::Position& p, GameWorld::Move m);
GameWorld::Position operator-(const GameWorld::Position& p, GameWorld::Move m);

std::istream& operator>>(std::istream& istream, GameWorld::Position& p);
std::ostream& operator<<(std::ostream& ostream, const GameWorld::Position& p);


// ============================================================================
//   GameWorld Definitions
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

std::size_t GameWorld::rows() const { return map_.size(); }
std::size_t GameWorld::cols() const { return map_[0].size(); }

GameWorld::State GameWorld::state() const { return state_; }

const GameWorld::Position& GameWorld::position(Player p) const {
    return p == RedPlayer ? redPos_ : greenPos_;
}

const GameWorld::Cell& GameWorld::cell(const Position& pos) const {
    return map_[pos.first][pos.second];
}

void GameWorld::move(Move redMove, Move greenMove)
{
    assert(state() == GameRunningState);

    bool redMoveValid = moveValid(*this, RedPlayer, redMove);
    bool greenMoveValid = moveValid(*this, GreenPlayer, greenMove);

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

    Position newRedPos = redPos_ + redMove;
    Position newGreenPos = greenPos_ + greenMove;

    if (newRedPos == newGreenPos) {
        state_ = DrawState;
        return;
    }

    map_[redPos_.first][redPos_.second] = GameWorld::RedSymbol;
    map_[greenPos_.first][greenPos_.second] = GameWorld::GreenSymbol;

    redPos_ = newRedPos;
    greenPos_ = newGreenPos;

    state_ = GameRunningState;
}

//void GameWorld::undo()
//{
//}

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


// ============================================================================
//   Main
// ----------------------------------------------------------------------------

int main()
{
    return 0;
}
