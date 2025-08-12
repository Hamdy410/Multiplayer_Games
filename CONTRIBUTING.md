# Contributing to SFML Multi-Player Games Collection

Thank you for your interest in contributing to our project! This document provides guidelines and information for contributors.

## 🤝 How to Contribute

### Types of Contributions

We welcome various types of contributions:

- 🎮 **New Games**: Implement new games following the `IGame` interface
- 🐛 **Bug Fixes**: Fix issues and improve stability
- ✨ **Features**: Add new features to existing games or the UI
- 📚 **Documentation**: Improve README, code comments, and guides
- 🎨 **UI/UX**: Enhance the user interface and experience
- 🧪 **Testing**: Add tests and improve test coverage
- 🔧 **Infrastructure**: Improve build system, CI/CD, or development tools

## 🚀 Getting Started

### Prerequisites

- **C++17 compatible compiler**
- **CMake 3.15+**
- **SFML 2.5+ or 3.x**
- **Git**

### Development Setup

1. **Fork the repository**
2. **Clone your fork**
   ```bash
   git clone https://github.com/YOUR_USERNAME/sfml-xo.git
   cd sfml-xo
   ```
3. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```
4. **Set up the development environment**
   ```bash
   mkdir build && cd build
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   cmake --build .
   ```

## 📝 Code Style Guidelines

### C++ Style

- **Naming Convention**:
  - Classes: `PascalCase` (e.g., `GameCard`, `BackgroundPattern`)
  - Variables: `camelCase` (e.g., `m_window`, `m_currentPlayer`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `DEFAULT_WIDTH`, `GRID_MARGIN`)
  - Namespaces: `PascalCase` (e.g., `ApplicationConstants`)

- **File Organization**:
  - Headers: `#pragma once` for include guards
  - Implementation: One class per `.cpp` file
  - Constants: Organized in appropriate namespace files

- **Code Structure**:
  - Use smart pointers (`std::unique_ptr`, `std::shared_ptr`)
  - Prefer `const` references over copying
  - Use `override` keyword for virtual functions
  - Initialize member variables in constructor initialization lists

### Example Code Style

```cpp
class ExampleClass : public BaseClass
{
private:
    std::unique_ptr<SomeObject> m_object;
    sf::Vector2f m_position;
    bool m_isActive;

public:
    ExampleClass(sf::Vector2f position);
    void update(float deltaTime) override;
    bool isActive() const { return m_isActive; }
};
```

## 🎮 Adding New Games

### 1. Create Game Class

Implement the `IGame` interface:

```cpp
#include <games/igame.hpp>

class NewGame : public IGame
{
private:
    // Game-specific members
    sf::Font* m_font;
    bool m_gameOver;
    std::string m_gameStatus;

public:
    NewGame(sf::Font* font);
    
    // Required interface methods
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    
    // Game lifecycle
    void initialize() override;
    void reset() override;
    void cleanup() override;
    
    // Game information
    std::string getGameName() const override { return "New Game"; }
    bool isGameOver() const override { return m_gameOver; }
    std::string getGameStatus() const override { return m_gameStatus; }
};
```

### 2. Add Game Card

Update `MainMenuState::setupGameCards()`:

```cpp
// Create game card
auto card = std::make_unique<GameCard>(
    sf::Vector2f(0, 0),
    sf::Vector2f(MenuConst::CARD_WIDTH, MenuConst::CARD_HEIGHT),
    m_sharedFont
);

card->setTexture(texture.get());
card->setTitle("New Game");
card->setDescription("Description of the new game");
card->setOnClick([this]() {
    auto newGame = std::make_unique<NewGame>(m_sharedFont);
    m_stateManager->pushState(
        std::make_unique<GameState>(m_window, m_stateManager, 
        m_sharedFont, std::move(newGame))
    );
});

m_ScrollableArea->addCard(std::move(card));
```

### 3. Add Constants

Create constants file `include/constants/newgameconstants.hpp`:

```cpp
#pragma once

namespace NewGameConstants {
    constexpr float GAME_MARGIN = 20.0f;
    constexpr int BOARD_SIZE = 8;
    // Add other game-specific constants
}
```

### 4. Add Assets

Place game assets in `assets/images/` and `assets/fonts/` directories.

## 🧪 Testing Guidelines

### Manual Testing

- **Test on multiple platforms** when possible
- **Test with different SFML versions** (2.5+, 3.x)
- **Test edge cases** and error conditions
- **Verify asset loading** and fallback behavior

### Code Quality

- **No compiler warnings** in Debug and Release builds
- **Memory leak free** (use tools like Valgrind, AddressSanitizer)
- **Consistent formatting** (use your IDE's auto-formatting)
- **Clear error messages** and logging

## 📤 Submitting Changes

### Commit Messages

Use clear, descriptive commit messages:

```
feat: add chess game implementation

- Implement chess board and piece movement
- Add win condition detection
- Include chess piece assets
- Update main menu with chess card

Closes #123
```

### Pull Request Process

1. **Ensure your code compiles** without warnings
2. **Test thoroughly** on your local machine
3. **Update documentation** if needed
4. **Create a descriptive PR** with:
   - Clear title describing the change
   - Detailed description of what was changed
   - Screenshots/videos for UI changes
   - Reference to related issues

### PR Review Process

- **Code review** by maintainers
- **Automated checks** must pass
- **Address feedback** promptly
- **Squash commits** if requested

## 🐛 Reporting Issues

### Bug Reports

Include the following information:

- **OS and version**
- **SFML version**
- **Compiler and version**
- **Steps to reproduce**
- **Expected vs actual behavior**
- **Screenshots or error messages**

### Feature Requests

- **Clear description** of the feature
- **Use case** and benefits
- **Mockups** or examples if applicable
- **Priority level** (low/medium/high)

## 📚 Additional Resources

- **SFML Documentation**: [sfml-dev.org](https://www.sfml-dev.org/documentation.php)
- **C++ Reference**: [cppreference.com](https://en.cppreference.com/)
- **CMake Documentation**: [cmake.org](https://cmake.org/documentation/)

## 🏆 Recognition

Contributors will be recognized in:
- **README.md** contributors section
- **GitHub contributors** page
- **Release notes** for significant contributions

## 📞 Questions?

- **GitHub Issues**: For bugs and feature requests
- **GitHub Discussions**: For questions and general discussion
- **Pull Requests**: For code reviews and feedback

Thank you for contributing to our project! 🎉
