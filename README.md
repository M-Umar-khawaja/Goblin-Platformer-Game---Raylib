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

3. ## Game Over or Level Transition:
   - Displays a game-over screen when the player loses or transitions to the next level if they succeed.
   - Allows the player to restart or quit.

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
