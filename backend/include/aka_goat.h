#pragma once

#include "soccerPlayer.h"

#define TIMEOUT 5000
#define BREAK "-------------------------------------------------------------------------------"

typedef bool (*compare_func)(SoccerPlayer&, SoccerPlayer&, op);

void run();
std::string get_string_selection(int selection);
void run_sorting(std::vector<SoccerPlayer> &tim_vec, std::vector<SoccerPlayer> &quick_vec, std::vector<SoccerPlayer> &merge_vec, int selection);
compare_func get_compare_function(int selection);
int print_options();
int get_attribute(SoccerPlayer player, int selection);
std::string set_cursor_position(int row, int col);