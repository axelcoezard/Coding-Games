#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <stdint.h>
#include <cmath>

typedef struct {
    uint32_t nb_medailles_or;
    uint32_t nb_medailles_argent;
    uint32_t nb_medailles_bronze;
} PlayerScore;

typedef struct {
    uint32_t global_score;
    std::vector<PlayerScore> scores;    
} Player;

typedef struct {
    std::string gpu;
    uint32_t reg_0;
    uint32_t reg_1;
    uint32_t reg_2;
    uint32_t reg_3;
    uint32_t reg_4;
    uint32_t reg_5;
    uint32_t reg_6;
} MiniGame;

constexpr uint32_t MAXIMUM_PLAYER_COUNT = 3;

uint32_t ParseInteger()
{
    uint32_t value;
    std::cin >> value;
    std::cin.ignore();
    return value;
}

void ParsePlayers(std::vector<Player>& players, uint32_t nb_games)
{
    for (int i = 0; i < MAXIMUM_PLAYER_COUNT; i++)
    {
        auto& currentPlayer = players.at(i);

        std::cin >> currentPlayer.global_score;

        for (int j = 0; j < nb_games; j++)
        {
            auto& score = currentPlayer.scores[j];
            std::cin >> score.nb_medailles_or;
            std::cin >> score.nb_medailles_argent;
            std::cin >> score.nb_medailles_bronze;
        }

        std::cin.ignore();
    }
}

void ParseMiniGames(std::vector<MiniGame>& miniGames, uint32_t nb_games)
{
    for (int i = 0; i < nb_games; i++)
    {
        auto& currentMiniGame = miniGames.at(i);

        std::cin >> currentMiniGame.gpu
                >> currentMiniGame.reg_0
                >> currentMiniGame.reg_1
                >> currentMiniGame.reg_2
                >> currentMiniGame.reg_3
                >> currentMiniGame.reg_4
                >> currentMiniGame.reg_5
                >> currentMiniGame.reg_6; 
        std::cin.ignore();
    }
}

constexpr uint32_t GAME_TYPE_UNKNOWN = 0;
constexpr uint32_t GAME_TYPE_RUNNING = 1;
constexpr uint32_t GAME_TYPE_SHOOTING = 2;
constexpr uint32_t GAME_TYPE_CYCLING = 3;
constexpr uint32_t GAME_TYPE_DIVING = 4;

uint32_t GetGameType(std::string gpu)
{
    if ( std::regex_match(gpu, std::regex("^[URLD]+$")))
    {
        if (gpu.size() == 4)
            return GAME_TYPE_CYCLING;
        return GAME_TYPE_DIVING;
    }

    if (std::regex_match(gpu, std::regex("^[0-9]+$")))
        return GAME_TYPE_SHOOTING;

    if (gpu.size() == 30 &&  std::regex_match(gpu, std::regex("^[.#]+$")))
        return GAME_TYPE_RUNNING;    

    return GAME_TYPE_UNKNOWN;
}

std::tuple<std::string, double> GetDirectionForRunning(std::vector<MiniGame>& miniGames, uint32_t player_idx, uint32_t nb_games)
{
    auto GetPlayerPosition = [](uint32_t playerIndex, MiniGame& miniGame) {
        if (playerIndex == 0)
            return miniGame.reg_0;
        if (playerIndex == 1)
            return miniGame.reg_1;
        return miniGame.reg_2;
    };

    auto GetPlayerStuntCount = [](uint32_t playerIndex, MiniGame& miniGame) {
        if (playerIndex == 0)
            return miniGame.reg_3;
        if (playerIndex == 1)
            return miniGame.reg_4;
        return miniGame.reg_5;
    };

    auto DistanceToNextHedge = [](MiniGame& miniGame, int32_t playerPosition) {
        int32_t foundPosition = miniGame.gpu.find('#', playerPosition);
        if (foundPosition == std::string::npos)
            return std::numeric_limits<double>::max();

        if (playerPosition == -1)
            return (double) foundPosition;

        return (double) (foundPosition - playerPosition - 1);
    };

    double minDistance = std::numeric_limits<double>::max();
    for (uint32_t i = 0; i < nb_games; i++)
    {
        auto& currentGame = miniGames.at(i);

        if (GetGameType(currentGame.gpu) != GAME_TYPE_RUNNING)
            continue;

        int32_t playerPosition = GetPlayerPosition(player_idx, currentGame);
        int32_t playerStuntCount = GetPlayerStuntCount(player_idx, currentGame);
        
        if (playerStuntCount > 0)
            continue;

        double distance = DistanceToNextHedge(currentGame, playerPosition);
        if (distance >= 0 && distance < minDistance)
            minDistance = distance;
    }

    std::string                 minDirection = "UP";
    if (minDistance >= 3)       minDirection = "RIGHT";
    else if (minDistance >= 2)  minDirection = "DOWN";
    else if (minDistance >= 1)  minDirection = "LEFT";

    return std::tuple(minDirection, minDistance / 30.0);
}

std::tuple<std::string, double> GetDirectionForShooting(std::vector<MiniGame>& miniGames, uint32_t player_idx, uint32_t nb_games)
{
    auto GetPlayerPosition = [](uint32_t playerIndex, MiniGame& miniGame) {
        if (playerIndex == 0)
            return std::tuple(miniGame.reg_0, miniGame.reg_1);
        if (playerIndex == 1)
            return std::tuple(miniGame.reg_2, miniGame.reg_3);
        return std::tuple(miniGame.reg_4, miniGame.reg_5);
    };

    auto CalculateDistance = [](int x1, int y1, int x2, int y2) {
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    };

    double minDistance = std::numeric_limits<double>::max();
    std::string minDirection = "UP";
    for (uint32_t i = 0; i < nb_games; i++)
    {
        auto& currentGame = miniGames.at(i);

        if (GetGameType(currentGame.gpu) != GAME_TYPE_SHOOTING)
            continue;

        uint32_t windPower = currentGame.gpu[0] - '0';
        auto [x, y] = GetPlayerPosition(player_idx, currentGame);

        double distanceN = CalculateDistance(x, y + windPower, 0, 0); // Nord
        double distanceS = CalculateDistance(x, y - windPower, 0, 0); // Sud
        double distanceE = CalculateDistance(x + windPower, y, 0, 0); // Est
        double distanceW = CalculateDistance(x - windPower, y, 0, 0); // Ouest
        double localMinDistance = std::min({distanceN, distanceS, distanceE, distanceW});

        if (localMinDistance < minDistance)
        {
            minDistance = localMinDistance;
            if (localMinDistance == distanceN) {
                minDirection = "UP";
            } else if (localMinDistance == distanceS) {
                minDirection = "DOWN";
            } else if (localMinDistance == distanceE) {
                minDirection = "RIGHT";
            } else if (localMinDistance == distanceW) {
                minDirection = "LEFT";
            }
        }
    }

    return std::tuple(minDirection, minDistance / 20.0);
}

int main()
{
    uint32_t player_idx = ParseInteger();
    uint32_t nb_games = ParseInteger();

    std::vector<Player> players(MAXIMUM_PLAYER_COUNT);
    std::vector<MiniGame> miniGames(nb_games);

    for (auto& player : players)
        player.scores.resize(nb_games);

    // game loop (one loop per game round)
    while (true)
    {
        ParsePlayers(players, nb_games);
        ParseMiniGames(miniGames, nb_games);
        
        auto [runningChoice, runningDistance] = GetDirectionForRunning(miniGames, player_idx, nb_games);
        auto [shootingChoice, shootingDistance] = GetDirectionForShooting(miniGames, player_idx, nb_games);

        std::string bestChoice;
        double minDistance = std::min(runningDistance, shootingDistance);

        if (minDistance == runningDistance) {
            bestChoice = runningChoice;
        } else {
            bestChoice = shootingChoice;
        }

        std::cout << bestChoice << std::endl;
    }
}
