#ifndef HASHMAP_H
#define HASPMAP_H

#include <string>
#include <vector>
#include <functional>

struct SoccerPlayer {
    std::string playerId;
    std::string name;
    std::string nationality;
    std::string position;
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

class HashMap {
    private:
    struct HashNode{
        std::string key;
        SoccerPlayer val;
        HashNode* next;
        HashNode(const std::string& k, const SoccerPlayer& v) {
            key = k;
            val = v;
            next = nullptr;
        }  
    };

    std::vector<HashNode*> table;
    const int tableSize = 100000;

    const int hash(const std::string& key) {
        std::hash<std::string> hasher;
        return static_cast<int>(hasher(key) % tableSize);
    }

    public:
    HashMap() {
        table.resize(tableSize);
        for (int i = 0; i < tableSize; i++){
            table[i] = nullptr;
        }
    }

    void insert(const std::string& playerId, const SoccerPlayer& player) {
        int index = hash(playerId);
        HashNode* current = table[index];
    }

};

#endif