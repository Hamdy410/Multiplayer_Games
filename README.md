# SFML Multi-Player Games Collection

A modern, extensible game collection application built with SFML (Simple and Fast Multimedia Library) that provides a polished user interface for launching and playing various games. Currently features a fully functional Tic-Tac-Toe game with plans for expansion.

## 🎮 Features

### Core Application
- **Modern UI Framework**: Clean, responsive interface with animated background patterns
- **State Management**: Robust state machine for seamless navigation between menu and games
- **Extensible Architecture**: Easy to add new games through a well-defined interface
- **Cross-Platform**: Built with CMake for easy compilation on Windows, macOS, and Linux

### User Interface
- **Dynamic Background Patterns**: 4 different animated background styles (Grid Fade, Floating Pixels, Wave Pattern, Matrix Rain)
- **Interactive Game Cards**: Clickable game selection cards with descriptions and icons
- **Responsive Layout**: Adaptive UI that works with different window sizes
- **Smooth Animations**: 60 FPS rendering with smooth transitions and effects

### Games
- **Tic-Tac-Toe**: Complete implementation with:
  - Turn-based gameplay (X and O players)
  - Win detection (rows, columns, diagonals)
  - Draw detection
  - Visual win line indicators
  - Game reset functionality
  - Status display

### Technical Features
- **SFML 2.5+ & 3.x Compatibility**: Automatic version detection and appropriate linking
- **Modern C++17**: Leverages modern C++ features for clean, maintainable code
- **Memory Management**: Smart pointers and RAII for automatic resource management
- **Event-Driven Architecture**: Efficient event handling system
- **Asset Management**: Automatic asset copying and fallback handling

## 🏗️ Architecture

### Core Components

```
src/
├── core/           # Application core and state management
├── states/         # Application states (menu, game)
├── games/          # Game implementations
└── ui/             # User interface components
```

### Design Patterns

- **State Pattern**: Clean separation between menu and game states
- **Strategy Pattern**: Pluggable game implementations via `IGame` interface
- **Observer Pattern**: Event-driven UI updates
- **Factory Pattern**: Dynamic game object creation

### Key Classes

- **`Application`**: Main application loop and window management
- **`StateManager`**: Handles state transitions and stack management
- **`BaseState`**: Abstract base for all application states
- **`IGame`**: Interface for all game implementations
- **`XOGame`**: Tic-Tac-Toe game implementation
- **`GameCard`**: Interactive game selection cards
- **`BackgroundPattern`**: Animated background system

## 🚀 Installation

### Prerequisites

- **C++17 compatible compiler** (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake 3.15 or higher**
- **SFML 2.5+ or 3.x**

### Building from Source

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd sfml-xo
   ```

2. **Create build directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**
   ```bash
   cmake ..
   ```

4. **Build the project**
   ```bash
   cmake --build .
   ```

5. **Run the application**
   ```bash
   ./bin/sfml-app  # Linux/macOS
   .\bin\sfml-app.exe  # Windows
   ```

### SFML Installation

#### Windows
- Download SFML from [sfml-dev.org](https://www.sfml-dev.org/download.php)
- Extract to a directory and set `SFML_DIR` environment variable
- Or use vcpkg: `vcpkg install sfml`

#### macOS
```bash
brew install sfml
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsfml-dev
```

#### Linux (Fedora)
```bash
sudo dnf install SFML-devel
```

## 🎯 Usage

### Controls

- **Mouse**: Navigate and click on game cards
- **Space**: Cycle through background patterns
- **Escape**: Exit application or return to previous state
- **Enter**: Reset game (when game is over)

### Navigation

1. **Main Menu**: Select games from the interactive card interface
2. **Game State**: Play the selected game with full-screen interface
3. **Return**: Use Escape key or back button to return to main menu

### Adding New Games

1. **Create game class** implementing `IGame` interface
2. **Add game card** in `MainMenuState::setupGameCards()`
3. **Implement game logic** following the established patterns
4. **Add assets** to the `assets/` directory

## 🔧 Development

### Project Structure

```
sfml-xo/
├── assets/                 # Game assets (fonts, images)
├── include/               # Header files
│   ├── constants/        # Configuration constants
│   ├── core/            # Core application classes
│   ├── games/           # Game interfaces and implementations
│   ├── states/          # Application states
│   └── ui/              # User interface components
├── src/                  # Source files
│   ├── core/            # Core implementation
│   ├── games/           # Game implementations
│   ├── states/          # State implementations
│   └── ui/              # UI implementations
├── CMakeLists.txt        # Build configuration
└── README.md            # This file
```

### Code Style

- **Naming**: camelCase for variables, PascalCase for classes
- **Headers**: Include guards with `#pragma once`
- **Namespaces**: Constants organized in namespaces
- **Memory**: Smart pointers for automatic resource management
- **Error Handling**: Graceful fallbacks and informative console output

### Building for Development

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

# With specific compiler
cmake -DCMAKE_CXX_COMPILER=g++-10 ..
```

### Testing

- **Manual Testing**: Run the application and test all features
- **Debug Output**: Console logging for state transitions and game events
- **Asset Validation**: Automatic fallback for missing assets

## 🌟 Future Enhancements

### Planned Features
- **Additional Games**: Chess, Checkers, Connect Four
- **Multiplayer Support**: Network-based gameplay
- **Save/Load System**: Game state persistence
- **Settings Menu**: Customizable UI and game options
- **Sound Effects**: Audio feedback and background music
- **Achievements**: Progress tracking and unlockables

### Technical Improvements
- **Shader Support**: Advanced visual effects
- **Mobile Support**: Touch interface optimization
- **Web Assembly**: Browser-based deployment
- **Plugin System**: Dynamic game loading

## 🤝 Contributing

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/new-game`
3. **Implement your changes** following the established patterns
4. **Test thoroughly** with different SFML versions
5. **Submit a pull request** with detailed description

### Development Guidelines

- **Follow existing code style** and architecture patterns
- **Add appropriate constants** to the constants files
- **Update documentation** for new features
- **Test on multiple platforms** when possible
- **Use meaningful commit messages**

## 📝 License

This project is open source. Please check the license file for specific terms.

## 🙏 Acknowledgments

- **SFML Team**: For the excellent multimedia library
- **CMake Community**: For the robust build system
- **Open Source Contributors**: For inspiration and best practices

## 📞 Support

- **Issues**: Report bugs and feature requests via GitHub issues
- **Discussions**: Join community discussions for help and ideas
- **Documentation**: Check inline code comments and header files

---

**Built with ❤️ using SFML and modern C++**
