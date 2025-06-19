#pragma once

namespace ApplicationConstants {
    // Window settings
    namespace Window {
        constexpr float DEFAULT_WIDTH = 800;
        constexpr float DEFAULT_HEIGHT = 600;
        constexpr float FRAMERATE_LIMIT = 60;
        constexpr char TITLE[] = "Multi-Player Games Collection";
    }
    
    // UI Layout
    namespace UI {
        constexpr float TITLE_Y_POSITION = 40.0f;
        constexpr int TITLE_FONT_SIZE = 42;
        constexpr float TITLE_OUTLINE_THICKNESS = 2.0f;
        
        constexpr float GAME_AREA_X = 50.0f;
        constexpr float GAME_AREA_Y = 120.0f;
        constexpr float GAME_AREA_WIDTH = 700.0f;
        constexpr float GAME_AREA_HEIGHT = 400.0f;
        constexpr float GAME_AREA_OUTLINE_THICKNESS = 2.0f;
        constexpr int GAME_AREA_BACKGROUND_ALPHA = 100;
        constexpr int GAME_AREA_OUTLINE_ALPHA = 180;
        
        constexpr int INSTRUCTION_FONT_SIZE = 18;
        constexpr float INSTRUCTION_OUTLINE_THICKNESS = 1.0f;
        constexpr int INSTRUCTION_TEXT_ALPHA = 255;
        
        constexpr char INSTRUCTION_TEXT[] = "Game cards will appear here\nPress SPACE to change background pattern";
    }
    
    // Color values
    namespace Colors {
        constexpr int WHITE_R = 255;
        constexpr int WHITE_G = 255;
        constexpr int WHITE_B = 255;
        constexpr int WHITE_A = 255;
        
        constexpr int BLACK_R = 0;
        constexpr int BLACK_G = 0;
        constexpr int BLACK_B = 0;
        constexpr int BLACK_A = 255;
        
        constexpr int GAME_AREA_OUTLINE_R = 100;
        constexpr int GAME_AREA_OUTLINE_G = 150;
        constexpr int GAME_AREA_OUTLINE_B = 200;
        
        constexpr int INSTRUCTION_TEXT_R = 220;
        constexpr int INSTRUCTION_TEXT_G = 220;
        constexpr int INSTRUCTION_TEXT_B = 220;
    }
    
    // File paths
    namespace Paths {
        constexpr char FONT_JERSEY15[] = "assets/fonts/Jersey15-Regular.ttf";
    }
}
