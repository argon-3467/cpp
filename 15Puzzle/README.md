# [15 Puzzle wiki](https://en.wikipedia.org/wiki/15_puzzle)  

headers folder contains the interface of the following classes
 - Board
 - Tile  
Their implementation is provided in source folder  
Rest of the Classes were trivial and are implemented in the header files itself  
 - Direction
 - Point
 - userinput (namespace)
 - random.h(From [LearnCPP](https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/#RandomH))

Open the folder containing game.cpp and compile and run using  
 `g++ game.cpp source/*.cpp -o game && ./game `  
use 'w' to slide up  
    's' to slide down
    'a' to slide left
    'd' to slide right
    'q' to quit the game
Invalid characters are ignored

