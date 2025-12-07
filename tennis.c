#include <stdio.h>
void clearInputBuffer(void);
void tennis() {
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
    while (1){
        int f;
        clearInputBuffer();
        printf("\nCurrent server: %s\n", (n == 1) ? np1 : np2);
        printf("Current score: %d - %d\n", p1, p2);
        printf("\nWho scored a point? (Enter 1 for %s, 2 for %s): ", np1, np2);
        f = scanf("%d", &n);
        if ((n == 1 || n == 2) && f == 1) {
            if (p1 >= 4 && p2 >= 4) {
                p1 = 4;
                p2 = 4;
            }
            else if (n == 1) {
                p1++;
            }
            else if (n == 2) {
                p2++;
            }
        }
        else {
            printf("Invalid input. Please enter 1 or 2.\n");
            continue;
        }

        if (p1>=4 || p2>=4) {
            if ((p2<=2 && p1>=4) || (p1<=2 && p2>=4)) {
                break;
            }
        };
    };
    int points[6] = {0, 15, 30, 40, 40, 40};
    printf("\nFinal score:\n%s: %d\n%s: %d\n", np1, points[p1], np2, points[p2]);
    if (p1 > p2) {
        printf("%s wins with %d points!\n", np1, points[p1]);
    } else {
        printf("%s wins with %d points!\n", np2, points[p2]);
    }
}
