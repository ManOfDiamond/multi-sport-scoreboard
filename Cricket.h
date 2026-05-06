#ifndef CRICKET_H
#define CRICKET_H

#include "Sport.h"
#include <sstream>

class Cricket : public Sport {
    int team1Wickets;
    int team2Wickets;
    int battingTeam; // 1 or 2
    int currentInnings; // 1 or 2
    string tossWinner;
    string tossChoice;
    string resultDetail;

public:
    Cricket(string t1, string t2) : Sport(t1, t2), team1Wickets(0), team2Wickets(0), battingTeam(1), currentInnings(1), resultDetail("") {}
    
    // Configure toss and initial batting team
    void setToss(string winner, string choice) {
        tossWinner = winner;
        tossChoice = choice;
        // Determine who bats first
        if (winner == team1Name) {
            battingTeam = (choice == "Bat") ? 1 : 2;
        } else {
            battingTeam = (choice == "Bat") ? 2 : 1;
        }
    }

    string getName() const override { return "Cricket"; }
    
    void nextPhase() override {
        if (currentInnings == 1) {
            currentInnings = 2;
            battingTeam = (battingTeam == 1) ? 2 : 1;
        }
    }
    
    string getStatus() const override {
        stringstream ss;
        ss << "Innings " << currentInnings << ": " << (battingTeam == 1 ? team1Name : team2Name) << " Batting";
        if (currentInnings == 2) {
            int target = (battingTeam == 1 ? team2Score : team1Score) + 1;
            int current = (battingTeam == 1 ? team1Score : team2Score);
            ss << " (Target: " << target << ", Need " << (target - current) << ")";
        }
        return ss.str();
    }

    string getResultDetail() const override {
        return (resultDetail.empty() ? Sport::getResultDetail() : resultDetail);
    }
    
    void updateScore(string team, int points) override {
        if (!winnerName.empty()) return;
        
        // Strict batting team check
        if (team == team1Name && battingTeam != 1) return; 
        if (team == team2Name && battingTeam != 2) return;

        if (team == team1Name) {
            if (points == -1) team1Wickets++;
            else team1Score += points;
        } else {
            if (points == -1) team2Wickets++;
            else team2Score += points;
        }
        
        // Check for "All Out" in current innings
        int currentWickets = (battingTeam == 1) ? team1Wickets : team2Wickets;
        if (currentWickets >= 10 && currentInnings == 1) {
            nextPhase();
        } else if (currentWickets >= 10 && currentInnings == 2) {
             // Second batting team all out -> Bowling team wins
             winnerName = (battingTeam == 1) ? team2Name : team1Name;
             int firstInningsScore = (battingTeam == 1 ? team2Score : team1Score);
             int currentScore = (battingTeam == 1 ? team1Score : team2Score);
             stringstream r;
             r << winnerName << " won by " << (firstInningsScore - currentScore) << " runs";
             resultDetail = r.str();
        }
        
        // Check Score Chasing in 2nd Innings
        if (winnerName.empty() && currentInnings == 2) {
             int target = (battingTeam == 1 ? team2Score : team1Score) + 1;
             int current = (battingTeam == 1 ? team1Score : team2Score);
             if (current >= target) {
                 winnerName = (battingTeam == 1) ? team1Name : team2Name;
                 int wicketsLeft = 10 - ((battingTeam == 1) ? team1Wickets : team2Wickets);
                 stringstream r;
                 r << winnerName << " won by " << wicketsLeft << " wickets";
                 resultDetail = r.str();
             }
        }
    }

    string getJson() const override {
        stringstream ss;
        ss << "{";
        ss << "\"sport\": \"Cricket\",";
        ss << "\"team1\": \"" << team1Name << "\",";
        ss << "\"team2\": \"" << team2Name << "\",";
        ss << "\"score1\": " << team1Score << ",";
        ss << "\"score2\": " << team2Score << ",";
        ss << "\"wickets1\": " << team1Wickets << ",";
        ss << "\"wickets2\": " << team2Wickets << ",";
        ss << "\"winner\": \"" << winnerName << "\",";
        ss << "\"result\": \"" << resultDetail << "\",";
        ss << "\"abandoned\": " << (abandoned ? "true" : "false") << ",";
        ss << "\"status\": \"" << getStatus() << "\",";
        ss << "\"currentInnings\": " << currentInnings << ",";
        ss << "\"battingTeam\": " << battingTeam;
        ss << "}";
        return ss.str();
    }
};

#endif
