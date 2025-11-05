#include <iostream>
#include "tim.h"
#include "quick.h"
#include "soccerPlayer.h"
#include "csv.hpp"

#ifdef RGB
#  undef RGB
#endif

#include "parse_csv.h"
#include "aka_goat.h"
#include "osmanip/progressbar/progress_bar.hpp"
#include "osmanip/utility/options.hpp"
#include <chrono>

#include "opencv2/opencv.hpp"
#include "cpr/cpr.h"

int print_options()
{
    int selection = 0;

    while (selection == 0)
    {
        std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;
        std::cout << "Pick an attirbute to sort by" << ENDL << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "1. " << osm::feat( osm::rst, "color" ) << "Dominance Score" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "2. " << osm::feat( osm::rst, "color" ) << "Total Goals" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "3. " << osm::feat( osm::rst, "color" ) << "Total Assista" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "4. " << osm::feat( osm::rst, "color" ) << "Total Minutes Played" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "5. " << osm::feat( osm::rst, "color" ) << "Total Yellow Cards" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "6. " << osm::feat( osm::rst, "color" ) << "Total Red Cards" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "7. " << osm::feat( osm::rst, "color" ) << "Total Clean Sheets" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "8. " << osm::feat( osm::rst, "color" ) << "National Team Goals" << ENDL;
        std::cout << osm::feat( osm::col, "green" ) << "9. " << osm::feat( osm::rst, "color" ) << "National Team Games Played" << ENDL;
        std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;

        std::cout << "Selection (1 - 9): ";
        if(!(std::cin >> selection))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << ENDL << osm::feat( osm::col, "red" ) << "Error: please select a value in the range (1 - 9)" << osm::feat( osm::rst, "color" ) << ENDL << ENDL;
            continue;
        }

        if (selection < 1 || selection > 9)
        {
            std::cout << ENDL << osm::feat( osm::col, "red" ) << "Error: please select a value in the range (1 - 9)" << osm::feat( osm::rst, "color" ) << ENDL << ENDL;
            selection = 0;
        }
    }

    return selection;
}

compare_func get_compare_function(int selection)
{
    switch (selection)
    {
    case 1:
        return compare_dominanceScore;
        break;

    case 2:
        return compare_totalGoals;
        break;

    case 3:
        return compare_totalAssists;
        break;

    case 4:
        return compare_totalMinPlayed;
        break;

    case 5:
        return compare_totalYellowCards;
        break;

    case 6:
        return compare_totalRedCards;
        break;

    case 7:
        return compare_totalCleanSheets;
        break;

    case 8:
        return compare_nationalTeamGoals;
        break;

    case 9:
        return compare_nationalTeamGames;
        break;
    
    default:
        return nullptr;
        break;
    }
}

void run()
{
    std::vector<SoccerPlayer> players_vector;
    parse_csvs(players_vector);
    
    std::cout << "Creating Copies for Sorting" << ENDL;

    // create a copy of the vector
    std::vector<SoccerPlayer> tim_sorted_list = players_vector;
    std::vector<SoccerPlayer> merge_sorted_list = players_vector;
    std::vector<SoccerPlayer> quick_sorted_list = players_vector;

    // Load image
    // cv::Mat img = get_image_data("https://img.a.transfermarkt.technology/portrait/header/default.jpg", TIMEOUT);

    // print_image_data(img);

    // Display Welcome Screen

    std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;
    std::cout << "Welcome to AKA GOAT" << ENDL;
    std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;

    // Display Sorting options

    int selection = print_options();

    // Display Sorting Time

    // Tim sort
    std::cout << "Running Tim Sort" << ENDL;

    auto tim_start = std::chrono::high_resolution_clock::now();
    timSort(tim_sorted_list, get_compare_function(selection));
    auto tim_end = std::chrono::high_resolution_clock::now();

    // Quick sort
    std::cout << "Running Quick Sort" << ENDL;

    auto quick_start = std::chrono::high_resolution_clock::now();
    quickSort(quick_sorted_list, 0, quick_sorted_list.size() - 1, get_compare_function(selection), LESS_THAN);
    auto quick_end = std::chrono::high_resolution_clock::now();

    // Merge sort
    std::cout << "Running Merge Sort" << ENDL;

    auto merge_start = std::chrono::high_resolution_clock::now();
    mergeSort(merge_sorted_list, 0, merge_sorted_list.size() - 1, get_compare_function(selection));
    auto merge_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> tim_elapsed = tim_end - tim_start;
    std::chrono::duration<double> quick_elapsed = quick_end - quick_start;
    std::chrono::duration<double> merge_elapsed = merge_end - merge_start;

    std::cout << "Elapsed time Tim Sort: " << osm::feat( osm::col, "green" ) << tim_elapsed.count() << osm::feat( osm::rst, "color" ) << " seconds\n";
    std::cout << "Elapsed time Quick Sort: " << osm::feat( osm::col, "green" ) << quick_elapsed.count() << osm::feat( osm::rst, "color" ) << " seconds\n";
    std::cout << "Elapsed time Merge Sort: " << osm::feat( osm::col, "green" ) << merge_elapsed.count() << osm::feat( osm::rst, "color" ) << " seconds\n";

    std::cout << tim_sorted_list.at(tim_sorted_list.size() - 1).name << "; Dominance Score: " << tim_sorted_list.at(tim_sorted_list.size() - 1).dominanceScore << std::endl;
    std::cout << tim_sorted_list.at(tim_sorted_list.size() - 2).name << "; Dominance Score: " << tim_sorted_list.at(tim_sorted_list.size() - 2).dominanceScore << std::endl;
    std::cout << tim_sorted_list.at(tim_sorted_list.size() - 3).name << "; Dominance Score: " << tim_sorted_list.at(tim_sorted_list.size() - 3).dominanceScore << std::endl;
    

    // Display GOAT on the left, with name, stats, and a picture

    // Display other 9 on the right
}

