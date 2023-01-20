# Solution Aproach

 ## External Display
We wanted to use a external Display to show the Game. So our first aproach was to source a suitable Display with a I2C or SPI Interface. Our intial plan was as follows:
  * Organise a Display with I2C or SPI interface.
  * Implement Libraries to Setup the Display.
  * Write Testcode to verify the Function of the Display.
  * Learn about the Capabilities and Limitaions of the Display.

## Game Code
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

## Internal Display
Unfortunately, we were unable to get the external display working for our project. The issue was with the SPI interface, which we were unable to properly configure for communication with the external display. Another Group was able to get it working but unfortunatly we where running out of time and had to resort to using the built-in 5x5 LED matrix as an alternative.

Note:
This solution has a limited resolution of 5x5 pixels, so the game is not very detailed. We had to remove the Bricks from the Display because there wasn't any space on the Display to properly show them.