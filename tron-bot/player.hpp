#ifndef TRON_MANY_PLAYER_HPP
#define TRON_MANY_PLAYER_HPP

class GameWorld;

enum Player {
    RedPlayer = 0, GreenPlayer = 1
};

Player otherPlayer(Player player);
bool isWinner(const GameWorld& world, Player player);

#endif // TRON_MANY_PLAYER_HPP