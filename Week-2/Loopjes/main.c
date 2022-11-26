#include <stdio.h>


int main() {
    int w = 20;
    int h = 5;
    /*//Opdracht A
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 20; ++j) {
            printf("#");
        }
        printf("\n");
    }*/
    /*   //Opdracht B
       for (int i = 0; i < w; ++i) {
           printf("#");
       }
       printf("\n");
       for (int i = 0; i < 3; ++i) {
           printf("%-18s %s", "#", "#");
           printf("\n");
       }
       for (int i = 0; i < w; ++i) {
           printf("#");
       }*/
    //Opdracht C
    int marioH = 8;
    int x = 7;
    int marioW = 1;
    //Loop voor hoogte
    for (int i = 0; i < marioH; ++i) {
        //Loop voor aantal whitespaces neemt elke look af
        for (int j = 0; j < x; ++j) {
            printf(" ");
        }
        //Loop voor aantal "#" neemt elke loop toe en is right aligned door de whitespaces niet door format
        //fun fact if you add a 2 to the %s like  this %2s it makes a perfect pyramid
        for (int j = 0; j < marioW; ++j) {
            printf("%s","#");
        }
        x--;
        marioW++;
        printf("\n");
    }
    return 0;
}
