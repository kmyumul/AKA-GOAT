#pragma once
#include <string>
#include <vector>

enum op
{
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL
};

struct SoccerPlayer
{
    std::string playerId = "";
    std::string name = "";
    std::string nationality = "";
    std::string position = "";
    int totalGoals = 0;
    int totalAssists = 0;
    int totalMinPlayed = 0;
    int totalYellowCards = 0;
    int totalRedCards= 0;
    int totalCleanSheets = 0;
    int nationalTeamGoals = 0;
    int nationalTeamGames = 0;
    int totalGamesPlayed = 0;
    float ratioGoalGame = 0.0f;
    float dominanceScore = 0.0f;
};

std::vector<SoccerPlayer> generateRandomPlayers(int n);

bool compare_totalGoals(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_totalAssists(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_totalMinPlayed(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_totalYellowCards(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_totalRedCards(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_totalCleanSheets(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_nationalTeamGoals(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_nationalTeamGames(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_totalGamesPlayed(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_ratioGoalGame(SoccerPlayer& first, SoccerPlayer& second, op operation);

bool compare_dominanceScore(SoccerPlayer& first, SoccerPlayer& second, op operation);
