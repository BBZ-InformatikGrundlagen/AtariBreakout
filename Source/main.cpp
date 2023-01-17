#include "MicroBit.h"

MicroBit uBit;
int bar_x = 0;
int point = 0;
int interval = 0;
int interval_step = 0;
int ball_x = 0;
int ball_y = 0;
int ball_dx = 0;
int ball_dy = 0;
bool in_game = false;


void onButtonA(MicroBitEvent)
{
    if (bar_x > 0) {
        uBit.display.image.setPixelValue(bar_x + 1,4,0);
        bar_x = bar_x - 1;
        uBit.display.image.setPixelValue(bar_x,4,1);
    }
}

void onButtonB(MicroBitEvent)
{
    if (bar_x < 3) {
        uBit.display.image.setPixelValue(bar_x,4,0);
        bar_x = bar_x + 1;
        uBit.display.image.setPixelValue(bar_x + 1,4,1);
    }
}

int main()
{
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.display.setDisplayMode(DISPLAY_MODE_BLACK_AND_WHITE); //Pixel on or off

    point = 0;
    interval = 500;
    interval_step = 10;
    ball_x = 3;
    ball_y = 3;
    ball_dx = -1;
    ball_dy = -1;
    bar_x = 0;
    //uBit.display.scroll("GO!");
    uBit.display.image.setPixelValue(ball_x,ball_y,1);
    uBit.display.image.setPixelValue(bar_x, 4 ,1);
    uBit.display.image.setPixelValue(bar_x + 1, 4,1);
    in_game = true;

    while(true){
   
        if (ball_x == 4){
            ball_dx = -1;
        }
        else if (ball_x == 0){
            ball_dx = 1;
        }

        if (ball_y == 0) {
            ball_dy = 1;
        }
        else if (ball_y == 4 ) {
            if (bar_x == ball_x || bar_x + 1 == ball_x) {
                ball_dy = -1;
                point++;
            }
            else {
                in_game = false;
            }
        }

        if (in_game) {
            uBit.display.image.setPixelValue(ball_x , ball_y ,0);
            ball_x = ball_x + ball_dx;
            ball_y = ball_y + ball_dy;
            uBit.display.image.setPixelValue(ball_x , ball_y ,1);

            uBit.sleep(500); //sleep for interval
        } 
        else {
            uBit.display.scroll("GAME OVER!");
        }
    }
}
