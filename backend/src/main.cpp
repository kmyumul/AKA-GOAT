#include <iostream>
#include "tim.h"
#include "quick.h"
#include "soccerPlayer.h"
#include <chrono>


#define ENDL '\n'


int main()
{
    std::vector<SoccerPlayer> list = generateRandomPlayers(1000000);

    std::vector<SoccerPlayer> tim_sorted_list = list;
    std::vector<SoccerPlayer> merge_sorted_list = list;
    std::vector<SoccerPlayer> insertion_sorted_list = list;
    std::vector<SoccerPlayer> quick_sorted_list = list;

    // TIM SORT
    auto start = std::chrono::high_resolution_clock::now();

    timSort(tim_sorted_list, compare_dominanceScore);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time Tim Sort: " << elapsed.count() << " seconds\n";
    std::cout << tim_sorted_list.at(0).name << "; Dominance Score: " << tim_sorted_list.at(0).dominanceScore << std::endl;
    std::cout << tim_sorted_list.at(1).name << "; Dominance Score: " << tim_sorted_list.at(1).dominanceScore << std::endl;
    std::cout << tim_sorted_list.at(2).name << "; Dominance Score: " << tim_sorted_list.at(2).dominanceScore << std::endl;

    // MERGE SORT
    start = std::chrono::high_resolution_clock::now();

    mergeSort(merge_sorted_list, 0, merge_sorted_list.size() - 1, compare_dominanceScore);

    end = std::chrono::high_resolution_clock::now();

    elapsed = end - start;
    std::cout << "Elapsed time Merge Sort: " << elapsed.count() << " seconds\n";
    std::cout << merge_sorted_list.at(0).name << "; Dominance Score: " << merge_sorted_list.at(0).dominanceScore << std::endl;
    std::cout << merge_sorted_list.at(1).name << "; Dominance Score: " << merge_sorted_list.at(1).dominanceScore << std::endl;
    std::cout << merge_sorted_list.at(2).name << "; Dominance Score: " << merge_sorted_list.at(2).dominanceScore << std::endl;

    // QUICK SORT

    start = std::chrono::high_resolution_clock::now();

    quickSort(quick_sorted_list, 0, quick_sorted_list.size() - 1, compare_dominanceScore, LESS_THAN);

    end = std::chrono::high_resolution_clock::now();

    elapsed = end - start;
    std::cout << "Elapsed time Quick Sort: " << elapsed.count() << " seconds\n";
    std::cout << quick_sorted_list.at(0).name << "; Dominance Score: " << quick_sorted_list.at(0).dominanceScore << std::endl;
    std::cout << quick_sorted_list.at(1).name << "; Dominance Score: " << quick_sorted_list.at(1).dominanceScore << std::endl;
    std::cout << quick_sorted_list.at(2).name << "; Dominance Score: " << quick_sorted_list.at(2).dominanceScore << std::endl;

    // INSERTION SORT
    // start = std::chrono::high_resolution_clock::now();

    // insertionSort(insertion_sorted_list, 0, insertion_sorted_list.size() - 1, compare_totalMinPlayed);

    // end = std::chrono::high_resolution_clock::now();

    // elapsed = end - start;
    // std::cout << "Elapsed time Insertion Sort: " << elapsed.count() << " seconds\n";

    // for (int i = 0; i < 400; i++)
    // {
    //     std::cout << merge_sorted_list.at(i).totalMinPlayed << ENDL;
    // }

    // for (int i = 0; i < 400; i++)
    // {
    //     std::cout << tim_sorted_list.at(i).totalMinPlayed << ENDL;
    // }

    // std::cout << ENDL << "TOP 10" << ENDL;

    // for (int i = 0; i < 10; i++)
    // {
    //     std::cout << list.at(list.size() - i - 1).totalGoals << ENDL;
    // }
    return 0;
}