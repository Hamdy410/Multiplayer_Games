# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Planned
- Additional games (Chess, Checkers, Connect Four)
- Multiplayer support
- Save/load system
- Settings menu
- Sound effects and background music
- Achievement system

## [1.0.0] - 2024-12-19

### Added
- Initial release of SFML Multi-Player Games Collection
- Complete Tic-Tac-Toe game implementation
  - Turn-based gameplay (X and O players)
  - Win detection for rows, columns, and diagonals
  - Draw detection
  - Visual win line indicators
  - Game reset functionality
  - Status display
- Modern UI framework with animated background patterns
  - Grid Fade pattern
  - Floating Pixels pattern
  - Wave Pattern
  - Matrix Rain pattern
- Interactive game selection cards
- State management system
  - Main menu state
  - Game state
  - Seamless navigation between states
- Extensible game architecture via `IGame` interface
- Cross-platform CMake build system
- SFML 2.5+ and 3.x compatibility with automatic version detection
- Asset management with fallback handling
- Responsive layout system
- Event-driven architecture

### Technical Features
- Modern C++17 implementation
- Smart pointer memory management
- RAII resource handling
- Comprehensive error handling
- 60 FPS rendering with smooth animations
- Automatic asset copying to build output
- Windows, macOS, and Linux support

## [0.2.0] - 2024-12-15

### Added
- Background pattern system with multiple animation types
- Scrollable content area for game cards
- Game card UI component with hover effects
- State manager for application state handling
- Base state class for common UI elements

### Changed
- Refactored application architecture to use state pattern
- Improved UI layout and positioning system
- Enhanced event handling system

## [0.1.0] - 2024-12-10

### Added
- Basic SFML application structure
- Window management and event handling
- Simple Tic-Tac-Toe game implementation
- Basic UI rendering system

### Changed
- Initial project setup and CMake configuration
- Basic game logic implementation

---

## Version Numbering

- **Major version** (1.0.0): Breaking changes, major new features
- **Minor version** (1.1.0): New features, backward compatible
- **Patch version** (1.0.1): Bug fixes, backward compatible

## Release Types

- **Alpha**: Early development, features incomplete
- **Beta**: Feature complete, testing phase
- **Release Candidate**: Final testing before release
- **Release**: Stable, production-ready version

## Contributing to Changelog

When adding entries to the changelog:

1. **Add entries under [Unreleased]** for upcoming changes
2. **Use clear, concise descriptions** of what changed
3. **Categorize changes** using the standard sections:
   - Added: New features
   - Changed: Changes in existing functionality
   - Deprecated: Soon-to-be removed features
   - Removed: Removed features
   - Fixed: Bug fixes
   - Security: Vulnerability fixes
4. **Include issue numbers** when applicable
5. **Update version numbers** and dates for releases
