#ifndef BADMINTON_H
#define BADMINTON_H

#include "Sport.h"
#include <sstream>

class Badminton : public Sport {
public:
    Badminton(string t1, string t2) : Sport(t1, t2) {}

    string getName() const override { return "Badminton"; }

    void updateScore(string team, int points) override {
        if (!winnerName.empty()) return; // Game already over

        if (team == team1Name) {
            team1Score += points;
        } else {
            team2Score += points;
        }

        // Check for win condition: 21 points and lead by 2
        if (team1Score >= 21) {
            if (team1Score >= team2Score + 2) winnerName = team1Name;
            else if (team1Score == 30) winnerName = team1Name; // Max points cap
        } else if (team2Score >= 21) {
            if (team2Score >= team1Score + 2) winnerName = team2Name;
            else if (team2Score == 30) winnerName = team2Name;
        }
    }

    string getJson() const override {
        stringstream ss;
        ss << "{";
        ss << "\"sport\": \"Badminton\",";
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
