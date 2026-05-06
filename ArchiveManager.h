#ifndef ARCHIVEMANAGER_H
#define ARCHIVEMANAGER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class ArchiveManager {
public:
    static void writeCSV(const string& sport, const string& team1, int score1, const string& team2, int score2, const string& remark = "") {
        ofstream file("scores.csv", ios::app);
        if (file.is_open()) {
            file << sport << "," << team1 << "," << score1 << "," << team2 << "," << score2 << "," << remark << endl;
            file.close();
        } else {
            cerr << "Unable to open scores.csv for writing" << endl;
        }
    }

    static string readHistory() {
        ifstream file("scores.csv");
        string line;
        string json = "[";
        bool first = true;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back(); // Handle potential CR
                if (line.empty()) continue;

                // Simple CSV parsing
                // Format: Sport,Team1,Score1,Team2,Score2,Remark
                stringstream ss(line);
                string segment;
                vector<string> seglist;
                while(getline(ss, segment, ',')) {
                   seglist.push_back(segment);
                }
                
                if (seglist.size() >= 5) {
                    if (!first) json += ",";
                    
                    json += "{";
                    json += "\"sport\": \"" + seglist[0] + "\",";
                    json += "\"team1\": \"" + seglist[1] + "\",";
                    json += "\"score1\": " + seglist[2] + ",";
                    json += "\"team2\": \"" + seglist[3] + "\",";
                    json += "\"score2\": " + seglist[4];
                    if (seglist.size() > 5) {
                         json += ",\"remark\": \"" + seglist[5] + "\"";
                    }
                    json += "}";
                    first = false;
                }
            }
            file.close();
        }
        json += "]";
        return json;
    }
};

#endif
