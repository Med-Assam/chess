# Chess Game - C Project

**Team Members:**
- Mohamed Assam
- Abdelmoujib Bricha

A fully functional chess game developed in **C11** with complete chess rules, check/checkmate detection, and memory-safe design. Terminal-based UI with Windows console colors for enhanced visual experience.

## Features

✅ **Complete Chess Rules**
- All pieces move correctly (Pawn, Rook, Knight, Bishop, Queen, King)
- Move validation and path checking
- Check and Checkmate detection
- Stalemate detection
- Pawn promotion

✅ **User Interface**
- Enhanced terminal UI with Windows console colors
- Formatted 8×8 chessboard with piece symbols
- Real-time turn indicator
- Move counter
- Menu system with rules

✅ **Code Quality**
- Modular architecture (6 separate modules)
- Zero memory leaks (all malloc/free paired)
- Compiled with strict warnings: -Wall -Wextra -Wpedantic
- Well-commented and structured code
- Professional C11 standards

## Project Structure

```
chess-c/
├── src/
│   ├── main.c          # Entry point, game loop
│   ├── game.c          # Game state management
│   ├── board.c         # Board logic and layout
│   ├── piece.c         # Piece type utilities
│   ├── move.c          # Move validation, check/mate detection
│   └── graphics.c      # Raylib rendering
├── include/
│   ├── defines.h       # Constants and type definitions
│   ├── game.h          # Game state header
│   ├── board.h         # Board header
│   ├── piece.h         # Piece header
│   ├── move.h          # Move validation header
│   └── graphics.h      # Graphics header
├── Makefile            # Build configuration
└── README.md           # This file
```

## Prerequisites

- **GCC/MinGW** (C11 support)
- **Windows** (for console colors) or **Linux/macOS** compatible

## Installation

### Windows (MinGW)
1. Install MinGW-w64 with GCC
2. No additional libraries needed - uses Windows standard API

### Linux/macOS
```bash
sudo apt-get install build-essential  # Linux
brew install gcc                      # macOS
```

## Compilation

### Using Makefile (Windows)
```bash
make
```

### Manual Compilation (Windows)
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -g src/*.c -o chess.exe -Iinclude -lm
```

### Manual Compilation (Linux/macOS)
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -g src/*.c -o chess -Iinclude -lm
```

## Execution

### Windows
```bash
chess.exe
# or
make run
```

### Linux/macOS
```bash
./chess
```

## How to Play

**Main Menu:**
```
> play            # Start a new game
> rules           # Show chess rules
> quit            # Exit the application
```

**During Game:**
```
Enter moves in format: SOURCE DESTINATION
Example: e2 e4    (moves piece from e2 to e4)

Commands:
- Type move (e.g., "e2 e4") to move pieces
- Type "reset" to start a new game
- Type "quit" to exit
```

**Piece Notation:**
- Uppercase (P, R, N, B, Q, K) = White pieces
- Lowercase (p, r, n, b, q, k) = Black pieces
- `.` = Empty square

## Game Rules Implemented

1. **Pawn**: Moves 1 square forward (2 on first move), captures diagonally
2. **Rook**: Moves any number of squares horizontally or vertically
3. **Knight**: Moves in L-shape (2+1 squares)
4. **Bishop**: Moves diagonally any number of squares
5. **Queen**: Combines Rook and Bishop movements
6. **King**: Moves 1 square in any direction
7. **Check**: King is under attack
8. **Checkmate**: King in check with no legal moves (game ends, player wins)
9. **Stalemate**: King not in check but no legal moves (draw)

## Memory Management

✅ **Zero Memory Leaks**
- Board dynamically allocated at startup
- Temporary boards created for move validation, freed immediately
- Game state single allocation, freed on exit
- All malloc/free calls balanced and verified

## Architecture Overview

### Game Flow
1. **Menu State**: Main menu options
2. **Playing State**: Take turns entering moves
3. **Checkmate/Stalemate**: Game detects end conditions
4. **Reset**: Start new game anytime

### Key Modules

| Module | Purpose | Lines |
|--------|---------|-------|
| game.c | Game state, turn management, move execution | ~80 |
| board.c | Board state, initialization, piece placement | ~90 |
| piece.c | Piece type identification and utilities | ~50 |
| move.c | Move validation, check/mate detection (most complex) | ~180 |
| graphics.c | Terminal UI and output | ~40 |
| main.c | Entry point, input handling, game loop | ~150 |

## Testing

### Compile with Memory Checking
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -fsanitize=address -g src/*.c -o chess -Iinclude -lraylib
./chess
```

### Test Checkmate Scenario
1. Navigate Kings toward each other
2. Try to create checkmate position manually
3. Game automatically detects and ends

### Test Stalemate
1. Set up stalemate position
2. Game notifies draw (stalemate)

## Known Limitations

- Castling not implemented
- En passant capture not implemented
- No move undo functionality
- No save/load game
- Piece promotion defaults to Queen
- No AI opponent (2-player only)

## Future Improvements

- Add Castling and En Passant rules
- Implement move history and undo
- Add game save/load functionality
- Create single-player AI with difficulty levels
- Add sound effects and animations
- Implement clock for timed games
- Add multiplayer over network

## Code Quality Standards

- **Naming**: Clear, descriptive function and variable names
- **Modularity**: Separate concerns into dedicated files
- **Memory Safety**: Every allocation has matching free
- **Error Handling**: Null checks and bounds validation
- **Comments**: Key logic explained inline

## Compilation Flags Explained

| Flag | Purpose |
|------|---------|
| `-std=c11` | Use C11 standard |
| `-Wall -Wextra -Wpedantic` | Enable all warnings, extra checks |
| `-fsanitize=address` | Detect memory leaks and errors |
| `-g` | Include debugging symbols |
| `-Iinclude` | Include header search path |
| `-lraylib` | Link Raylib library |

## Author

Developed as a C programming project demonstrating:
- Modular design and separation of concerns
- Proper memory management in C
- Game logic implementation
- Graphics integration with Raylib
- Compliance with strict coding standards

## License

This project is open source for educational purposes.

## Game Screenshots

### Menu Screen
```
CHESS - C Project
Press ENTER to Start
Press Q to Quit
```

### Playing Board
- 8×8 grid with alternating light/dark squares
- Pieces shown as letter symbols (P, R, N, B, Q, K)
- Selected piece highlighted in green
- Current player turn displayed

### Game Over
```
White Wins - Checkmate!
Press R to Restart | Q to Quit
```

## Troubleshooting

**Issue**: `raylib.h: No such file or directory`
- **Solution**: Install Raylib and ensure it's in your include path

**Issue**: Memory leak warnings
- **Solution**: Recompile and run with ASAN enabled to identify the leak

**Issue**: Game won't compile
- **Solution**: Verify GCC supports C11 (`gcc --version`)

---

**Last Updated**: April 7, 2026
