#include <raylib.h>
#include <string>

enum BOARD
{
    BOARD_WIDTH = 10,
    BOARD_HEIGHT = 20,
    CELL_SIZE = 30
};

const int screenWidth = 1200;
const int screenHeight = 800;
const int boardOffsetX = (screenWidth - BOARD_WIDTH * CELL_SIZE) / 2;
const int boardOffsetY = (screenHeight - BOARD_HEIGHT * CELL_SIZE) / 2;

class Map 
{
public:
    void DrawMap() 
    {
        for (int y = 0; y < BOARD_HEIGHT; y++) 
        {
            std::string leftWall = (y == 0) ? "<!" : "<!";
            std::string rightWall = (y == 0) ? "!>" : "!>";
            
            DrawText(leftWall.c_str(), boardOffsetX - CELL_SIZE, boardOffsetY + y * CELL_SIZE, CELL_SIZE, GREEN);
            DrawText(rightWall.c_str(), boardOffsetX + BOARD_WIDTH * CELL_SIZE, boardOffsetY + y * CELL_SIZE, CELL_SIZE, GREEN);
            
            for (int x = 0; x < BOARD_WIDTH; x++) 
            {
                DrawText(".", boardOffsetX + x * CELL_SIZE + CELL_SIZE / 2, boardOffsetY + y * CELL_SIZE, CELL_SIZE, GREEN);
            }
        }
        
        // Draw bottom
        DrawText("<!=====================!>", boardOffsetX - CELL_SIZE, boardOffsetY + BOARD_HEIGHT * CELL_SIZE, CELL_SIZE, GREEN);
        DrawText(" \\/\\/\\/\\/\\/\\/\\/", boardOffsetX - CELL_SIZE, boardOffsetY + (BOARD_HEIGHT + 1) * CELL_SIZE, CELL_SIZE, GREEN);
    }
};

int main() 
{
    InitWindow(screenWidth, screenHeight, "Tetris 1984");
    SetTargetFPS(60);

    Map gameMap;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLACK);

        gameMap.DrawMap();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}