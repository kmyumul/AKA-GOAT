#include "soccerPlayer.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

std::vector<SoccerPlayer> generateRandomPlayers(int n)
{
    std::vector<std::string> names = {"Leo", "Cristiano", "Kylian", "Erling", "Neymar", "Kevin", "Luka", "Sergio", "Virgil", "Harry"};
    std::vector<std::string> nationalities = {"Argentina", "Portugal", "France", "Norway", "Brazil", "Belgium", "Croatia", "Spain", "Netherlands", "England"};
    std::vector<std::string> positions = {"Forward", "Midfielder", "Defender", "Goalkeeper"};

    std::vector<SoccerPlayer> players;
    players.reserve(n);

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < n; ++i)
    {
        SoccerPlayer p;
        p.playerId = "P" + std::to_string(1000 + rand() % 9000);
        p.name = names[rand() % names.size()];
        p.nationality = nationalities[rand() % nationalities.size()];
        p.position = positions[rand() % positions.size()];
        p.totalGoals = rand() % 50;
        p.totalAssists = rand() % 30;
        p.totalMinPlayed = 500 + rand() % 4000;
        p.totalYellowCards = rand() % 10;
        p.totalRedCards = rand() % 3;
        p.totalCleanSheets = rand() % 20;
        p.nationalTeamGoals = rand() % 15;
        p.nationalTeamGames = 1 + rand() % 40;
        p.totalGamesPlayed = 10 + rand() % 100;
        p.ratioGoalGame = (p.totalGamesPlayed > 0) ? static_cast<float>(p.totalGoals) / p.totalGamesPlayed : 0.0f;
        p.dominanceScore = p.totalGoals * 0.6f + p.totalAssists * 0.3f + p.totalCleanSheets * 0.1f;

        players.push_back(p);
    }

    return players; // unsorted by default
}

bool compare_totalGoals(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalGoals < second.totalGoals;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalGoals > second.totalGoals;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalGoals <= second.totalGoals;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalGoals >= second.totalGoals;
        break;
    default:
        break;
    }

    return false;
}

bool compare_totalAssists(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalAssists < second.totalAssists;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalAssists > second.totalAssists;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalAssists <= second.totalAssists;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalAssists >= second.totalAssists;
        break;
    default:
        break;
    }

    return false;
}

bool compare_totalMinPlayed(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalMinPlayed < second.totalMinPlayed;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalMinPlayed > second.totalMinPlayed;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalMinPlayed <= second.totalMinPlayed;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalMinPlayed >= second.totalMinPlayed;
        break;
    default:
        break;
    }

    return false;
}

bool compare_totalYellowCards(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalYellowCards < second.totalYellowCards;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalYellowCards > second.totalYellowCards;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalYellowCards <= second.totalYellowCards;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalYellowCards >= second.totalYellowCards;
        break;
    default:
        break;
    }

    return false;
}

bool compare_totalRedCards(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalRedCards < second.totalRedCards;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalRedCards > second.totalRedCards;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalRedCards <= second.totalRedCards;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalRedCards >= second.totalRedCards;
        break;
    default:
        break;
    }

    return false;
}

bool compare_totalCleanSheets(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalCleanSheets < second.totalCleanSheets;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalCleanSheets > second.totalCleanSheets;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalCleanSheets <= second.totalCleanSheets;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalCleanSheets >= second.totalCleanSheets;
        break;
    default:
        break;
    }

    return false;
}

bool compare_nationalTeamGoals(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.nationalTeamGoals < second.nationalTeamGoals;
        break;
    // greater than
    case GREATER_THAN:
        return first.nationalTeamGoals > second.nationalTeamGoals;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.nationalTeamGoals <= second.nationalTeamGoals;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.nationalTeamGoals >= second.nationalTeamGoals;
        break;
    default:
        break;
    }

    return false;
}

bool compare_nationalTeamGames(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.nationalTeamGames < second.nationalTeamGames;
        break;
    // greater than
    case GREATER_THAN:
        return first.nationalTeamGames > second.nationalTeamGames;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.nationalTeamGames <= second.nationalTeamGames;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.nationalTeamGames >= second.nationalTeamGames;
        break;
    default:
        break;
    }

    return false;
}

bool compare_totalGamesPlayed(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.totalGamesPlayed < second.totalGamesPlayed;
        break;
    // greater than
    case GREATER_THAN:
        return first.totalGamesPlayed > second.totalGamesPlayed;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.totalGamesPlayed <= second.totalGamesPlayed;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.totalGamesPlayed >= second.totalGamesPlayed;
        break;
    default:
        break;
    }

    return false;
}

bool compare_ratioGoalGame(SoccerPlayer& first, SoccerPlayer& second, op operation)
{
    switch (operation)
    {
    // less than
    case LESS_THAN:
        return first.ratioGoalGame < second.ratioGoalGame;
        break;
    // greater than
    case GREATER_THAN:
        return first.ratioGoalGame > second.ratioGoalGame;
        break;
    // less than or equal to
    case LESS_THAN_OR_EQUAL:
        return first.ratioGoalGame <= second.ratioGoalGame;
        break;
    // greater than or equal to
    case GREATER_THAN_OR_EQUAL:
        return first.ratioGoalGame >= second.ratioGoalGame;
        break;
    default:
        break;
    }

    return false;
}
