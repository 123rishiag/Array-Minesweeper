# Array Minesweeper

## Overview
Welcome to **Minesweeper**, a classic puzzle game that combines strategy and quick thinking. In this project, we'll recreate this iconic game using C++ and SFML, diving deep into game mechanics and 2D arrays to deliver an engaging experience.

## Features
- **Grid Mechanics**: 
  - Navigate a grid of cells to uncover safe areas and avoid mines.
  - Use clues from adjacent cells to locate hidden mines.
- **Mine Detection**: 
  - Reveal cells to gather information about nearby mines.
  - Flag suspected mines to avoid triggering them.
- **Game State Management**: 
  - Handle game state transitions smoothly, including win and lose conditions.

## Learning Outcomes

- **Data Structures**: Gained hands-on experience with 2D arrays, crucial for implementing grid-based games like Minesweeper.
- **Game Logic**: Developed an understanding of game mechanics and state management.
- **User Interface**: Designed and implemented an intuitive UI to enhance the gameplay experience.
- **Event Handling**: Created responsive controls for smooth and engaging gameplay.
- **Object-Oriented Design**: Enhanced understanding of OOP principles and practices.
- **Game Loop and State Management**: Maintained fluid transitions and consistent game state throughout the gameplay.

## Project Structure

### Services and Their Model, View, and Controllers

- **GraphicService**: Manages game window and rendering operations.
- **EventService**: Handles user input and game events.
- **TimeService**: Manages game timing and countdowns.
- **SoundService**: Manages sound effects and music playback.
- **UIService**: Manages UI components.
  - UI Controllers: `SplashScreenUIController`, `MainMenuUIController`, `LevelConfigurationUIController`, `InstructionsUIController`, `GameplayUIController`, `CreditsScreenUIController`
  - UI Elements: `UIView`, `TextView`, `ImageView`, `ButtonView`, `AnimatedImageView`
  - UI Interface: `IUIController`
- **GameplayService**: Manages core gameplay mechanics and win/loss conditions.
  - Includes: `GameplayController`, `GameplayView`
- **BoardService**: Manages the grid layout and cell interactions.
  - Includes: `BoardController`, `BoardView`, `CellController`, `CellModel`, `CellView`

### Additional Core Components

- **Main**: Entry point of the game.
- **GameService**: Core service for game initialization and management.
  - Declares and manages all game states.
  - Oversees the initialization, updating, and rendering of `ServiceLocator`.
- **ServiceLocator**: Coordinates the initialization, updating, and rendering of all services, ensuring efficient communication between them.
- **Config**: Contains file paths for assets, including textures, sounds, and fonts.

## How to Play

### Controls
- **Reveal**: Click on a cell to reveal its contents.
- **Flag**: Right-click on a cell to mark it with a flag for suspected mines.
- **Objective**: Uncover all safe cells and avoid mines to win.

1. **Clone the repository**:
    ```bash
    git clone https://github.com/123rishiag/Array-Minesweeper.git
    ```
2. **Build the project** using your preferred C++ compiler.
   - Ensure you have SFML installed. Installation instructions are available on SFML’s [official website](https://www.sfml-dev.org/).

3. **Run the executable** to start the game.

## Video Demo
Watch the [Video Demo](https://www.loom.com/share/6a6e5f76320449f19d989a61aa6b6b65?sid=77630b8c-7677-499a-a1b3-d792a3068aad) to understand Minesweeper's gameplay!