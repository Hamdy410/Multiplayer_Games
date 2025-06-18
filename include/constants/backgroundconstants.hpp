#pragma once

namespace BackgroundConstants {
    // Animation speeds
    namespace AnimationSpeed {
        constexpr float VERY_SLOW = 0.1f;
        constexpr float SLOW = 0.2f;
        constexpr float MEDIUM = 0.5f;
        constexpr float FAST = 0.8f;
        constexpr float VERY_FAST = 1.2f;
        
        // Pattern-specific defaults
        constexpr float GRID_FADE_DEFAULT = 0.2f;
        constexpr float FLOATING_PIXELS_DEFAULT = 0.5f;
        constexpr float WAVE_PATTERN_DEFAULT = 0.7f;
        constexpr float MATRIX_RAIN_DEFAULT = 0.8f;
    }
    
    // Pixel sizes
    namespace PixelSize {
        constexpr int MIN_SIZE = 4;
        constexpr int MAX_SIZE = 32;
        constexpr int DEFAULT_SIZE = 12;
        constexpr int SMALL = 8;
        constexpr int MEDIUM = 12;
        constexpr int LARGE = 16;
        constexpr int EXTRA_LARGE = 24;
    }
    
    // Grid Fade Pattern
    namespace GridFade {
        constexpr float WAVE_FREQUENCY_X = 0.025f;
        constexpr float WAVE_FREQUENCY_Y = 0.025f;
        constexpr float OPACITY_MULTIPLIER = 100.0f;
        constexpr float OPACITY_BASE = 50.0f;
        constexpr float ACCENT_PROBABILITY = 0.001f;
        constexpr float ACCENT_OPACITY_MULTIPLIER = 1.1f;
    }
    
    // Floating Pixels Pattern
    namespace FloatingPixels {
        constexpr float FLOAT_AMPLITUDE = 3.0f;
        constexpr float FLOAT_FREQUENCY_X = 1.0f;
        constexpr float FLOAT_FREQUENCY_Y = 0.7f;
        constexpr float PULSE_FREQUENCY = 2.0f;
        constexpr float OPACITY_MULTIPLIER = 100.0f;
        constexpr float OPACITY_BASE = 60.0f;
    }
    
    // Wave Pattern
    namespace WavePattern {
        constexpr float WAVE_FREQUENCY = 0.02f;
        constexpr float WAVE_SPEED = 3.0f;
        constexpr float OPACITY_MULTIPLIER = 150.0f;
        constexpr float OPACITY_BASE = 50.0f;
    }
    
    // Matrix Rain Pattern
    namespace MatrixRain {
        constexpr float BASE_FALL_SPEED = 2.0f;
        constexpr float SPEED_VARIATION = 3.0f;
        constexpr float PHASE_MULTIPLIER = 10.0f;
        constexpr float TRAIL_LENGTH = 5.0f;
        constexpr float TRAIL_FADE_DISTANCE = 4.0f;
        constexpr float COLUMN_VARIATION_FREQUENCY = 0.5f;
        constexpr float COLUMN_VARIATION_SPEED = 0.3f;
        constexpr float COLUMN_VARIATION_AMPLITUDE = 0.3f;
        constexpr float COLUMN_VARIATION_BASE = 0.7f;
        constexpr float MAX_OPACITY = 200.0f;
        constexpr float ACCENT_PROBABILITY = 0.002f;
        constexpr float BACKGROUND_OPACITY = 30.0f;
        
        // Color thresholds
        constexpr float BRIGHT_THRESHOLD = 0.8f;
        constexpr float MEDIUM_THRESHOLD = 0.3f;
        constexpr float FADE_THRESHOLD = 0.1f;
    }
    
    // Color values
    namespace Colors {
        // Matrix Rain colors
        namespace MatrixRain {
            constexpr int BRIGHT_R = 100;
            constexpr int BRIGHT_G = 255;
            constexpr int BRIGHT_B = 100;
            
            constexpr int MEDIUM_R = 0;
            constexpr int MEDIUM_G = 200;
            constexpr int MEDIUM_B = 50;
            
            constexpr int DARK_R = 0;
            constexpr int DARK_G = 100;
            constexpr int DARK_B = 25;
            
            constexpr int ACCENT_R = 255;
            constexpr int ACCENT_G = 255;
            constexpr int ACCENT_B = 255;
        }
    }
}
