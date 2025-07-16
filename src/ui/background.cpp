#include <ui/backgroundpattern.hpp>
#include <constants/backgroundconstants.hpp>
#include <cmath>

using namespace sf;

// Namespace alias for cleaner code
namespace BgConst = BackgroundConstants;

// Type aliases for SFML version compatibility
#if SFML_VERSION_MAJOR >= 3
    using UInt8Type = std::uint8_t;
    constexpr auto QuadsType = sf::PrimitiveType::Triangles;
    constexpr int VERTICES_PER_QUAD = 6; // 2 triangles = 6 vertices
#else
    using UInt8Type = sf::Uint8;
    constexpr auto QuadsType = sf::Quads;
    constexpr int VERTICES_PER_QUAD = 4; // 1 quad = 4 vertices
#endif

BackgroundPattern::BackgroundPattern(RenderWindow* window, PatternType pattern) 
    : m_window(window), m_currentPattern(pattern), 
      m_pixelSize(BgConst::PixelSize::DEFAULT_SIZE), 
      m_animationSpeed(BgConst::AnimationSpeed::SLOW),
      m_rng(std::random_device{}()), m_randomFloat(0.0f, 1.0f)
{
    
    m_windowSize = m_window->getSize();
    m_primaryColors = getCyberColorScheme();
    m_accentColors = getNeonColorScheme();
    initializePattern();
}

void BackgroundPattern::initializePattern()
{
    int cols = m_windowSize.x / m_pixelSize;
    int rows = m_windowSize.y / m_pixelSize;
    int totalPixels = cols * rows;
    
    m_vertices.setPrimitiveType(QuadsType);
    m_vertices.resize(totalPixels * VERTICES_PER_QUAD);
    
    // Initialize animation data
    m_pixelPhases.resize(totalPixels);
    m_pixelVelocities.resize(totalPixels);
    
    for (int i = 0; i < totalPixels; ++i)
    {
        m_pixelPhases[i] = m_randomFloat(m_rng) * 6.28f; // 2π
        m_pixelVelocities[i] = Vector2f(
            (m_randomFloat(m_rng) - 0.5f) * 50.0f,
            (m_randomFloat(m_rng) - 0.5f) * 50.0f
        );
    }
    
    // Create initial pixel grid
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int pixelIndex = row * cols + col;
            int vertexIndex = pixelIndex * VERTICES_PER_QUAD;
            
            float x = col * m_pixelSize;
            float y = row * m_pixelSize;
            
#if SFML_VERSION_MAJOR >= 3
            // SFML 3.0+ - Convert quad to two triangles
            // Triangle 1: top-left, top-right, bottom-left
            m_vertices[vertexIndex].position = Vector2f(x, y);                              // top-left
            m_vertices[vertexIndex + 1].position = Vector2f(x + m_pixelSize, y);           // top-right
            m_vertices[vertexIndex + 2].position = Vector2f(x, y + m_pixelSize);           // bottom-left
            
            // Triangle 2: top-right, bottom-right, bottom-left
            m_vertices[vertexIndex + 3].position = Vector2f(x + m_pixelSize, y);           // top-right
            m_vertices[vertexIndex + 4].position = Vector2f(x + m_pixelSize, y + m_pixelSize); // bottom-right
            m_vertices[vertexIndex + 5].position = Vector2f(x, y + m_pixelSize);           // bottom-left
#else
            // SFML 2.x - Use quad vertices
            m_vertices[vertexIndex].position = Vector2f(x, y);
            m_vertices[vertexIndex + 1].position = Vector2f(x + m_pixelSize, y);
            m_vertices[vertexIndex + 2].position = Vector2f(x + m_pixelSize, y + m_pixelSize);
            m_vertices[vertexIndex + 3].position = Vector2f(x, y + m_pixelSize);
#endif
        }
    }
}

void BackgroundPattern::updateGridFade()
{
    int cols = m_windowSize.x / m_pixelSize;
    int rows = m_windowSize.y / m_pixelSize;
    float time = m_animationClock.getElapsedTime().asSeconds() * m_animationSpeed;
    
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int pixelIndex = row * cols + col;
            int vertexIndex = pixelIndex * VERTICES_PER_QUAD;
            
            // Use constants with namespace alias
            float wave = std::sin(time + (col * BgConst::GridFade::WAVE_FREQUENCY_X) + (row * BgConst::GridFade::WAVE_FREQUENCY_Y));
            float opacity = (wave + 1.0f) * 0.5f * BgConst::GridFade::OPACITY_MULTIPLIER + BgConst::GridFade::OPACITY_BASE;
            
            Color baseColor = m_primaryColors[pixelIndex % m_primaryColors.size()];
            Color color(baseColor.r, baseColor.g, baseColor.b, static_cast<UInt8Type>(opacity));
            
            if (m_randomFloat(m_rng) < BgConst::GridFade::ACCENT_PROBABILITY) {
                color = m_accentColors[pixelIndex % m_accentColors.size()];
                color.a = static_cast<UInt8Type>(opacity * BgConst::GridFade::ACCENT_OPACITY_MULTIPLIER);
            }
            
            for (int i = 0; i < VERTICES_PER_QUAD; ++i)
                m_vertices[vertexIndex + i].color = color;
        }
    }
}

void BackgroundPattern::updateFloatingPixels()
{
    int cols = m_windowSize.x / m_pixelSize;
    int rows = m_windowSize.y / m_pixelSize;
    float time = m_animationClock.getElapsedTime().asSeconds() * m_animationSpeed;
    
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int pixelIndex = row * cols + col;
            int vertexIndex = pixelIndex * VERTICES_PER_QUAD;
            
            // Use constants with namespace alias
            float floatX = std::sin(time * BgConst::FloatingPixels::FLOAT_FREQUENCY_X + m_pixelPhases[pixelIndex]) * BgConst::FloatingPixels::FLOAT_AMPLITUDE;
            float floatY = std::cos(time * BgConst::FloatingPixels::FLOAT_FREQUENCY_Y + m_pixelPhases[pixelIndex]) * BgConst::FloatingPixels::FLOAT_AMPLITUDE;
            
            float baseX = col * m_pixelSize;
            float baseY = row * m_pixelSize;
            
#if SFML_VERSION_MAJOR >= 3
            // SFML 3.0+ - Update triangle positions
            // Triangle 1: top-left, top-right, bottom-left
            m_vertices[vertexIndex].position = Vector2f(baseX + floatX, baseY + floatY);
            m_vertices[vertexIndex + 1].position = Vector2f(baseX + m_pixelSize + floatX, baseY + floatY);
            m_vertices[vertexIndex + 2].position = Vector2f(baseX + floatX, baseY + m_pixelSize + floatY);
            
            // Triangle 2: top-right, bottom-right, bottom-left
            m_vertices[vertexIndex + 3].position = Vector2f(baseX + m_pixelSize + floatX, baseY + floatY);
            m_vertices[vertexIndex + 4].position = Vector2f(baseX + m_pixelSize + floatX, baseY + m_pixelSize + floatY);
            m_vertices[vertexIndex + 5].position = Vector2f(baseX + floatX, baseY + m_pixelSize + floatY);
#else
            // SFML 2.x - Update quad positions
            m_vertices[vertexIndex].position = Vector2f(baseX + floatX, baseY + floatY);
            m_vertices[vertexIndex + 1].position = Vector2f(baseX + m_pixelSize + floatX, baseY + floatY);
            m_vertices[vertexIndex + 2].position = Vector2f(baseX + m_pixelSize + floatX, baseY + m_pixelSize + floatY);
            m_vertices[vertexIndex + 3].position = Vector2f(baseX + floatX, baseY + m_pixelSize + floatY);
#endif
            
            float pulse = (std::sin(time * BgConst::FloatingPixels::PULSE_FREQUENCY + m_pixelPhases[pixelIndex]) + 1.0f) * 0.5f;
            float opacity = pulse * BgConst::FloatingPixels::OPACITY_MULTIPLIER + BgConst::FloatingPixels::OPACITY_BASE;
            
            Color color = m_primaryColors[pixelIndex % m_primaryColors.size()];
            color.a = static_cast<UInt8Type>(opacity);
            
            for (int i = 0; i < VERTICES_PER_QUAD; ++i)
                m_vertices[vertexIndex + i].color = color;
        }
    }
}

void BackgroundPattern::updateWavePattern()
{
    int cols = m_windowSize.x / m_pixelSize;
    int rows = m_windowSize.y / m_pixelSize;
    float time = m_animationClock.getElapsedTime().asSeconds() * m_animationSpeed;
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int pixelIndex = row * cols + col;
            int vertexIndex = pixelIndex * VERTICES_PER_QUAD;
            
            // Create ripple effect from center using constants
            float centerX = m_windowSize.x * 0.5f;
            float centerY = m_windowSize.y * 0.5f;
            float pixelX = col * m_pixelSize + m_pixelSize * 0.5f;
            float pixelY = row * m_pixelSize + m_pixelSize * 0.5f;
            
            float distance = std::sqrt((pixelX - centerX) * (pixelX - centerX) + 
                                     (pixelY - centerY) * (pixelY - centerY));
            
            float wave = std::sin(distance * BgConst::WavePattern::WAVE_FREQUENCY - time * BgConst::WavePattern::WAVE_SPEED);
            float opacity = (wave + 1.0f) * 0.5f * BgConst::WavePattern::OPACITY_MULTIPLIER + BgConst::WavePattern::OPACITY_BASE;
            
            Color color = (wave > 0) ? m_accentColors[0] : m_primaryColors[0];
            color.a = static_cast<UInt8Type>(opacity);
            
            for (int i = 0; i < VERTICES_PER_QUAD; ++i)
                m_vertices[vertexIndex + i].color = color;
        }
    }
}

void BackgroundPattern::updateMatrixRain()
{
    int cols = m_windowSize.x / m_pixelSize;
    int rows = m_windowSize.y / m_pixelSize;
    float time = m_animationClock.getElapsedTime().asSeconds() * m_animationSpeed;
    
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int pixelIndex = row * cols + col;
            int vertexIndex = pixelIndex * VERTICES_PER_QUAD;
            
            // Use constants with namespace alias for Matrix Rain effect
            float fallSpeed = BgConst::MatrixRain::BASE_FALL_SPEED + (m_pixelPhases[pixelIndex] * BgConst::MatrixRain::SPEED_VARIATION);
            float rainPosition = fmod(time * fallSpeed + m_pixelPhases[pixelIndex] * BgConst::MatrixRain::PHASE_MULTIPLIER, rows + BgConst::MatrixRain::TRAIL_LENGTH);
            
            float distanceFromRain = abs(row - rainPosition);
            
            float intensity = 0.0f;
            if (distanceFromRain < 1.0f)
                intensity = 1.0f;
            else if (distanceFromRain < BgConst::MatrixRain::TRAIL_LENGTH)
                intensity = 1.0f - (distanceFromRain - 1.0f) / BgConst::MatrixRain::TRAIL_FADE_DISTANCE;
            
            float columnVariation = std::sin(col * BgConst::MatrixRain::COLUMN_VARIATION_FREQUENCY + time * BgConst::MatrixRain::COLUMN_VARIATION_SPEED) 
                                  * BgConst::MatrixRain::COLUMN_VARIATION_AMPLITUDE + BgConst::MatrixRain::COLUMN_VARIATION_BASE;
            intensity *= columnVariation;
            
            float opacity = intensity * BgConst::MatrixRain::MAX_OPACITY;
            opacity = std::max(0.0f, std::min(255.0f, opacity));
            
            Color color;
            if (intensity > BgConst::MatrixRain::BRIGHT_THRESHOLD)
                color = Color(BgConst::Colors::MatrixRain::BRIGHT_R, BgConst::Colors::MatrixRain::BRIGHT_G, BgConst::Colors::MatrixRain::BRIGHT_B, static_cast<UInt8Type>(opacity));
            else if (intensity > BgConst::MatrixRain::MEDIUM_THRESHOLD)
                color = Color(BgConst::Colors::MatrixRain::MEDIUM_R, BgConst::Colors::MatrixRain::MEDIUM_G, BgConst::Colors::MatrixRain::MEDIUM_B, static_cast<UInt8Type>(opacity));
            else if (intensity > BgConst::MatrixRain::FADE_THRESHOLD)
                color = Color(BgConst::Colors::MatrixRain::DARK_R, BgConst::Colors::MatrixRain::DARK_G, BgConst::Colors::MatrixRain::DARK_B, static_cast<UInt8Type>(opacity));
            else {
                Color baseColor = m_primaryColors[pixelIndex % m_primaryColors.size()];
                color = Color(baseColor.r, baseColor.g, baseColor.b, BgConst::MatrixRain::BACKGROUND_OPACITY);
            }
            
            if (m_randomFloat(m_rng) < BgConst::MatrixRain::ACCENT_PROBABILITY && intensity > 0.5f)
                color = Color(BgConst::Colors::MatrixRain::ACCENT_R, BgConst::Colors::MatrixRain::ACCENT_G, BgConst::Colors::MatrixRain::ACCENT_B, static_cast<UInt8Type>(opacity));
            
            for (int i = 0; i < VERTICES_PER_QUAD; ++i)
                m_vertices[vertexIndex + i].color = color;
        }
    }
}

void BackgroundPattern::update() {
    switch (m_currentPattern)
    {
        case PatternType::GRID_FADE:
            updateGridFade();
            break;
        case PatternType::FLOATING_PIXELS:
            updateFloatingPixels();
            break;
        case PatternType::WAVE_PATTERN:
            updateWavePattern();
            break;
        case PatternType::MATRIX_RAIN:
            updateMatrixRain();
            break;
        default:
            updateGridFade();
            break;
    }
}

void BackgroundPattern::draw()
{
    m_window->draw(m_vertices);
}

void BackgroundPattern::setPattern(PatternType pattern)
{
    m_currentPattern = pattern;
    initializePattern();
}

void BackgroundPattern::setPixelSize(int size)
{
    m_pixelSize = std::max(BgConst::PixelSize::MIN_SIZE, std::min(BgConst::PixelSize::MAX_SIZE, size));
    initializePattern();
}

void BackgroundPattern::setAnimationSpeed(float speed)
{
    m_animationSpeed = std::max(BgConst::AnimationSpeed::VERY_SLOW, std::min(BgConst::AnimationSpeed::VERY_FAST, speed));
}

void BackgroundPattern::setColorScheme(const std::vector<Color>& primary, const std::vector<Color>& accent)
{
    m_primaryColors = primary;
    m_accentColors = accent;
}

// Static color scheme methods
std::vector<Color> BackgroundPattern::getCyberColorScheme()
{
    return {
        Color(20, 30, 50, 160),
        Color(30, 40, 70, 160),
        Color(40, 50, 90, 160),
        Color(25, 35, 60, 160)
    };
}

std::vector<Color> BackgroundPattern::getRetroColorScheme()
{
    return {
        Color(80, 40, 120, 160),
        Color(120, 40, 80, 160),
        Color(40, 80, 120, 160),
        Color(60, 60, 100, 160)
    };
}

std::vector<Color> BackgroundPattern::getNeonColorScheme()
{
    return {
        Color(0, 255, 150, 180),
        Color(255, 0, 150, 180),
        Color(150, 0, 255, 180),
        Color(0, 150, 255, 180)
    };
}
