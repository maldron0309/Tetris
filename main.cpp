#include <raylib.h>
#include <string>
#include "raymath.h"

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
            std::string leftWall = "<!";
            std::string rightWall = "!>";

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

class Block
{
private:
    int block[4][4];
    int posX, posY;
    double lastMoveTime, lastHorizontalMoveTime;
    double moveDelay, horizontalMoveDelay;

    int OBlock[4][4] =
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
    };

    int IBlock[4][4] =
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
    };

    int TBlock[4][4] =
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0},
    };

    int JBlock[4][4] =
        {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0},
    };

    int LBlock[4][4] =
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
    };

    int SBlock[4][4] =
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
    };

    int ZBlock[4][4] =
        {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
    };

public:
    Block(int blockType)
    {
        if (blockType == -1)
            blockType = GetRandomValue(0, 6);

        switch (blockType)
        {
        case 0:
            memcpy(block, OBlock, sizeof(block));
            break;
        case 1:
            memcpy(block, IBlock, sizeof(block));
            break;
        case 2:
            memcpy(block, TBlock, sizeof(block));
            break;
        case 3:
            memcpy(block, JBlock, sizeof(block));
            break;
        case 4:
            memcpy(block, LBlock, sizeof(block));
            break;
        case 5:
            memcpy(block, SBlock, sizeof(block));
            break;
        case 6:
            memcpy(block, ZBlock, sizeof(block));
            break;
        }

        posX = BOARD_WIDTH / 2;
        posY = -1;
        lastMoveTime = GetTime();
        lastHorizontalMoveTime = GetTime();
        moveDelay = 0.5;
        horizontalMoveDelay = 0.1; // Adjust horizontal speed
    }

    void DrawBlock()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (block[y][x] == 1)
                {
                    int blockX = boardOffsetX + (posX + x) * CELL_SIZE;
                    int blockY = boardOffsetY + (posY + y) * CELL_SIZE;

                    DrawText("[]", blockX, blockY, CELL_SIZE, GREEN);
                }
            }
        }
    }

    void Update()
    {
        double currentTime = GetTime();

        // Move down
        if (currentTime - lastMoveTime >= moveDelay)
        {
            lastMoveTime = currentTime;
            posY++;
            if (posY >= BOARD_HEIGHT - 1)
            {
                posX = BOARD_WIDTH / 2;
                posY = -1;
                return;
            }
        }

        // Move left or right
        if (currentTime - lastHorizontalMoveTime >= horizontalMoveDelay)
        {
            int moveX = 0;
            if (IsKeyDown(KEY_LEFT) && CanMoveLeft()) moveX--;
            if (IsKeyDown(KEY_RIGHT) && CanMoveRight()) moveX++;

            if (moveX != 0)
            {
                posX += moveX;
                lastHorizontalMoveTime = currentTime;
            }
        }
    }

    bool CanMoveLeft()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (block[y][x] == 1 && posX + x - 1 < 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool CanMoveRight()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (block[y][x] == 1 && posX + x + 1 >= BOARD_WIDTH)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    InitWindow(screenWidth, screenHeight, "Tetris 1984");
    SetTargetFPS(60);

    Map map;
    Block block(-1);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        map.DrawMap();
        block.DrawBlock();
        block.Update();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
