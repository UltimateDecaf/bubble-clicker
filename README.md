# bubble-clicker
 A simple Bubble Clicker game for Windows made with C++ and SFML.
 
 **Goal:** make a simple game to get comfortable with SFML functionality and C++ syntax and features (e.g. std::shared_ptr<T>)

 Although, I go through different courses that delve into C++ and Game Programming specifically, in this small project I dealt on my own with:

- alignment of sprites and text using code (though implementation was in SFML, the concepts can be well translated into game engines).
- adding a timer countdown that is properly displayed in game.
- C++11 Random Number Generation.
- How and when should the program generate random positions for bubbles. 100 positions are calculated at the start-up, and stored in a std::vector. The game goes through a vector one by one, whenever the bubble is popped.
- Changing states (the game screen and game related UI are not shown, while not in game session).
- Making game replayable in one session (where and how to reset variables so that the game can be replayed without any exceptions).

For this project I decided not to make separate classes and methods, all of the functionality is in main() function. However, if I decide to proceed further with the project, a better code organization will be introduced.

Apart from code organization, certain features can be introduced or fixed:
- Better randomization of positions.
- Simple animation to show a successful click.
- Randomize bubble's radius within a defined range.
- Introduce power-ups (e.g. time limit extension).
- Make more bubbles appear on screen and add a lifetime to them.

<img src="https://github.com/UltimateDecaf/bubble-clicker/blob/main/clicker-gif.gif)https://github.com/UltimateDecaf/bubble-clicker/blob/main/clicker-gif.gif" width="50%" height="50%">
