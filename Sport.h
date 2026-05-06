#ifndef SPORT_H
#define SPORT_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Sport {
protected:
    string team1Name;
    string team2Name;
    int team1Score;
    int team2Score;
    string winnerName;
    bool abandoned;
    bool archived; 

public:
    Sport(string t1, string t2) : team1Name(t1), team2Name(t2), team1Score(0), team2Score(0), winnerName(""), abandoned(false), archived(false) {}
    virtual ~Sport() = default;

    virtual void updateScore(string team, int points) = 0;
    virtual string getJson() const = 0; // Return JSON representation
    virtual string getName() const = 0; // Return Sport Name
    virtual string getTeamName(int teamId) const { return (teamId == 1) ? team1Name : team2Name; }
    virtual int getScore(int teamId) const { return (teamId == 1) ? team1Score : team2Score; }
    virtual string getWinner() const { return winnerName; }
    virtual string getResultDetail() const { return "Completed"; }
    virtual void abandon() { abandoned = true; }
    virtual bool isAbandoned() const { return abandoned; }
    virtual void setArchived() { archived = true; }
    virtual bool isArchived() const { return archived; }
    virtual void nextPhase() {} // For Cricket innings, etc.
    virtual string getStatus() const { return ""; } // Additional status info

    // For console debugging
    virtual void displayScore() const {
        cout << team1Name << ": " << team1Score << " - " << team2Name << ": " << team2Score << endl;
    }
};

#endif
