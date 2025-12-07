#include <stdio.h>
#include "badminton.c"
#include "volleyball.c"
#include "tennis.c"
#include "basketball.c"
#include "cricket.c"
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void badminton(), volleyball(), tennis(), basketball();
int cricket();
int main()
{
    int ch, c=1;
    while (c==1){
        printf("\n======================\nMulti-Sport Scoreboard\n======================\nMenu:\n0. Exit\n1. Badminton\n2. Volleyball\n3. Tennis\n4. Basketball\n5. Cricket\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch){
            case 0:
                c=0;
                break;
            case 1:
                badminton();
                clearInputBuffer();
                break;
            case 2:
                volleyball();
                clearInputBuffer();
                break;
            case 3:
                tennis();
                clearInputBuffer();
                break;
            case 4:
                basketball();
                clearInputBuffer();
                break;
            case 5:
                cricket();
                clearInputBuffer();
                break;
            default:
                printf("Invalid choice...");
        };
    };
    return 0;
}
