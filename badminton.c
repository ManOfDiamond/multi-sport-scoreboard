#include <stdio.h>
void clearInputBuffer(void);
void badminton() {
    int p1 = 0, p2 = 0, n;
    char np1[20], np2[20];
    printf("Enter name of player 1: ");
    scanf("%s", np1);
    printf("Enter name of player 2: ");
    scanf("%s", np2);
    printf("(Decided based on real-time toss)\nWho will serve first? (Enter 1 for %s, 2 for %s): ", np1, np2);
    scanf("%d", &n);
    if (n != 1 && n != 2) {
        printf("Invalid choice for server. Defaulting to %s.\n", np1);
        n = 1;
        clearInputBuffer();
    }
    while (1){ //p1 < 25 && p2 < 25) {
        printf("\nCurrent server: %s\n", (n == 1) ? np1 : np2);
        printf("Current score: %d - %d\n", p1, p2);
        printf("\nWho scored a point? (Enter 1 for %s, 2 for %s): ", np1, np2);
        scanf("%d", &n);
        if (n == 1) {
            p1++;
        }
        else if (n == 2) {
            p2++;
        }
        else {
            printf("Invalid input. Please enter 1 or 2.\n");
            clearInputBuffer();
            continue;
        }
        if (p1>=20 || p2>=20) {
            if ((p1>=p2+2 && p1>=21) || (p2>=p1+2 && p2>=21)) {
                break;
            }
        };
    };
    printf("\nFinal score:\n%s: %d\n%s: %d\n", np1, p1, np2, p2);
    if (p1 > p2) {
        printf("%s wins with %d points!\n", np1, p1);
    } else {
        printf("%s wins with %d points!\n", np2, p2);
    }
}
