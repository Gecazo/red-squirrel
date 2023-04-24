#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h> // to use HANDLE

const int SCREEN_WIDTH = 12;
const int SCREEN_HEIGHT = 20;

int GOAL_POINTS;

int lives;
int score;

int immunity_count_down;

HANDLE _output_handle; // works only on windows

void hidecursor()
{
   _output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(_output_handle, &info);
}

void display_message(const char *message, int yOffset){
    char buffer[100] = {0};
    strcpy(buffer, message);
    print_at_xy(SCREEN_WIDTH/2 - strlen(message)/2, 
                (SCREEN_HEIGHT/2 - 1)+yOffset, buffer);
}

void display_score(){
    char buffer[50] = {0};
    sprintf(buffer, "SCORE: %4d LIVES: %d", score, lives);
    print_at_xy(0, 0, buffer);
}

void display_count_down(){
    if(immunity_count_down > 0){
        char buffer[3] = {0};
        char *countdown = itoa(immunity_count_down/10, buffer, 10);
        strcpy(buffer, countdown);
        SetConsoleTextAttribute (_output_handle, FOREGROUND_BLUE);
        display_message("GET READY!", -2);
        display_message(buffer, 0);
        SetConsoleTextAttribute (_output_handle, FOREGROUND_INTENSITY);
    }
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

void increment_score(){
    score += GOAL_POINTS;
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