#include <iostream>
#include "parse_csv.h"

std::string get_string_safe(const csv::CSVRow &row, const std::string &col)
{
    try
    {
        auto field = row[col];
        if (field.is_null()) return "";
        return field.get<>();
    } catch (...) {
        return "";
    }
}

int stoi_safe(const std::string &s)
{
    if (s.empty()) return 0;
    try { return std::stoi(s); } catch(...) { return 0; }
}

void parse_csvs(std::vector<SoccerPlayer> &out_vector)
{
    // hashmap for dataprocessing, gives us fast lookup
    std::unordered_map<std::string, SoccerPlayer> players;

    // process data
    init_player_profiles(players);
    init_performance_data(players);
    init_national_data(players);
    init_aggregate_data(players);

    // fill out vector
    std::cout << "Creating Lists for Sorting" << ENDL;
    
    out_vector.reserve(players.size());
    std::transform(players.begin(), players.end(),
                std::back_inserter(out_vector),
                [](const auto &p) {return p.second;});
}

// Create the inital player structs
void init_player_profiles(std::unordered_map<std::string, SoccerPlayer> &players)
{
    std::cout << "Initializing player profiles" << ENDL;
    try
    {
        csv::CSVReader reader(std::string(DATASET_PATH) + "player_profiles/player_profiles.csv");
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

            // get player image
            if (!row["player_image_url"].is_null()) sp.image = row["player_image_url"].get<>();

            players[player_id] = std::move(sp);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading profiles CSV: " << e.what() << "\n";
    }
}

// Fill in the general performance part of the struct
void init_performance_data(std::unordered_map<std::string, SoccerPlayer> &players)
{
    std::cout << "Filling player profiles with general performance data" << ENDL;

    try
    {
        csv::CSVReader statsReader(std::string(DATASET_PATH) + "player_performances/player_performances.csv");
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

            // get data
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
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading stats CSV: " << e.what() << "\n";
    }
}

// Fill in the national performance part of the struct
void init_national_data(std::unordered_map<std::string, SoccerPlayer> &players)
{
    std::cout << "Filling player profiles with national performance data" << ENDL;

    try
    {
        csv::CSVReader statsReader(std::string(DATASET_PATH) + "player_national_performances/player_national_performances.csv");
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

            // get data
            int matches = stoi_safe(get_string_safe(row, "matches"));
            int goals = stoi_safe(get_string_safe(row, "goals"));

            sp.nationalTeamGames += matches;
            sp.nationalTeamGoals += goals;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading stats CSV: " << e.what() << "\n";
    }
}

// Fill in aggregate values
void init_aggregate_data(std::unordered_map<std::string, SoccerPlayer> &players)
{
    std::cout << "Calculating GOAT Values" << ENDL;

    for (auto &kv : players)
    {
        SoccerPlayer &p = kv.second;
        p.ratioGoalGame = (p.totalGamesPlayed > 0) ? static_cast<float>(p.totalGoals) / p.totalGamesPlayed : 0.0f;
        p.dominanceScore = (p.totalGoals * 0.45f) + (p.totalAssists * 0.35f) + (p.totalCleanSheets * 0.05f) + (p.totalGamesPlayed/ 10.0f * 0.15f);
    }
}

// Get Image Data
cv::Mat get_image_data(const std::string& url, int timeout_ms)
{
    // Get a response from the link
    cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{timeout_ms});

    // Check for errors
    if (r.error)
    {
        return cv::Mat();
    }
    if (r.status_code != 200 || r.text.empty()) 
    {
        return cv::Mat();
    }

    // copy data into a vector
    std::vector<unsigned char> bytes(r.text.begin(), r.text.end());

    // convert vector into a cv::Mat
    cv::Mat dataMat(1, static_cast<int>(bytes.size()), CV_8UC1, bytes.data());
    cv::Mat img = cv::imdecode(dataMat, cv::IMREAD_COLOR);

    // return image
    return img;
}

// Prints image data
void print_image_data(cv::Mat &img)
{
    std::vector<TermColor> terminal_colors = {
        {"black", "\033[30m", {0, 0, 0}},
        {"red", "\033[31m", {0, 0, 255}},
        {"green", "\033[32m", {0, 255, 0}},
        {"orange", "\033[33m", {0, 165, 255}},
        {"blue", "\033[34m", {255, 0, 0}},
        {"purple", "\033[35m", {128, 0, 128}},
        {"cyan", "\033[36m", {255, 255, 0}},
        {"gray", "\033[37m", {192, 192, 192}},
        {"dk gray", "\033[90m", {128, 128, 128}},
        {"lt red", "\033[91m", {0, 128, 255}},
        {"lt green", "\033[92m", {144, 238, 144}},
        {"yellow", "\033[93m", {0, 255, 255}},
        {"lt blue", "\033[94m", {173, 216, 230}},
        {"lt purple", "\033[95m", {216, 191, 216}},
        {"lt cyan", "\033[96m", {224, 255, 255}},
        {"white", "\033[97m", {255, 255, 255}}
    };

    // Resize image to max 128x128 while keeping aspect ratio
    int maxDim = 32;
    int width = img.cols;
    int height = img.rows;
    float scale = std::min((float)maxDim / width, (float)maxDim / height);
    cv::resize(img, img, cv::Size(width * scale, height * scale));

    // Print image using colors
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            cv::Vec3b px = img.at<cv::Vec3b>(y, x);
            // Find nearest color
            TermColor* best = nullptr;
            int bestDist = 256*256*3;
            for (auto &c : terminal_colors)
            {
                int db = px[0] - c.rgb[0];
                int dg = px[1] - c.rgb[1];
                int dr = px[2] - c.rgb[2];
                int dist = db*db + dg*dg + dr*dr;
                if (dist < bestDist)
                {
                    bestDist = dist;
                    best = &c;
                }
            }
            std::cout << best->code << "█";
        }
        // Reset color at end of line
        std::cout << "\033[0m" << std::endl;
    }
}