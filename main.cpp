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
    const int gravity{1'000};

    // Texture
    Texture2D scarfy = LoadTexture("./textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 2) - (scarfyRec.width / 2);
    scarfyPos.y = (windowHeight / 2) - (scarfyRec.height / 2);

    // animation frame
    int frame{};
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    int velocity{0};
    // jump velocity (pixels/second)
    const int jumpVel{-600};

    SetTargetFPS(60);

   
    while (!WindowShouldClose()) {
        BeginDrawing();

        // deltatime (time since last frame)
        const float dT{GetFrameTime()};

        // Perform ground check
        if (isOnGround(scarfyPos.y, windowHeight - scarfyRec.width)) {
            // rectangle is on the ground
            velocity = 0;
        } else {
            // rectangle is in the air
            // Apply gravity
            velocity += gravity * dT;
        }

        if (IsKeyPressed(KEY_SPACE) && isOnGround(scarfyPos.y, windowHeight - scarfyRec.width)) {
            velocity += jumpVel;    
        }
        // Update Y Positions
        scarfyPos.y += velocity * dT;

        // Update animation frame
        runningTime += dT;
        if (runningTime >= updateTime) {
            runningTime = 0.0;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5) {
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        ClearBackground(WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}