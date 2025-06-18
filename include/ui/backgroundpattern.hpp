#ifndef BACKGROUNDPATTERN_HPP
#define BACKGROUNDPATTERN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

enum class PatternType {
    GRID_FADE,
    FLOATING_PIXELS,
    WAVE_PATTERN,
    MATRIX_RAIN
};

class BackgroundPattern {
private:
    sf::RenderWindow* m_window;
    sf::VertexArray m_vertices;
    sf::Clock m_animationClock;
    
    // Pattern properties
    PatternType m_currentPattern;
    sf::Vector2u m_windowSize;
    int m_pixelSize;
    float m_animationSpeed;
    
    // Color schemes
    std::vector<sf::Color> m_primaryColors;
    std::vector<sf::Color> m_accentColors;
    
    // Animation data
    std::vector<float> m_pixelPhases;
    std::vector<sf::Vector2f> m_pixelVelocities;
    
    // Random number generation
    std::mt19937 m_rng;
    std::uniform_real_distribution<float> m_randomFloat;
    
    // Private methods for different patterns
    void initializePattern();
    void updateGridFade();
    void updateFloatingPixels();
    void updateWavePattern();
    void updateMatrixRain();

public:
    BackgroundPattern(sf::RenderWindow* window, PatternType pattern = PatternType::GRID_FADE);
    ~BackgroundPattern() = default;
    
    // Configuration methods
    void setPattern(PatternType pattern);
    void setPixelSize(int size);
    void setAnimationSpeed(float speed);
    void setColorScheme(const std::vector<sf::Color>& primary, const std::vector<sf::Color>& accent);
    
    // Main methods
    void update();
    void draw();
    
    // Static color scheme presets
    static std::vector<sf::Color> getCyberColorScheme();
    static std::vector<sf::Color> getRetroColorScheme();
    static std::vector<sf::Color> getNeonColorScheme();
};

#endif  // BACKGROUNDPATTERN_HPP
