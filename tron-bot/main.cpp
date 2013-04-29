#include "world.hpp"

#include "world.hpp"
#include <algorithm>
#include <cmath>

#define INF 9999
void getProximalArea(const GameWorld& world, const GameWorld::Position& pos,
    int depth, std::vector<GameWorld::Position>& area)
{
    if (depth == 0)
        return;

    if (std::find(area.begin(), area.end(), pos) != area.end())
        return;

    area.push_back(pos);

    for (GameWorld::Move move = GameWorld::MovesBegin;
         move != GameWorld::MovesEnd; ++move)
    {
        if (!world.moveValid(pos, move))
            continue;

        GameWorld::Position pos2 = pos + move;
        getProximalArea(world, pos2, depth - 1, area);
    }
}

double getAreaSpread(const std::vector<GameWorld::Position>& area,
    GameWorld::Coordinate GameWorld::Position::*coord)
{
    double deviation = 0.0, average = 0.0;
    std::vector<GameWorld::Position>::const_iterator cell;

    for (cell = area.begin(); cell != area.end(); ++cell) {
        average += (*cell).*coord;
    }

    average /= area.size();

    for (cell = area.begin(); cell != area.end(); ++cell) {
        double temp = (*cell).*coord - average;
        deviation += temp * temp;
    }

    deviation = std::sqrt(deviation / area.size());

    return deviation;
}

int numNeighbours(const GameWorld& world, const GameWorld::Position& pos)
{
    int count = 0;

    for (GameWorld::Move move = GameWorld::MovesBegin;
         move != GameWorld::MovesEnd; ++move)
    {
        if (world.moveValid(pos, move))
            ++count;
    }

    return count;
}

bool isWinner(const GameWorld& world, GameWorld::Player player) {
    GameWorld::State state = world.state();
    if (player == GameWorld::RedPlayer && state == GameWorld::RedWonState) {
        return true;
    }
    if (player == GameWorld::GreenPlayer && state == GameWorld::GreenWonState) {
        return true;
    }
    return false;
}

int evalMove (GameWorld& world, GameWorld::Player player, int depth) {
        GameWorld::State state = world.state();
        GameWorld::Player enemy = player == GameWorld::RedPlayer ? GameWorld::GreenPlayer : GameWorld::RedPlayer;

        std::size_t playerArea, enemyArea;
        std::vector<GameWorld::Position> area;

        getProximalArea(world, world.position(player), depth, area);
        playerArea = area.size();

        area.clear();
        getProximalArea(world, world.position(enemy), depth, area);
        enemyArea = area.size();

        if (isWinner(world, player)) {
            return INF;
        }
        if (isWinner(world, enemy)) {
            return -INF;
        }
        if (state == GameWorld::DrawState) {
            return -20;
        }
        return playerArea - enemyArea;

}

int negaMax (GameWorld& world, GameWorld::Player player, int depth, GameWorld::Move& returnMove) {

    GameWorld::Player enemy = player == GameWorld::RedPlayer ? GameWorld::GreenPlayer : GameWorld::RedPlayer;
    GameWorld::Position positionPlayer = world.position(player);
    GameWorld::Position positionEnemy = world.position(enemy);
    GameWorld::State state = world.state();

    if (depth == 0) {
        return evalMove(world, player, 9);
    }
    int max = -INF;
    int score;
    GameWorld::Move bestMove;

    if (state == GameWorld::GameRunningState) {
        for (GameWorld::Move movePlayer = GameWorld::MovesBegin; movePlayer != GameWorld::MovesEnd; ++movePlayer) {
            if (!world.moveValid(positionPlayer, movePlayer)) {
                continue;
            }
           for (GameWorld::Move moveEnemy = GameWorld::MovesBegin; moveEnemy != GameWorld::MovesEnd; ++moveEnemy) {
                if (!world.moveValid(positionEnemy, moveEnemy)) {
                    continue;
                }
                world.move(player, movePlayer, enemy, moveEnemy);

                score = -negaMax(world, player, depth - 1, returnMove);
                world.undo();
                if (score > max) {
                    max = score;
                    bestMove = movePlayer;
                }
           }
        }
    }
    else {
        return evalMove(world, player, 9);
    }
    returnMove = bestMove;
    return max;
}

int main()
{

    GameWorld::Player player;
    std::cin >> player;
    GameWorld world (std::cin);

    GameWorld::Move bestMove;

    negaMax(world, player, 5, bestMove);

    std::cout << bestMove << '\n';



    return 0;
}
