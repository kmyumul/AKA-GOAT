#pragma once

#include <unordered_map>

#include "soccerPlayer.h"
#include "csv.hpp"
#include "parse_csv.h"
#include "opencv2/opencv.hpp"
#include "cpr/cpr.h"

#define DATASET_PATH "../extern/datasets/datalake/transfermarkt/"
#define ENDL '\n'

struct TermColor
{
    std::string name;
    std::string code;
    cv::Vec3b rgb;
};

std::string get_string_safe(const csv::CSVRow &row, const std::string &col);

int stoi_safe(const std::string &s);

void parse_csvs(std::vector<SoccerPlayer> &out_vector);

void init_player_profiles(std::unordered_map<std::string, SoccerPlayer> &players);

void init_performance_data(std::unordered_map<std::string, SoccerPlayer> &players);

void init_national_data(std::unordered_map<std::string, SoccerPlayer> &players);

void init_aggregate_data(std::unordered_map<std::string, SoccerPlayer> &players);

cv::Mat get_image_data(const std::string& url, int timeout_ms);

void print_image_data(cv::Mat &img);