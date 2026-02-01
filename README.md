# Fetlar Hnefatafl Terminal

A terminal-based implementation of the ancient Norse board game Hnefatafl, specifically following the Fetlar competition rules. This project is written in C++ and designed for Windows environments.

## Description

This application brings the strategic depth of Hnefatafl to the command line. The game features an 11x11 board where the defenders must escort their King to one of the corner squares, while the attackers attempt to capture him.

### Game Rules
The logic is based on the **Fetlar Hnefatafl** rules. Key mechanics include:
* Captured pieces are removed when surrounded on two opposite sides by enemies.
* The King must reach any of the four corner squares to win.
* The King is captured if surrounded on all four sides (or three sides plus the central Throne).

For a detailed explanation of the rules, visit [this site](https://aagenielsen.dk/fetlar_rules_en.php).


## Prerequisites

* **Operating System:** Windows.
* **Compiler:** A C++ compiler supporting C++11 (like MinGW/GCC).
* **(optional) Environment:** Dev-C++ 5.11 (if you wish to compile using IDE).

## How to Run

### 1. Compilation
You can compile the project manually via g++ or in Dev-C++ IDE.

**Using g++ directly:**
```
g++ main.cpp Game.cpp TerminalRenderer.cpp -o fetlar-hnefatafl-terminal.exe -std=c++11
```

**Or just with Dev-C++:**
```
Open the project and press F11.
```

### 2. Execution
Run the compiled executable from your terminal:
```
fetlar-hnefatafl-terminal.exe
``` 
<sup>btw, it `cls`'es your terminal first.</sup>

## Controls
The game is played within the terminal.
- `ARROWS`/`WSAD` - move indicator
- `ENTER`/`SPACE` - confirm selection
- `ESC` - cancel selection / exit the game
- `R` - cancel selection / reset the game