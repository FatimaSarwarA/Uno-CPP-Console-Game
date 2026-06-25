# 🃏 UNO C++ Console Game

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)

A comprehensive, terminal-based implementation of the classic UNO card game written entirely in C++. This project was developed as a semester project to demonstrate strong foundational skills in Object-Oriented Programming (OOP), dynamic memory management, and data structure implementation.

## 🎥 Demo


[![UNO Game Demo](https://img.shields.io/badge/Watch-Demo_Video-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/watch?v=YOUR_YOUTUBE_VIDEO_ID)

## 📑 Table of Contents
* [Features](#-features)
* [System Architecture](#-system-architecture)
* [Important Notes & Warnings](#️-important-notes--warnings)
* [Prerequisites](#-prerequisites)
* [Getting Started](#-getting-started)
* [Gameplay Guide](#-gameplay-guide)
* [Future Improvements](#-future-improvements)

## ✨ Features
* **Custom Linked List Implementation:** Manages the game's decks, stockpile, and player hands dynamically using custom nodes, demonstrating memory management without relying on standard library containers like `std::vector`.
* **Dynamic Terminal UI:** Utilizes the Windows API (`<windows.h>`) to provide color-coded terminal output that visually adapts based on the active card color.
* **Complete Game Logic:** Supports all standard UNO rules, including Wild Cards, Draw Two, Skip, and Reverse mechanics.
* **Robust Error Handling:** Validates user inputs and prevents illegal moves using custom exception handling (`std::runtime_error`) to ensure game stability.

## 🏗️ System Architecture
The game is structured around three core C++ classes, emphasizing encapsulation and single-responsibility principles:

* **`UnoCard`**: Represents a single card. Contains enumerations for `Color` (Red, Blue, Green, Yellow, Wild) and `Value` (0-9, DrawTwo, Skip, Reverse, Wild_Card, Wild_Four). It also includes static utility methods for safe string parsing and conversion.
* **`UnoDeck`**: A custom linked-list data structure (`Node*`) that manages a collection of `UnoCard` objects. It handles deck initialization, memory-safe card removal, destructors to prevent memory leaks, and a randomized shuffling algorithm using `<ctime>`.
* **`UnoGame`**: The central controller that tracks the game state. It manages player turn order (`gameDirection`), processes special card effects, and handles interactions between the player hands, the draw deck, and the discard stockpile.

## ⚠️ Important Notes & Warnings
Please be aware of the following constraints and behaviors before compiling or playing the game:

* **OS Dependency (Windows Only):** This application utilizes the `<windows.h>` library specifically for `SetConsoleTextAttribute` to render colored text in the console. Attempting to compile this on macOS or Linux environments will result in fatal compilation errors unless the Windows-specific code is stripped out or replaced with ANSI escape sequences.
* **Case-Sensitive Input:** The string parser for card selection is strictly case-sensitive. When playing a card, you must format it exactly as it appears in your hand (e.g., typing `Red_Skip`, not `red_skip` or `Red Skip`).
* **Console Window Size:** For the best visual experience, ensure your terminal/console window is expanded. Line wrapping on smaller terminal windows may distort the deck display.
* **No Network Multiplayer:** This is a localized "hot-seat" multiplayer game. Players must share the same keyboard/terminal to take their turns.

## 💻 Prerequisites
* **Operating System:** Windows 10/11
* **Compiler:** MSVC (Microsoft Visual C++) or MinGW
* **IDE:** Visual Studio Community (Recommended)

## 🚀 Getting Started
1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/Uno-CPP-Console-Game.git](https://github.com/FatimaSarwarA/Uno-CPP-Console-Game.git)
   ```
2. Open the project directory in Visual Studio Community.
3. Ensure `Code1.0.cpp` is set as your main compilation target.
4. Press `Ctrl + F5` to build and run the executable.

## 🎮 Gameplay Guide
The console interface provides clear feedback on the game state. Once the application is running, follow the on-screen prompts:

1. **Setup:** Enter the names of the players when prompted. Press **Enter** to start the game.
2. **Game State:** At the start of each turn, the console will display the top card on the discard pile, the current player's name, and the cards in their hand[cite: 2].
3. **Taking a Turn:**
    * To play a card from your hand, type `play` and press **Enter**. You will then be asked to type the card's exact name.
    * If you cannot or do not want to play a card, type `draw` and press **Enter** to draw a new card from the deck.
4. **Wild Cards:** If playing a wild card, you will be prompted to enter a declared color[cite: 2]. Valid colors are **Red**, **Blue**, **Green**, and **Yellow**.
5. **Progression:** After each move, press **Enter** to clear the screen and proceed to the next iteration.

## 📈 Future Improvements
* **Cross-Platform Support:** Replace `<windows.h>` coloring with ANSI escape codes to support Linux and macOS terminals seamlessly.
* **Computer AI:** Implement a basic algorithm to allow for single-player games against a CPU opponent.
* **Dynamic Player Scaling:** Refactor the codebase to dynamically prompt for and support between 2 to 10 players.
* **Input Sanitization:** Upgrade the `std::cin` parsing logic to handle lowercase inputs and trailing whitespace automatically to improve User Experience (UX).
