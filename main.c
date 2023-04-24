#include <stdio.h>
#include <string.h>
#include <conio.h>

const int SCREEN_WIDTH = 12;
const int SCREEN_HEIGHT = 20;

int lives;

void display_message(const char *message, int yOffset){
    char buffer[100] = {0};
    strcpy(buffer, message);
    print_at_xy(SCREEN_WIDTH/2 - strlen(message)/2, 
                (SCREEN_HEIGHT/2 - 1)+yOffset, buffer);
}

char get_input(){
    char ch = 0;

    if(kbhit()){
        ch = getch();
    }

    return ch;
}

void clear_screen(){
    char buffer[] = "            "; //12  spaces

    for(int i=0;i<3;i++)
    {
        print_at_xy(0, i, buffer);
    }
}

void decrement_lives(){
    lives--;
}

int zero_lives(){
    if(lives == 0){
        return 1;
    }
    return 0;
}