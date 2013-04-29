// Standard headers
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// Project headers
#include "player.hpp"
#include "world.hpp"

void getProximalArea(const GameWorld& world, const GameWorld::Position& pos,
    int depth, std::vector<GameWorld::Position>& area)
{
    if (depth == 0)
        return;

    if (std::find(area.begin(), area.end(), pos) != area.end())
        return;

    area.push_back(pos);

    for (Move move = MovesBegin; move != MovesEnd; ++move)
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

double evaluateBoard(const GameWorld& world, Player player)
{    
    std::vector<GameWorld::Position> area;
    double playerSpread, enemySpread;
    
    getProximalArea(world, world.position(player), 10, area);
    double rowSpread = getAreaSpread(area, &GameWorld::Position::first);
    double colSpread = getAreaSpread(area, &GameWorld::Position::second);
    playerSpread = rowSpread * colSpread;
    
    area.clear();
    getProximalArea(world, world.position(otherPlayer(player)), 15, area);
    rowSpread = getAreaSpread(area, &GameWorld::Position::first);
    colSpread = getAreaSpread(area, &GameWorld::Position::second);
    enemySpread = rowSpread * colSpread;
    
    return playerSpread - enemySpread;
}

double nash(GameWorld& world, Player player, int depth, Move& returnMove)
{
    Player enemy = otherPlayer(player);
    Move dummy = Left; // Doesn't matter

    GameWorld::Position playerPos = world.position(player);
    GameWorld::Position enemyPos = world.position(enemy);

    double winScore = 999.0, lossScore = -999.0, drawScore = -400.0;
    double scores[MovesSize][MovesSize];
    double worstScore = lossScore;

    for (Move pMove = MovesBegin; pMove != MovesEnd; ++pMove)
    {
        if (!world.moveValid(playerPos, pMove))
            continue;
            
        double bestScore = winScore;
    
        for (Move eMove = MovesBegin; eMove != MovesEnd; ++eMove)
        {
            if (!world.moveValid(enemyPos, eMove))
                continue;

            world.move(player, pMove, enemy, eMove);

            if (isWinner(world, player))
                scores[pMove][eMove] = winScore;
            else if (isWinner(world, enemy))
                scores[pMove][eMove] = lossScore;
            else if (world.state() == GameWorld::DrawState)
                scores[pMove][eMove] = drawScore;
            else if (depth > 1)
                scores[pMove][eMove] = nash(world, player, depth - 1, dummy);
            else
                scores[pMove][eMove] = evaluateBoard(world, player);

            world.undo();
            
            if (scores[pMove][eMove] < bestScore) {
                bestScore = scores[pMove][eMove];
            }
        }

        if (worstScore < bestScore) {
            worstScore = bestScore;
            returnMove = pMove;
        }
    }

    return worstScore;
}

int main()
{
    Player player;
    Move move = Left; // Prevents "move is uninitialized" warnings

    std::cin >> player;
    GameWorld world(std::cin);

    nash(world, player, 4, move);
    std::cout << move << "\n";

    return 0;
}
