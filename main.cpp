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

    // Nebula Variables
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec;
    nebulaRec.width = nebula.width / 8;
    nebulaRec.height = nebula.height / 8;
    nebulaRec.x = windowWidth;
    nebulaRec.y = windowHeight - nebulaRec.height;
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

    // Nebula x velocity (pixels/s)
    int nebVel{-600};

    // Scarfy Variables
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
        // && isOnGround(scarfyPos.y, windowHeight - scarfyRec.width)
        if (IsKeyPressed(KEY_SPACE)) {
            velocity += jumpVel;    
        }
        // Update nebula position
        nebulaPos.x += nebVel * dT;

        // Update scarfy Positions
        scarfyPos.y += velocity * dT;

        if (isOnGround(scarfyPos.y, windowHeight - scarfyRec.width)) {
            // Update animation frame
            runningTime += dT;
            // if enough time has passed and scarfy isn't jumping
            if (runningTime >= updateTime) {
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5) {
                    frame = 0;
                }
            }
        }
        // Draw Nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        ClearBackground(WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}