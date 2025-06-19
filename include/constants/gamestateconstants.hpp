#pragma once

namespace GameStateConstants {
    // UI Layout
    constexpr float STATUS_TEXT_X = 400.0f;
    constexpr float STATUS_TEXT_Y = 540.0f;
    constexpr float BACK_BUTTON_X = 50.0f;
    constexpr float BACK_BUTTON_Y = 50.0f;
    
    // Font sizes
    constexpr int STATUS_FONT_SIZE = 24;
    constexpr int BACK_BUTTON_FONT_SIZE = 18;
    
    // Text content
    constexpr char BACK_BUTTON_TEXT[] = "<-- Back to Menu";
    
    // Debug messages
    constexpr char DEBUG_ENTERED_GAME[] = "Entered Game State: ";
    constexpr char DEBUG_RETURNED_TO_MENU[] = "Returned to Main Menu";
}
