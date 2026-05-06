#ifndef FOOTBALL_H
#define FOOTBALL_H

#include "Sport.h"
#include <sstream>

class Football : public Sport {
public:
    Football(string t1, string t2) : Sport(t1, t2) {}

    string getName() const override { return "Football"; }

    void updateScore(string team, int points) override {
        if (!winnerName.empty()) return;

        if (team == team1Name) {
            team1Score += points;
        } else {
            team2Score += points;
        }

        // Win condition: First to 5 goals
        if (team1Score >= 5) winnerName = team1Name;
        else if (team2Score >= 5) winnerName = team2Name;
    }

    string getJson() const override {
        stringstream ss;
        ss << "{";
        ss << "\"sport\": \"Football\",";
        ss << "\"team1\": \"" << team1Name << "\",";
        ss << "\"team2\": \"" << team2Name << "\",";
        ss << "\"score1\": " << team1Score << ",";
        ss << "\"score2\": " << team2Score << ",";
        ss << "\"winner\": \"" << winnerName << "\",";
        ss << "\"abandoned\": " << (abandoned ? "true" : "false");
        ss << "}";
        return ss.str();
    }
};

#endif
