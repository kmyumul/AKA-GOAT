#include <iostream>
#include <windows.h>
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
        for (int i = 1; i < 10; i++)
        {
            std::cout << osm::feat( osm::col, "green" ) << i << ". " << osm::feat( osm::rst, "color" ) << get_string_selection(i) << ENDL;
        }
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

void run_sorting(std::vector<SoccerPlayer> &tim_vec, std::vector<SoccerPlayer> &quick_vec, std::vector<SoccerPlayer> &merge_vec, int selection)
{
    std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;
    std::cout << "Sorting ..." << ENDL << ENDL;

    // Tim sort
    std::cout << "Running " << osm::feat( osm::col, "green" ) << "Tim Sort" << osm::feat( osm::rst, "color" ) << ENDL;

    auto tim_start = std::chrono::high_resolution_clock::now();
    timSort(tim_vec, get_compare_function(selection));
    auto tim_end = std::chrono::high_resolution_clock::now();

    auto quick_start = std::chrono::high_resolution_clock::now();
    if (selection == 1)
    {
        //Quick sort
        std::cout << "Running " << osm::feat( osm::col, "green" ) << "Quick Sort" << osm::feat( osm::rst, "color" ) << ENDL;

        quickSort(quick_vec, 0, quick_vec.size() - 1, get_compare_function(selection), LESS_THAN);
    }
    auto quick_end = std::chrono::high_resolution_clock::now();


    // Merge sort
    std::cout << "Running " << osm::feat( osm::col, "green" ) << "Merge Sort" << osm::feat( osm::rst, "color" ) << ENDL << ENDL;

    auto merge_start = std::chrono::high_resolution_clock::now();
    mergeSort(merge_vec, 0, merge_vec.size() - 1, get_compare_function(selection));
    auto merge_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> tim_elapsed = tim_end - tim_start;
    std::chrono::duration<double> quick_elapsed = quick_end - quick_start;
    std::chrono::duration<double> merge_elapsed = merge_end - merge_start;

    std::cout << "Elapsed time Tim Sort: " << osm::feat( osm::col, "green" ) << tim_elapsed.count() << osm::feat( osm::rst, "color" ) << " seconds\n";
    if (selection == 1)
    {
        std::cout << "Elapsed time Quick Sort: " << osm::feat( osm::col, "green" ) << quick_elapsed.count() << osm::feat( osm::rst, "color" ) << " seconds\n";
    }
    std::cout << "Elapsed time Merge Sort: " << osm::feat( osm::col, "green" ) << merge_elapsed.count() << osm::feat( osm::rst, "color" ) << " seconds\n";

    std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;
}

std::string get_string_selection(int selection)
{
    switch (selection)
    {
    case 1:
        return "Dominance Score";
        break;

    case 2:
        return "Total Goals";
        break;

    case 3:
        return "Total Assists";
        break;

    case 4:
        return "Total Minutes Played";
        break;

    case 5:
        return "Total Yellow Cards";
        break;

    case 6:
        return "Total Red Cards";
        break;

    case 7:
        return "Total Clean Sheets";
        break;

    case 8:
        return "National Team Goals";
        break;

    case 9:
        return "National Team Games Played";
        break;
    
    default:
        return "";
        break;
    }
}

int get_attribute(SoccerPlayer player, int selection)
{
    switch (selection)
    {
    case 1:
        return (int)player.dominanceScore;
        break;

    case 2:
        return player.totalGoals;
        break;

    case 3:
        return player.totalAssists;
        break;

    case 4:
        return player.totalMinPlayed;
        break;

    case 5:
        return player.totalYellowCards;
        break;

    case 6:
        return player.totalRedCards;
        break;

    case 7:
        return player.totalCleanSheets;
        break;

    case 8:
        return player.nationalTeamGoals;
        break;

    case 9:
        return player.nationalTeamGames;
        break;
    
    default:
        return 0;
        break;
    }
}

std::string set_cursor_position(int row, int col)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int termRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int termCols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int targetRow = termRows - row;

    return "\033[" + std::to_string(targetRow) + ";" + std::to_string(col) + "H";
    
}

void run()
{
    std::vector<SoccerPlayer> players_vector;
    parse_csvs(players_vector);
    
    std::cout << "Creating Copies for Sorting" << ENDL;

    // create a copy of the vectors
    std::vector<SoccerPlayer> tim_sorted_list = players_vector;
    std::vector<SoccerPlayer> merge_sorted_list = players_vector;
    std::vector<SoccerPlayer> quick_sorted_list = players_vector;

    // Display Welcome Screen

    std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;
    std::cout << "Welcome to AKA GOAT" << ENDL;
    std::cout << osm::feat( osm::col, "yellow" ) << BREAK << osm::feat( osm::rst, "color" ) << ENDL;

    // Display Sorting options

    while (1)
    {
        int selection = print_options();

        // Display Sorting Time

        run_sorting(tim_sorted_list, quick_sorted_list, merge_sorted_list, selection);

        // Display stats

        std::string string_selection = get_string_selection(selection);

        std::cout << ENDL;

        std::cout << set_cursor_position(1, 80);
        std::cout << osm::feat( osm::col, "yellow" ) << "TOP 10" << osm::feat( osm::rst, "color" ) << ENDL << ENDL << ENDL;

        for (int i = 0; i < 10; i++)
        {
            SoccerPlayer player = tim_sorted_list.at(tim_sorted_list.size() - (i+1));
            std::string padded_string;
            int spaces = (30 - player.name.length());
            if (spaces > 0)
            {
                padded_string = player.name + std::string(spaces, ' ');
            }
            std::cout << set_cursor_position(1, 80);
            std::string num_string = std::to_string(i + 1) + ". ";
            std::cout << std::left << std::setw(4) << num_string << osm::feat( osm::col, "yellow" ) << padded_string << osm::feat( osm::rst, "color" ) << ": " << string_selection << ": " << osm::feat( osm::col, "green" ) << get_attribute(player, selection) << osm::feat( osm::rst, "color" ) << ENDL << ENDL;
        }

        // Display GOAT

        std::cout << set_cursor_position(13, 0);
        std::cout << osm::feat( osm::col, "green" ) << "GOAT: " << osm::feat( osm::rst, "color" );

        SoccerPlayer player = tim_sorted_list.at(tim_sorted_list.size() - 1);

        std::cout << osm::feat( osm::col, "yellow" ) << player.name << osm::feat( osm::rst, "color" ) << ": " << string_selection << ": " << osm::feat( osm::col, "green" ) << get_attribute(player, selection) << osm::feat( osm::rst, "color" );
        
        cv::Mat img = get_image_data(player.image, TIMEOUT);

        std::cout << set_cursor_position(11, 0);

        print_image_data(img);

        std::cout << set_cursor_position(0, 0);

        std::cout << ENDL;
        int restart = -1;

        while (1)
        {
            std::cout << "Would you like to run again? 0 = Y, 1 = N? ";
            if(!(std::cin >> restart))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << ENDL << osm::feat( osm::col, "red" ) << "Error: please select a value in the range (0 - 1)" << osm::feat( osm::rst, "color" ) << ENDL << ENDL;
                continue;

            }

            if (restart < 0 || restart > 1)
            {
                std::cout << ENDL << osm::feat( osm::col, "red" ) << "Error: please select a value in the range (0 - 1)" << osm::feat( osm::rst, "color" ) << ENDL << ENDL;
                selection = 0;
                continue;
            }
            break;
        }

        if (restart == 1)
        {
            break;
        }

    }


}

