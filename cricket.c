#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 11

struct Player {
    char name[50];
    int runs;
    int balls;
    int wickets;
    float overs;
};

struct Team {
    char name[50];
    struct Player players[MAX_PLAYERS];
    int totalRuns;
    int totalWickets;
};

void inputTeamDetails(struct Team *team, int numPlayers) {
    printf("Enter team name: ");
    scanf(" %[^\n]", team->name);
    team->totalRuns = 0;
    team->totalWickets = 0;
    printf("\n--- Enter Player Details for %s ---\n", team->name);
    for (int i = 0; i < numPlayers; i++) {
        printf("\nPlayer %d name: ", i + 1);
        scanf(" %[^\n]", team->players[i].name);
        printf("Runs scored by %s: ", team->players[i].name);
        scanf("%d", &team->players[i].runs);
        printf("Balls faced by %s: ", team->players[i].name);
        scanf("%d", &team->players[i].balls);
        printf("Wickets taken by %s: ", team->players[i].name);
        scanf("%d", &team->players[i].wickets);
        printf("Overs bowled by %s: ", team->players[i].name);
        scanf("%f", &team->players[i].overs);
        team->totalRuns += team->players[i].runs;
        team->totalWickets += team->players[i].wickets;
    }
}

void displayScorecard(struct Team team, int numPlayers) {
    printf("\n\n==============================\n");
    printf("        SCORECARD - %s\n", team.name);
    printf("==============================\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Player", "Runs", "Balls", "Wkts", "Overs");
    for (int i = 0; i < numPlayers; i++) {
        printf("%-20s %-10d %-10d %-10d %-10.1f\n",
               team.players[i].name,
               team.players[i].runs,
               team.players[i].balls,
               team.players[i].wickets,
               team.players[i].overs);
    }
    printf("-------------------------------------------\n");
    printf("Total Runs: %d\n", team.totalRuns);
    printf("Total Wickets: %d\n", team.totalWickets);
    printf("===========================================\n");
}

void decideWinner(struct Team t1, struct Team t2) {
    printf("\n\n******** MATCH RESULT ********\n");
    if (t1.totalRuns > t2.totalRuns)
        printf("%s won the match by %d runs!\n", t1.name, t1.totalRuns - t2.totalRuns);
    else if (t2.totalRuns > t1.totalRuns)
        printf("%s won the match by %d runs!\n", t2.name, t2.totalRuns - t1.totalRuns);
    else
        printf("The match is a tie!\n");
    printf("*******************************\n");
}

int cricket() {
    struct Team team1, team2;
    int numPlayers;
    printf("Enter number of players per team (max %d): ", MAX_PLAYERS);
    scanf("%d", &numPlayers);
    if (numPlayers > MAX_PLAYERS || numPlayers <= 0) {
        printf("Invalid number of players!\n");
        return 1;
    }
    printf("\n=== TEAM 1 DETAILS ===\n");
    inputTeamDetails(&team1, numPlayers);
    printf("\n=== TEAM 2 DETAILS ===\n");
    inputTeamDetails(&team2, numPlayers);
    displayScorecard(team1, numPlayers);
    displayScorecard(team2, numPlayers);
    decideWinner(team1, team2);
    return 0;
}
