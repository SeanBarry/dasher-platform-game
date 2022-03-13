#include "raylib.h"

bool isOnGround(int posY, int groundLevel) {
    return posY >= groundLevel;
}


int main() {
    // Window Dimensions
    const int windowWidth{500};
    const int windowHeight{500};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // Acceleration due to gravity (pixels per frame, per frame)
    const int gravity{1};

    // Rectangle Dimensions
    const int width{50};
    const int height{80};
    int posY{windowHeight - height};
    int velocity{0};
    const int jumpVel{-22};

    SetTargetFPS(60);

   
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Perform ground check
        if (isOnGround(posY, windowHeight - height)) {
            // rectangle is on the ground
            velocity = 0;
        } else {
            // rectangle is in the air
            // Apply gravity
            velocity += gravity;
        }

        if (IsKeyPressed(KEY_SPACE) && isOnGround(posY, windowHeight - height)) {
            velocity += jumpVel;    
        }
        // Update Y Positions
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE); 

        ClearBackground(WHITE);

        EndDrawing();
    }
    CloseWindow();
}