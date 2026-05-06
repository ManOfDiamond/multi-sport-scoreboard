# Multi-Sport Scoreboard

A modular C++ scoreboard application with a web-based GUI and a lightweight HTTP API. The project provides sport-specific scoring logic, CSV persistence, and an embedded HTTP server so scores can be viewed remotely via a simple web UI.

**What changed**: Project moved to a C++ codebase (`main.cpp`) and added an HTTP server (`ScoreboardServer.h`, `httplib.h`) plus persistence and archiving utilities (`ArchiveManager.h`, `scores.csv`). The README below reflects the current repository layout and build/run instructions.

**Highlights**
- **Web UI / HTTP Server**: Embedded server implemented in `ScoreboardServer.h` using the single-file `httplib.h`. The server serves `index.html` and exposes current scores.
- **Persistence**: Scores are stored/loaded from [scores.csv](scores.csv) and historical data is managed by `ArchiveManager.h`.
- **Multi-Sport Modules**: Sport-specific logic is organized in header modules.

**Supported sports (modules present)**
- [Badminton.h](Badminton.h)
- [Basketball.h](Basketball.h)
- [Cricket.h](Cricket.h)
- [Football.h](Football.h)
- [Sport.h](Sport.h) (shared interfaces and helpers)

**Other notable files**
- [ArchiveManager.h](ArchiveManager.h) : Archiving and score persistence helper.
- [ScoreboardServer.h](ScoreboardServer.h) : HTTP server wrapper and endpoints.
- [httplib.h](httplib.h) : Embedded single-header HTTP library used by the server.
- [index.html](index.html) : Minimal web client served by the server.
- [scores.csv](scores.csv) : Persistent CSV store for current scores.
- [server_out.txt](server_out.txt) : Example/server log output captured from a run.

## Getting Started

### Prerequisites

- A C++ compiler (g++/MinGW on Windows is used in the provided tasks).

### Build (Windows / MinGW)

Use the provided VS Code task or run the following command in a terminal from the project root:

```powershell
"C:\Program Files\mingw64\bin\g++.exe" -g "main.cpp" -o "main.exe" -lws2_32 -D_WIN32_WINNT=0x0A00
```

Notes:
- The `-lws2_32` link flag is required on Windows for sockets.
- The `_WIN32_WINNT` macro enables modern Windows networking APIs when building with MinGW.

### Run

Start the executable from the project root (the server will print its bind address and port):

```powershell
./main.exe
```

- The server serves `index.html`; open the URL printed by the program in your browser to access the web UI.
- The program writes logs to [server_out.txt](server_out.txt) and updates [scores.csv](scores.csv) as games progress.

## HTTP Endpoints

- **GET /scores**: Returns the current active game's data as JSON (`application/json`). If no game is active returns `{}`.
- **POST /start**: Start a new game. Accepts form or query parameters: `sport` (Cricket|Football|Basketball|Badminton), `team1`, `team2`, optional `tossWin`, `choice`. Archives any previous active game before starting a new one.
- **POST /update**: Update the active game's score. Parameters: `team` (team name) and `points` (integer). Returns updated game JSON. If the game ends, it is archived automatically.
- **POST /nextphase**: Advance to the next phase (used for Cricket innings). Returns JSON status `{"status":"ok"}` on success.
- **GET /abandon**: Abandon the current game and archive it with remark `Abandoned`.
- **GET /history**: Returns archived games as JSON (reads from `scores.csv`).

- Default server address: `http://localhost:8080`. `main.cpp` launches the default browser automatically shortly after startup.

## Development Notes

- The main entry is `main.cpp` and sport logic resides in the corresponding header files. The design favors small, focused modules for each sport and a thin server wrapper to present scores via HTTP.
- To add a new sport: implement a new header that follows the interface patterns in `Sport.h` and register it in `main.cpp`.

## Troubleshooting

- If build fails with socket-related errors on Windows, ensure MinGW's `libws2_32` is available and that you are passing `-lws2_32`.
- If the web UI does not load, check `server_out.txt` for the bound port and any error messages.