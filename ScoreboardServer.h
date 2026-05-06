#ifndef SCOREBOARDSERVER_H
#define SCOREBOARDSERVER_H

#include "httplib.h"
#include "Sport.h"
#include "Cricket.h"
#include "Football.h"
#include "Basketball.h"
#include "Badminton.h"
#include "ArchiveManager.h"
#include <memory>
#include <map>
#include <sstream>

using namespace std;

class ScoreboardServer {
    httplib::Server svr;
    unique_ptr<Sport> currentSport;

public:
    ScoreboardServer() : currentSport(nullptr) {
        setupRoutes();
    }

    void start() {
        cout << "Server started at http://localhost:8080" << endl;
        svr.listen("0.0.0.0", 8080);
    }

private:
    void setupRoutes() {
        // Serve static files
        svr.set_mount_point("/", "./public");
        
        // Serve index.html as root
        svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
            ifstream file("index.html");
            if (file) {
                stringstream buffer;
                buffer << file.rdbuf();
                res.set_content(buffer.str(), "text/html");
            } else {
                res.set_content("<h1>Scoreboard Frontend Not Found</h1>", "text/html");
            }
        });

        svr.Get("/scores", [this](const httplib::Request&, httplib::Response& res) {
            if (currentSport) {
                res.set_content(currentSport->getJson(), "application/json");
            } else {
                res.set_content("{}", "application/json");
            }
        });

        svr.Get("/abandon", [this](const httplib::Request&, httplib::Response& res) {
            if (currentSport && !currentSport->isAbandoned() && currentSport->getWinner().empty()) {
                currentSport->abandon();
                if (!currentSport->isArchived()) {
                    ArchiveManager::writeCSV(
                        currentSport->getName(),
                        currentSport->getTeamName(1), currentSport->getScore(1),
                        currentSport->getTeamName(2), currentSport->getScore(2),
                        "Abandoned"
                    );
                    currentSport->setArchived();
                }
                res.set_content("{\"status\":\"abandoned\"}", "application/json");
            } else {
                res.set_content("{\"status\":\"error\", \"message\":\"No active game or already ended\"}", "application/json");
            }
        });

        svr.Get("/history", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(ArchiveManager::readHistory(), "application/json");
        });

        svr.Post("/start", [this](const httplib::Request& req, httplib::Response& res) {
            // Using query parameters or body parameters via httplib helper
            string sport = req.get_param_value("sport");
            string t1 = req.get_param_value("team1");
            string t2 = req.get_param_value("team2");
            string tossWin = req.get_param_value("tossWin");
            string choice = req.get_param_value("choice");
            
            if (currentSport) {
                // Archive previous game if not already archived
                if (!currentSport->isArchived()) {
                     string result = currentSport->getWinner().empty() ? "Interrupted" : currentSport->getResultDetail();
                     // For Cricket, we might want to store more info, but the CSV format is fixed.
                     // The 6th column is 'remark'. "Completed" was there. Now we put resultDetail.
                     ArchiveManager::writeCSV(
                         currentSport->getName(), 
                         currentSport->getTeamName(1), currentSport->getScore(1), 
                         currentSport->getTeamName(2), currentSport->getScore(2),
                         result
                     );
                     currentSport->setArchived();
                }
            }

            if (sport == "Cricket") {
                auto c = make_unique<Cricket>(t1, t2);
                c->setToss(tossWin, choice);
                currentSport = move(c);
            }
            else if (sport == "Football") currentSport = make_unique<Football>(t1, t2);
            else if (sport == "Basketball") currentSport = make_unique<Basketball>(t1, t2);
            else if (sport == "Badminton") currentSport = make_unique<Badminton>(t1, t2);
            else {
                res.status = 400;
                res.set_content("Invalid Sport", "text/plain");
                return;
            }
            res.set_content("Game Started", "text/plain");
        });
        
        // Endpoint for Finish Innings (Next Phase)
        svr.Post("/nextphase", [this](const httplib::Request&, httplib::Response& res) {
            if (currentSport && currentSport->getName() == "Cricket" && currentSport->getWinner().empty() && !currentSport->isAbandoned()) {
                // We assume Cricket because only Cricket uses phases currently
                // Ideally use dynamic_cast but unique_ptr<Sport> needs RTTI and we have it.
                // But let's just create nextPhase in base class
                string status = currentSport->getStatus(); // Check if innings 1
                currentSport->nextPhase();
                res.set_content("{\"status\":\"ok\"}", "application/json");
            } else {
                res.set_content("{\"status\":\"error\"}", "application/json");
            }
        });

        svr.Post("/update", [this](const httplib::Request& req, httplib::Response& res) {
            if (!currentSport) {
                res.status = 400;
                res.set_content("No active game", "text/plain");
                return;
            }
            string team = req.get_param_value("team");
            string pts = req.get_param_value("points");
            try {
                int points = stoi(pts);
                currentSport->updateScore(team, points);
                
                // Real-time archiving if game ends
                if (!currentSport->getWinner().empty() && !currentSport->isArchived()) {
                    ArchiveManager::writeCSV(
                        currentSport->getName(),
                        currentSport->getTeamName(1), currentSport->getScore(1),
                        currentSport->getTeamName(2), currentSport->getScore(2),
                        "Completed"
                    );
                    currentSport->setArchived();
                }
                
                res.set_content(currentSport->getJson(), "application/json");
            } catch (...) {
                res.status = 400;
                res.set_content("Invalid Input", "text/plain");
            }
        });
    }


    string getParam(const string& body, const string& key) {
        // Very basic parsing for url-encoded or JSON body
        // Assuming url-encoded: key=value&key2=value2
        size_t pos = body.find(key + "=");
        if (pos == string::npos) return "";
        pos += key.length() + 1;
        size_t end = body.find("&", pos);
        if (end == string::npos) end = body.length();
        string val = body.substr(pos, end - pos);
        // Decode URL encoding if necessary (simplified: replace + with space)
        for (auto& c : val) if(c == '+') c = ' ';
        return val; 
    }
};

#endif
