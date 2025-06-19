#pragma once

namespace ScrollableContentAreaConstants {
    // Scrolling parameters
    constexpr float DEFAULT_SCROLL_SPEED = 30.0f;
    constexpr float INITIAL_SCROLL_OFFSET = 0.0f;
    constexpr float INITIAL_MAX_SCROLL_OFFSET = 0.0f;
    constexpr float INITIAL_TOTAL_CONTENT_HEIGHT = 0.0f;
    
    // Grid layout
    constexpr int INITIAL_CARDS_PER_ROW = 1;
    constexpr float DEFAULT_CARD_SPACING = 25.0f;
    constexpr float SPACING_MULTIPLIER = 2.0f; // For padding calculations
    constexpr int MIN_CARDS_PER_ROW = 1;
    
    // Visibility and bounds
    constexpr float BOUNDS_TOLERANCE = 0.0f;
    
    // Debug messages
    constexpr char DEBUG_NO_CARDS[] = "No cards to layout";
    constexpr char DEBUG_GRID_LAYOUT[] = "Grid Layout Debug:";
    constexpr char DEBUG_AVAILABLE_WIDTH[] = "  Available width: ";
    constexpr char DEBUG_CARD_WIDTH[] = "  Card width: ";
    constexpr char DEBUG_CARDS_PER_ROW[] = "  Cards per row: ";
    constexpr char DEBUG_TOTAL_CARDS[] = "  Total cards: ";
    constexpr char DEBUG_ROWS[] = "  Rows: ";
    constexpr char DEBUG_TOTAL_HEIGHT[] = "  Total content height: ";
    constexpr char DEBUG_CARD_POSITION[] = "  Card ";
    constexpr char DEBUG_ROW_COL[] = ": row=";
    constexpr char DEBUG_COL_POS[] = ", col=";
    constexpr char DEBUG_POSITION[] = ", pos=(";
    constexpr char DEBUG_RENDERING[] = "Rendering ";
    constexpr char DEBUG_OUT_OF[] = " out of ";
    constexpr char DEBUG_CARDS[] = " cards";
}
