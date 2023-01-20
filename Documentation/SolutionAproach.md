# Solution Aproach

## External Display
We wanted to use a external Display to show the Game. So our first aproach was to source a suitable Display with a I2C or SPI Interface. Our intial plan was as follows:
  * Organise a Display with I2C or SPI interface.
  * Implement Libraries to Setup the Display.
  * Write Testcode to verify the Function of the Display.
  * Learn about the Capabilities and Limitaions of the Display.

## Game Code Plan
We planned on implementing the Game Code as follows:
  * Setup and Test Basic Functions of the MicroBit.
  * Setup Event Handler for Asynchronos Button presses.
  * Progamm Bar and test movement.
  * Programm Collision Detection of Bar and Screen Boarder.
  * Programm Moving Ball.
  * Programm Collision Detection of Ball and Screen Boarder.
  * Programm Colission Detection of Ball and Bar. 
  * Add Game States (Game Over).
  * Add Scoring System.
  * Add Animations.
  * Add Levels

## Using a external Display
We where able to get a hold of a 128x128 1.44inch RGB TFT LCD Display with a SPI Interface.

The Lancaster University Runtime states that it support SPI. The SPI on the micro:bit is supported in the micro:bit runtime through the ARM mbed SPI class. However, by design, this is this is not initialised by default as part of the uBit object.

They recomend to instantiate a instance of SPI, using the mbed SPI class:
``` cpp
SPI spi(MOSI, MISO, SCK);
```
Unfortunatly after many tries it seems to us that the Hardware SPI Interface is not proberly set up in the Lancaster Runtime. 
We have also talked with a other Project Group which had the same Problem. Because of a  lack of Documentation we weren't able to resolve this issue. It is possible to set up a Software Defined SPI Interface. After some Dicussion we decided to use the built-in 5x5 LED Matrix  because of time constraints.

## Internal Display
This solution has a limited resolution of 5x5 pixels, so the game is not very detailed. We had to remove the Bricks from the Display because there wasn't any space on the Display to properly show them. The Plan for implement the Display changed as follows:
  * Familiarizing ourself with the LED matrix of the microbit with help of the documentation
  * Testing built-in functions.
  * Integrate the LED matrix into the game.

# Programm explanation
See `./Source/main.cpp` for the Source Code.

# Microbit System Functions
## Event Handler
An event handler in a microcontroller is a routine that is executed in response to a specific event or interrupt. Events can be triggered by external inputs, such as a button press or by internal processes, such as a timer reaching a certain value. The event handler typically performs a specific task or set of tasks in response to the event.

The micro:bit has an eventing model that can notify user code when specific things happen on the micro:bit.For example, the `MicroBitButton` will send events on a range of button up, down, click and hold events.

For our Program we have implemented a function which listens for Button Presses. We have implemented this because we want to call the Function for the Updating of the Bar even durring execution of the animation of the ball.

``` cpp
uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
```
This event handler is used to Register the Event of Clicking the Button A. If Button A is clicked the Function `onButtonA` is executed.  Same goes for Button B. `MICROBIT_ID_BUTTON_A` and `MICROBIT_BUTTON_EVT_CLICK` are ID's that are defined in the Runntime.

### Function onButtonA/B
``` cpp
void onButtonA(MicroBitEvent)
{
    if (bar_x > 0 && in_game)
    {
        //Code for Updating the Display
    }
}
```

The `if` statment in the Function checks for the Screen Edge. There is a `&&` Statment so the Updating of the Bar only gets Executed during the Game.

## Display
The `MicroBitDisplay` class is a general purpose device driver for controlling LED matrix displays. The Micro:bit uses a 5x5 LED matrix to displays simple 'Images'.

### Display Mode
``` cpp
uBit.display.setDisplayMode(DISPLAY_MODE_BLACK_AND_WHITE);
```
Using this Function we can Configure the Micro:bit to a 'ON/OFF' Display Mode. Normaly the LED are configured for `DISPLAY_MODE_GREYSCALE`, the LED's in this Mode are set with Values from 0-255 to controll the Brigthness of each Display. As we only want to turn the LED ON or OFF we have configured the for `DISPLAY_MODE_BLACK_AND_WHITE`.

### setPixelValue
``` cpp
uBit.display.image.setPixelValue(X_Coordinate,Y_Coordinate,Value);
```
Using this Function we can directly Access the Display Memory Buffer of the Microbit. The memory buffer that is used to drive the LEDs is itself a `MicroBitImage`. We can specify which LED we want to Turn ON/OFF with the Value of 0 or 1. The LED Matrix starts in the Top Left Corner with the Value `0`. As an exaple: To turn on the LED in the second colum second row you would use:
``` cpp
uBit.display.image.setPixelValue(1,1,1);
```
### MicroBitImage
We can save and display Bitmap Images on the Display using `MicroBitImage`. These can be created like any variable. Once created, we can use a function to Display a Image.
``` cpp
MicroBitImage play("0,1,0,0,0\n0,1,1,0,0\n0,1,1,1,0\n0,1,1,0,0\n0,1,0,0,0\n");
```
### Print Images
``` cpp
uBit.display.print(MicroBitImage);
```
Using this Function we can Display Images. We have used this Function to Display a Play Symbol before the Game starts and a small animation before the Game Over Text.
## ManagedString
``` cpp
ManagedString name(value);
```
Using this Function we can convert a Int Value to a String. This is used to Convert the Score so we can later Display it after the Game Over Screen.

## Sleep
``` cpp
uBit.sleep(Value);
```
Using this Function we can Delay the Programm of the Microbit. If this Functions isn't called the Game would run to fast for the Player to keep up. The `Value` in the Function is the Time in miliseconds.

# Game Code
## Global Varibles
``` cpp
int bar_x; 
int bar_x2;
bool in_game;
```

Some Varibles are declared as Globle Varibles. This has to be done so we can use those Varibles in other Functions such as `onButtonA` and `onButtonB`.

## Moving the Ball
``` cpp
int ball_x;
int ball_y;
int ball_xd;
int ball_yd;
```
We are using four Varibles to represent the Position and Direction of the Ball. `ball_x` and `ball_y` represent the X and Y Coordintes of the Ball.
`ball_xd` and `ball_yd` are used to represent the Direct in which the Ball is traveling.

## Checking for Boundries
``` cpp
if (ball_x + ball_xd < 0) ball_xd = 1;
```
Using a simple if Statment we can Check if the Ball would go Outside the Boundrie if he would continue in the Current direction. If that is the case we invert the direct of the Ball.

We can check for the Collision of the Ball and the bar the same way. We check if the next Position of the Ball would be the Same as the Position of the Bar. If that is the Case we invert the Direction of the Ball.

## Game Score
``` cpp
score++;
```
The Game Score get increased each Time the Ball hits the Bar. After Game Over the Score gets Displayed using the `ManagedString` and `uBit.display.scroll()` functions.

## Game Speed
``` cpp
if(speed - speed_up >= 10)speed = speed - speed_up;
```
If the Ball hit the Bar we increase the Speed. The `speed` Varible represents the sleep Time of the Micro:bit after each Cycle. We subtract the Value `speed_up` to decrease the sleep time. If we would choose a higher Value for `speed_up` the game would increase faster. We also check if the value would be smaller or equal to 10 mS. If we don't check for this the game would run as fast as the Cycle Time for the Micro:bit allows and Player couldn't keep up.

## Updating the Display
### Updating the Bar
The Bar only gets updated each time a player presses the Button of the Micro:bit. Example of Button A:
``` cpp
uBit.display.image.setPixelValue(--bar_x, MAX_Y, 1);
uBit.display.image.setPixelValue(bar_x2--, MAX_Y, 0);
```
The first function add the new LED to the Left of the Bar.
The second function delets the old LED to the right of the Bar. 

### Updating the Ball
``` cpp
//Update Display
uBit.display.image.setPixelValue(ball_x + ball_xd, ball_y + ball_yd, 1);
uBit.display.image.setPixelValue(ball_x, ball_y, 0);

//Update Ball Position
ball_x = ball_x + ball_xd;
ball_y = ball_y + ball_yd;
```
The first function add the new LED of the Ball Position.
The second function delets the old LED of the Ball Position.
After that the Ball Position gets Update to the new  Psotition using the Ball Direction$.