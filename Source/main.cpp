//////////////////////////////////////////
//                                      //
//  Micro:bit AtariBreakout (sort of)   //
//                                      //
//////////////////////////////////////////

#include "MicroBit.h"
MicroBit uBit;

//Define the Size of the Display -1
#define MAX_X 4 
#define MAX_Y 4

//Init Global Varibles
int bar_x = 0; 
int bar_x2 = 1;
bool in_game = false;

//Event if Button A is pressed
void onButtonA(MicroBitEvent)
{
    if (bar_x > 0 && in_game)//Check for Screen Edge
    {
        uBit.display.image.setPixelValue(--bar_x, MAX_Y, 1); //Set new LED
        uBit.display.image.setPixelValue(bar_x2--, MAX_Y, 0); //Reset old LED
    }
}

//Event if Button B is pressed
void onButtonB(MicroBitEvent)
{
    if (bar_x2 < MAX_X && in_game)//Check for Screen Edge
    {
        uBit.display.image.setPixelValue(++bar_x2, MAX_Y, 1); //Set new LED
        uBit.display.image.setPixelValue(bar_x++, MAX_Y, 0); //Reset old LED
    }
}

int main()
{
    //Initlise Controller Funktions
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA); //Eventshandler for Button A
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB); //Eventshandler for Button B
    uBit.display.setDisplayMode(DISPLAY_MODE_BLACK_AND_WHITE); //Configure Display Mode to Pixel on or off

    //Save Microbit Image Files to display on LED Matrix
    MicroBitImage play("0,1,0,0,0\n0,1,1,0,0\n0,1,1,1,0\n0,1,1,0,0\n0,1,0,0,0\n");
    MicroBitImage heart_1("0,1,0,1,0\n1,1,1,1,1\n1,1,1,1,1\n0,1,1,1,0\n0,0,1,0,0\n");
    MicroBitImage heart_2("0,0,0,0,0\n0,1,0,1,0\n0,1,1,1,0\n0,0,1,0,0\n0,0,0,0,0\n");
    MicroBitImage heart_3("0,0,0,0,0\n0,0,0,0,0\n0,0,1,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

    //Declare Local Varibles
    int score;
    int speed;
    int speed_up;
    int ball_x;
    int ball_y;
    int ball_xd;
    int ball_yd;

    //Loop
    while(true)
    {
        //Define Varibles, Resets the after each Loop
        bar_x = 0; 
        bar_x2 = 1;
        score = 0;
        speed = 500;
        speed_up = 20;
        ball_x = 2;
        ball_y = 3;
        ball_xd = -1;
        ball_yd = -1;
        in_game = false;

        //Show Play Image before the Start of the Game
        uBit.display.print(play);
        uBit.sleep(1000);
        uBit.display.image.clear();

        //Draw Game
        uBit.display.image.setPixelValue(ball_x, ball_y, 1);
        uBit.display.image.setPixelValue(bar_x, MAX_Y, 1);
        uBit.display.image.setPixelValue(bar_x2, MAX_Y, 1);
        in_game = true;
        uBit.sleep(speed);

        //Game Loop
        while(in_game)
        {
            //Check for Collision with left and right Border
            if (ball_x + ball_xd < 0) ball_xd = 1;
            else if (ball_x + ball_xd > MAX_Y) ball_xd = -1;

            //Check for Collision with Top and Bottom
            if (ball_y + ball_yd < 0) ball_yd = 1;
            else if (ball_y + ball_yd >= MAX_Y)
            {
                //Check for Hitting the bar
                if (ball_x + ball_xd == bar_x || ball_x + ball_xd == bar_x2)
                {
                    ball_yd = -1;
                    score++; //Increase Score
                    if(speed - speed_up >= 10)speed = speed - speed_up; //Speed up the Game
                }
                else in_game = false; //Game Over
            }

            //Update Display
            uBit.display.image.setPixelValue(ball_x + ball_xd, ball_y + ball_yd, 1);
            uBit.display.image.setPixelValue(ball_x, ball_y, 0);

            //Update Ball Position
            ball_x = ball_x + ball_xd;
            ball_y = ball_y + ball_yd;

            //Sleep for Speed
            uBit.sleep(speed);

            //Check for Game Over
            if (in_game == false)
            {
                //Display Heart Animation
                uBit.display.image.clear();
                uBit.display.print(heart_1);
                uBit.sleep(150);
                uBit.display.print(heart_2);
                uBit.sleep(150);
                uBit.display.print(heart_3);
                uBit.sleep(150);

                //Show Game over Message
                uBit.display.scroll("GAME OVER!");

                //Show Score
                uBit.display.scroll("SCORE");
                ManagedString score_str(score); //Convert int to str
                uBit.display.scroll(score_str);
                uBit.sleep(500);
            }
        }
    }
}
