#ifndef TRON_MANY_WORLD_HPP
#define TRON_MANY_WORLD_HPP

#include <iostream>
#include <stack>
#include <utility>
#include <vector>

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

    bool positionValid(const Position& p) const;
    bool moveValid(const Position& p, Move m) const;

    void move(Move redMove, Move greenMove);
    void undo();

  private:
    std::vector<std::vector<Cell> > map_;
    std::stack<std::pair<Move, Move> > history_;
    Position redPos_, greenPos_;
    State state_;
};

GameWorld::Move operator++(GameWorld::Move& m);

GameWorld::Position operator+(const GameWorld::Position& p, GameWorld::Move m);
GameWorld::Position operator-(const GameWorld::Position& p, GameWorld::Move m);

std::istream& operator>>(std::istream& istream, GameWorld::Position& p);
std::istream& operator>>(std::istream& istream, GameWorld::Player& p);
std::ostream& operator<<(std::ostream& ostream, GameWorld::Move m);

#endif // TRON_MANY_WORLD_HPP
