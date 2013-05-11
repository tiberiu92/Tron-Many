// Matching header
#include "player.hpp"

// Project headers
#include "world.hpp"

Player otherPlayer(Player player)
{
    return player == RedPlayer ? GreenPlayer : RedPlayer;
}

bool isWinner(const GameWorld& world, Player player)
{
    static GameWorld::State wins[] = {
        GameWorld::RedWonState, GameWorld::GreenWonState
    };
    
    GameWorld::State state = world.state();
    return state == wins[player];
}