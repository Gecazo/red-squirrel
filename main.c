#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h> // to use HANDLE


const int SCREEN_WIDTH = 12;
const int SCREEN_HEIGHT = 20;

int GOAL_POINTS;

int lives;
int score;

int wall_y_pos;
int WALL_SPEED;

char left_wall[60];
char right_wall[60];
char left_spike[3];
char right_spike[3];

int left_wall_spike;
int right_wall_spike;

int game_state;
int GAME_STATE_OVER;

int squirrel_delta;
int squirrel_SPEED;
char squirrel[2];
int squirrel_x;
int squirrel_y;

int immunity_count_down;


HANDLE _output_handle; // works only on windows


int main()
void init()

void hidecursor()
{
   _output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(_output_handle, &info);
}

void print_at_xy(int x, int y, char *val)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(_output_handle, coord);
  printf("%s", (const char *)val);
  fflush(stdout);
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

void draw_wall(){
    char wall_row[SCREEN_WIDTH+1];
    int wall_index = wall_y_pos * -1;
    left_wall_spike = 0;
    right_wall_spike = 0;
    for(int i=2;i<20;i++,wall_index++){

        for(int j=1;j<SCREEN_WIDTH;j++){
            wall_row[j] = ' ';
        }

        wall_row[SCREEN_WIDTH+1] = '\0';

        wall_row[0] = '|';
        wall_row[SCREEN_WIDTH] = '|';
        
        if(left_wall[wall_index] == '>'){            
            wall_row[1] = '>';
            if(i==SCREEN_HEIGHT/2){
                left_wall_spike = 1;
            }
        }


        if(right_wall[wall_index] == '<'){            
            wall_row[SCREEN_WIDTH-1] = '<';
            if(i==SCREEN_HEIGHT/2){
                right_wall_spike = 1;
            }
        }

        print_at_xy(0, i, wall_row);
    }
}

void draw_squirrel(){

    if(squirrel_y >= SCREEN_HEIGHT) return;

    SetConsoleTextAttribute (_output_handle, FOREGROUND_RED);
    print_at_xy(squirrel_x, squirrel_y, squirrel); 
    SetConsoleTextAttribute (_output_handle, FOREGROUND_INTENSITY);  
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

void update_squirrel(char ch){
    squirrel_x += squirrel_delta;
    if(squirrel_x == 1 && ch == 'j' && game_state == GAME_STATE_PLAYING){
        squirrel_delta = squirrel_SPEED;
        squirrel_x += squirrel_delta;
        increment_score();
    }
    else if(squirrel_x == SCREEN_WIDTH-1 && ch == 'j' && game_state == GAME_STATE_PLAYING){
        squirrel_delta = -squirrel_SPEED;
        squirrel_x += squirrel_delta;
        increment_score();
    }
    else if(squirrel_x <= 1){
        squirrel_delta = 0;
        squirrel_x = 1;        
    }
    else if(squirrel_x >= SCREEN_WIDTH-1){
        squirrel_delta = 0;
        squirrel_x = SCREEN_WIDTH-1;
    }  

    if(immunity_count_down > 10 && lives < 3){
        squirrel_x = SCREEN_WIDTH/2;
        squirrel_y += 1;
        if(squirrel_y >= SCREEN_HEIGHT){
            squirrel_y = SCREEN_HEIGHT;
        }
    }
    if(immunity_count_down < 10 && immunity_count_down > 1){
        squirrel_x = 1;
        squirrel_y = SCREEN_HEIGHT / 2;
    }  
}

void update_wall(){
    wall_y_pos += WALL_SPEED;
    if(wall_y_pos > 0){
        wall_y_pos = -SCREEN_HEIGHT;
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

void draw(){
    display_score();
    display_count_down();
}

int collides_with_spike(){
    if(game_state == GAME_STATE_OVER){
        return 0;
    }

    if(squirrel_x == 1 && left_wall_spike == 1){
        return 1;
    }
    else if(squirrel_x == SCREEN_WIDTH-1 && right_wall_spike == 1){
        return 1;
    }

    return 0;
}