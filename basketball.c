#include <stdio.h>
void basketball(){
    int team1 = 0, team2 = 0, t;
    char namet1[10], namet2[10];
    printf("Enter name of Team 1: ");
    scanf("%s", namet1);
    printf("Enter name of Team 2: ");
    scanf("%s", namet2);
    while (1){
        int s = 0;
        printf("\nCurrent score: %d - %d", team1, team2);
        printf("\nWho scored the point?");
        printf("\nEnter 1 for team %s", namet1);
        printf("\nEnter 2 for team %s", namet2);
        printf("\nEnter 3 if the time is up");
        printf("\nEnter 4 to reset the scores\n");
        scanf("%d", &t);
        switch(t){
            case 1:
                printf("\nEnter the points scored by team %s: ", namet1);
                scanf("%d", &s);
                if(s>3){
                    printf("Invalid input of scores!!\n");
                    break;
                }
                team1 = team1 + s;
                break;
            case 2:
                printf("\nEnter the points scored by team %s: ", namet2);
                scanf("%d", &s);
                if(s>3){
                    printf("Invalid input of scores!!\n");
                    break;
                }
                team2 = team2 + s;
                break;
            case 4:
                team1 = 0;
                team2 = 0;
                break;

        };
        if(t==3) break;
    };
    printf("\nFinal score:\n%s: %d\n%s: %d\n", namet1, team1, namet2, team2);
    if (team1 > team2) {
        printf("\nTeam %s wins with %d points!\n", namet1, team1);
    } else {
        printf("\nTeam %s wins with %d points!\n", namet2, team2);
    }
}
