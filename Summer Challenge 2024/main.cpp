#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h>

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

int32_t DistanceToNextHedge(MiniGame& miniGame, int32_t playerPosition)
{
	int32_t foundPosition = miniGame.gpu.find('#', playerPosition);
	if (foundPosition == std::string::npos)
		return INT32_MAX;

	if (playerPosition == -1)
		return foundPosition;

	return foundPosition - playerPosition - 1;
}

std::string ChooseDirection(int32_t minDistance)
{
	if (minDistance >= 3)
		return "RIGHT";

	if (minDistance >= 2)
		return "DOWN";

	if (minDistance >= 1)
		return "LEFT";

	return "UP";
}

int32_t GetPlayerPosition(uint32_t playerIndex, MiniGame& miniGame)
{
	if (playerIndex == 0)
		return miniGame.reg_0;
	if (playerIndex == 1)
		return miniGame.reg_1;
	return miniGame.reg_2;
}

int32_t GetPlayerStuntCount(uint32_t playerIndex, MiniGame& miniGame)
{
	if (playerIndex == 0)
		return miniGame.reg_3;
	if (playerIndex == 1)
		return miniGame.reg_4;
	return miniGame.reg_5;
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

		auto& currentPlayer = players.at(player_idx);

		int32_t minDistance = INT32_MAX;
		for (uint32_t i = 0; i < nb_games; i++)
		{
			auto& currentGame = miniGames.at(i);

			int32_t playerPosition = GetPlayerPosition(player_idx, currentGame);
			int32_t playerStuntCount = GetPlayerStuntCount(player_idx, currentGame);

			if (playerStuntCount > 0)
				continue;

			int32_t distance = DistanceToNextHedge(currentGame, playerPosition);
			if (distance >= 0 && distance < minDistance)
				minDistance = distance;
		}

		std::cout <<  ChooseDirection(minDistance) << std::endl;
	}
}
