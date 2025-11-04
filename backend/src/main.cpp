#include <iostream>
#include "tim.h"
#include "quick.h"
#include "soccerPlayer.h"
#include "csv.hpp"
#include <unordered_map>
#include <chrono>


#define ENDL '\n'


// int main()
// {
//     std::vector<SoccerPlayer> list = generateRandomPlayers(1000000);

//     std::vector<SoccerPlayer> tim_sorted_list = list;
//     std::vector<SoccerPlayer> merge_sorted_list = list;
//     std::vector<SoccerPlayer> insertion_sorted_list = list;
//     std::vector<SoccerPlayer> quick_sorted_list = list;

//     // TIM SORT
//     auto start = std::chrono::high_resolution_clock::now();

//     timSort(tim_sorted_list, compare_dominanceScore);

//     auto end = std::chrono::high_resolution_clock::now();

//     std::chrono::duration<double> elapsed = end - start;
//     std::cout << "Elapsed time Tim Sort: " << elapsed.count() << " seconds\n";
//     std::cout << tim_sorted_list.at(0).name << "; Dominance Score: " << tim_sorted_list.at(0).dominanceScore << std::endl;
//     std::cout << tim_sorted_list.at(1).name << "; Dominance Score: " << tim_sorted_list.at(1).dominanceScore << std::endl;
//     std::cout << tim_sorted_list.at(2).name << "; Dominance Score: " << tim_sorted_list.at(2).dominanceScore << std::endl;

//     // MERGE SORT
//     start = std::chrono::high_resolution_clock::now();

//     mergeSort(merge_sorted_list, 0, merge_sorted_list.size() - 1, compare_dominanceScore);

//     end = std::chrono::high_resolution_clock::now();

//     elapsed = end - start;
//     std::cout << "Elapsed time Merge Sort: " << elapsed.count() << " seconds\n";
//     std::cout << merge_sorted_list.at(0).name << "; Dominance Score: " << merge_sorted_list.at(0).dominanceScore << std::endl;
//     std::cout << merge_sorted_list.at(1).name << "; Dominance Score: " << merge_sorted_list.at(1).dominanceScore << std::endl;
//     std::cout << merge_sorted_list.at(2).name << "; Dominance Score: " << merge_sorted_list.at(2).dominanceScore << std::endl;

//     // QUICK SORT

//     start = std::chrono::high_resolution_clock::now();

//     quickSort(quick_sorted_list, 0, quick_sorted_list.size() - 1, compare_dominanceScore, LESS_THAN);

//     end = std::chrono::high_resolution_clock::now();

//     elapsed = end - start;
//     std::cout << "Elapsed time Quick Sort: " << elapsed.count() << " seconds\n";
//     std::cout << quick_sorted_list.at(0).name << "; Dominance Score: " << quick_sorted_list.at(0).dominanceScore << std::endl;
//     std::cout << quick_sorted_list.at(1).name << "; Dominance Score: " << quick_sorted_list.at(1).dominanceScore << std::endl;
//     std::cout << quick_sorted_list.at(2).name << "; Dominance Score: " << quick_sorted_list.at(2).dominanceScore << std::endl;

//     // INSERTION SORT
//     // start = std::chrono::high_resolution_clock::now();

//     // insertionSort(insertion_sorted_list, 0, insertion_sorted_list.size() - 1, compare_totalMinPlayed);

//     // end = std::chrono::high_resolution_clock::now();

//     // elapsed = end - start;
//     // std::cout << "Elapsed time Insertion Sort: " << elapsed.count() << " seconds\n";

//     // for (int i = 0; i < 400; i++)
//     // {
//     //     std::cout << merge_sorted_list.at(i).totalMinPlayed << ENDL;
//     // }

//     // for (int i = 0; i < 400; i++)
//     // {
//     //     std::cout << tim_sorted_list.at(i).totalMinPlayed << ENDL;
//     // }

//     // std::cout << ENDL << "TOP 10" << ENDL;

//     // for (int i = 0; i < 10; i++)
//     // {
//     //     std::cout << list.at(list.size() - i - 1).totalGoals << ENDL;
//     // }
//     return 0;
// }

inline std::string get_string_safe(const csv::CSVRow &row, const std::string &col) {
    try {
        auto field = row[col];
        if (field.is_null()) return "";
        return field.get<>();
    } catch (...) {
        return "";
    }
}

static inline int stoi_safe(const std::string &s) {
    if (s.empty()) return 0;
    try { return std::stoi(s); } catch(...) { return 0; }
}

int main()
{
    // start

    std::cout << "Welcome to AKA_GOAT" << ENDL;

    std::cout << "Initializing player profiles" << ENDL;

    // For data processing, we use a hashmap for fast lookup
    std::unordered_map<std::string, SoccerPlayer> players;
    const std::string DATASET_PATH = "../extern/datasets/datalake/transfermarkt/";

    try {
        csv::CSVReader reader(DATASET_PATH + "player_profiles/player_profiles.csv");
        for (csv::CSVRow &row : reader) {

            // make sure there is a player id
            if (row["player_id"].is_null()) continue;

            // get the player id if it exists
            std::string player_id = row["player_id"].get<>();
            if (player_id.empty()) continue;

            SoccerPlayer sp;
            sp.playerId = player_id;

            // get a player name
            if (!row["player_name"].is_null()) sp.name = row["player_name"].get<>();
            else if (!row["player_slug"].is_null()) sp.name = row["player_slug"].get<>();

            // get a nationality
            if (!row["citizenship"].is_null()) sp.nationality = row["citizenship"].get<>();
            else if (!row["country_of_birth"].is_null()) sp.nationality = row["country_of_birth"].get<>();

            // get a position
            if (!row["position"].is_null()) sp.position = row["position"].get<>();
            else if (!row["main_position"].is_null()) sp.position = row["main_position"].get<>();

            players[player_id] = std::move(sp);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error reading profiles CSV: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Filling player profiles with general performance data" << ENDL;

    // Fill in the general performance part of the struct
    try {
        csv::CSVReader statsReader(DATASET_PATH + "player_performances/player_performances.csv");
        for (csv::CSVRow &row : statsReader) {
            if (row["player_id"].is_null()) continue;
            std::string pid = row["player_id"].get<>();
            if (pid.empty()) continue;

            // ensure player exists
            if (players.find(pid) == players.end()) {
                SoccerPlayer sp; sp.playerId = pid;
                players[pid] = std::move(sp);
            }
            SoccerPlayer &sp = players[pid];

            int goals = stoi_safe(get_string_safe(row, "goals"));
            int assists = stoi_safe(get_string_safe(row, "assists"));
            int minutes_played = stoi_safe(get_string_safe(row, "minutes_played"));
            int yellow_cards = stoi_safe(get_string_safe(row, "yellow_cards"));
            int second_yellow_cards = stoi_safe(get_string_safe(row, "second_yellow_cards"));
            int direct_red_cards = stoi_safe(get_string_safe(row, "direct_red_cards"));
            int clean_sheets = stoi_safe(get_string_safe(row, "clean_sheets"));
            int nb_on_pitch = stoi_safe(get_string_safe(row, "nb_on_pitch"));
            int subed_in = stoi_safe(get_string_safe(row, "subed_in"));
            int own_goals = stoi_safe(get_string_safe(row, "own_goals"));
            std::string team_name = get_string_safe(row, "team_name");

            sp.totalGoals += goals;
            sp.totalAssists += assists;
            sp.totalMinPlayed += minutes_played;
            sp.totalYellowCards += yellow_cards;
            sp.totalRedCards += (direct_red_cards + second_yellow_cards);
            sp.totalCleanSheets += clean_sheets;
            sp.totalGamesPlayed += (nb_on_pitch + subed_in);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error reading stats CSV: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Filling player profiles with national performance data" << ENDL;

    // Fill in the national performance part of the struct
    try {
        csv::CSVReader statsReader(DATASET_PATH + "player_national_performances/player_national_performances.csv");
        for (csv::CSVRow &row : statsReader) {
            if (row["player_id"].is_null()) continue;
            std::string pid = row["player_id"].get<>();
            if (pid.empty()) continue;

            // ensure player exists
            if (players.find(pid) == players.end()) {
                SoccerPlayer sp; sp.playerId = pid;
                players[pid] = std::move(sp);
            }
            SoccerPlayer &sp = players[pid];

            int matches = stoi_safe(get_string_safe(row, "matches"));
            int goals = stoi_safe(get_string_safe(row, "goals"));

            sp.nationalTeamGames += matches;
            sp.nationalTeamGoals += goals;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error reading stats CSV: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Calculating GOAT Values" << ENDL;

    // Fill in aggregate values
    for (auto &kv : players) {
        SoccerPlayer &p = kv.second;
        p.ratioGoalGame = (p.totalGamesPlayed > 0) ? static_cast<float>(p.totalGoals) / p.totalGamesPlayed : 0.0f;
        p.dominanceScore = (p.totalGoals * 0.45f) + (p.totalAssists * 0.35f) + (p.totalCleanSheets * 0.05f) + (p.totalGamesPlayed/ 10.0f * 0.15f);
    }

    std::cout << "Creating Lists for Sorting" << ENDL;

    std::vector<SoccerPlayer> players_vector;
    players_vector.reserve(players.size());

    std::transform(players.begin(), players.end(),
                std::back_inserter(players_vector),
                [](const auto &p) {return p.second;});

    std::cout << "Creating Copies for Sorting" << ENDL;

    // create a copy of the vector
    std::vector<SoccerPlayer> tim_sorted_list = players_vector;

    std::cout << "Sorting" << ENDL;

    // sort the list
    timSort(tim_sorted_list, compare_dominanceScore);

    std::cout << "Printing" << ENDL;

    // print top 10
    for (int i = 0; i < 10; i++)
    {
        std::cout << "NUMBER " << (10 - i) << ": " << tim_sorted_list.at(tim_sorted_list.size() - (10 - i)).name << " SCORE: " << tim_sorted_list.at(tim_sorted_list.size() - (10 - i)).dominanceScore << ENDL;
    }

}