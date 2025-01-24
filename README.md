## Note on Game Structure:
This game was developed using C++ classes to manage different game components such as the player, enemies, and platforms. However, the classes are not optimized, and the game was initially intended to be completed in a single file. As a result, the code structure could be improved by separating it into header files and implementing more efficient class designs.
For future improvements, the classes should be optimized for better performance, and the project should be refactored into multiple files to improve code organization and maintainability

# Goblin-Platformer-Game-Raylib
This is a simple 2D platformer game prototype made using the Raylib library. In this game, you control a goblin character as it runs, jumps, and dodges obstacles to reach the goal. While this is a functional prototype, it may have some glitches and is a work in progress. The game combines fun mechanics with smooth gameplay to provide an enjoyable experience. Here's an overview of the project:

## Features
- **Game Window**: A well-designed game window to display all the action.
- **Player Controls**: Smooth movement and jumping mechanics for the goblin.
- **Enemies & Platforms**: Dynamic enemies and platforms to challenge the player.
- **Scoring & Levels**: Tracks the score and transitions between levels.
- **End Conditions**: Displays a game-over screen or transitions to the next level when conditions are met.
- **Visuals & Sounds**: Includes colorful assets and sound effects to enhance the experience.

## How It Works
1. ## Game Initialization:
   - Sets up the game window and loads all assets (images and sounds).
   - Initializes the player, enemies, platforms, and essential variables like score and level.

2. ## Main Game Loop:
   - Process Input: Captures user input (keyboard or mouse) for character control.
   - Update Game State:
     - Updates player and enemy movements.
     - Handles collisions between the goblin, enemies, and platforms.
     - Applies gravity and jumping mechanics for smooth gameplay.
   -  Render the Scene: Draws the goblin, enemies, platforms, and the background to the screen.
   - Check End Conditions: Determines if the player has won or lost the level.
![image](https://github.com/user-attachments/assets/4882f98c-3913-48ed-9f44-e6c030def3b1)
![image](https://github.com/user-attachments/assets/31286038-14f1-4d7d-8140-8b4c04cb7517)
![image](https://github.com/user-attachments/assets/24d61748-813b-4142-b39c-2c5f7f802de6)
![image](https://github.com/user-attachments/assets/94134e2e-3668-4e8a-aca2-14967fe50881)

3. ## Game Over or Level Transition:
   - Displays a game-over screen when the player loses or transitions to the next level if they succeed.
   - Allows the player to restart or quit.
![image](https://github.com/user-attachments/assets/39711259-e40a-4095-9010-2e30be0615d6)
![image](https://github.com/user-attachments/assets/2d6d1c48-e378-4aa7-a702-dfc46dc4e364)

## Why This Project?
This project was created to learn and practice game development concepts using Raylib. It focuses on:
- Handling player inputs and physics.
- Managing game objects like platforms and enemies.
- Creating a basic game loop and logic.
However, as a prototype, there are known glitches, and the game is still a work in progress.

## Getting Started
To play the game or explore the code:
1. Clone this repository.
2. Make sure you have Raylib installed on your system.
3. Compile and run the game using your preferred C++ compiler.
Feel free to explore, modify, or share your feedback on this project! 😊
