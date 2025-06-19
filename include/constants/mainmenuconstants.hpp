#pragma once

namespace MainMenuConstants {
    // Card dimensions and positioning
    constexpr float CARD_WIDTH = 180.0f;
    constexpr float CARD_HEIGHT = 280.0f;
    constexpr float CARD_POSITION_X = 120.0f;
    constexpr float CARD_POSITION_Y = 200.0f;

    // Instruction text positioning
    constexpr float INSTRUCTION_TEXT_POSITION_X = 800.0f;
    constexpr float INSTRUCTION_TEXT_POSITION_Y = 530.0f;

    // Font sizes
    constexpr int TITLE_FONT_SIZE = 42;
    constexpr int INSTRUCTION_FONT_SIZE = 18;

    // Game area properties
    constexpr float GAME_AREA_POSITION_X = 50.0f;
    constexpr float GAME_AREA_POSITION_Y = 120.0f;
    constexpr float GAME_AREA_WIDTH = 700.0f;
    constexpr float GAME_AREA_HEIGHT = 400.0f;
    constexpr int GAME_AREA_BACKGROUND_ALPHA = 100;
    constexpr int GAME_AREA_OUTLINE_ALPHA = 180;
    constexpr float GAME_AREA_OUTLINE_THICKNESS = 2.0f;

    // Background pattern cycling
    constexpr int PATTERN_COUNT = 4;
    constexpr float PATTERN_SPEEDS[] = {0.2f, 0.5f, 0.7f, 0.8f};

    // Text content
    constexpr char MAIN_TITLE[] = "Multi-Player Games Collection";
    constexpr char INSTRUCTION_TEXT[] = "SPACE: Change Background -- Press ESC to exit";
    constexpr char XO_CARD_TITLE[] = "Tic-Tac-Toe";
    constexpr char XO_CARD_DESCRIPTION[] = "Classic XO game";
    
    // Asset paths
    constexpr char XO_CARD_IMAGE_PATH[] = "assets/images/xo_card.png";
}
