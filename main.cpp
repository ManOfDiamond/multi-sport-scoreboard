#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "ScoreboardServer.h"

// Note: 'httplib.h': https://github.com/yhirose/cpp-httplib

using namespace std;

void openBrowser(const string& url) {
    string command;
    #ifdef _WIN32
        command = "start " + url;
    #elif __APPLE__
        command = "open " + url;
    #else
        command = "xdg-open " + url;
    #endif
    system(command.c_str());
}

int main() {
    try {
        ScoreboardServer server;
        
        // Launch browser in a separate thread after a short delay
        thread t([]() {
            this_thread::sleep_for(chrono::seconds(1));
            openBrowser("http://localhost:8080");
        });
        t.detach();

        server.start();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
