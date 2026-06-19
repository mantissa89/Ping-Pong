#include "raylib.h"

int main(){
    int screenWidth = 800;
    int screenHeight = 600;

    Vector2 ballPos = {
        .x = 0.5 * screenWidth,
        .y = 0.5 * screenHeight
    };

    Vector2 paddleSize = {
        .x = 15,
        .y = 90
    };

    Vector2 paddleL_X = {
        .x = 10,
        .y = 0.5 * screenHeight - (paddleSize.y / 2)
    };

    Vector2 paddleR_X = {
        .x = screenWidth - 10 - paddleSize.x,
        .y = 0.5 * screenHeight - (paddleSize.y / 2)
    };

    int radius = 10;

    int minHeight = screenHeight - paddleSize.y;
    int maxHeight = (screenHeight - screenHeight) + paddleSize.y;

    InitWindow(screenWidth, screenHeight, "Ping Pong");

    float ballVel = 0.05f;
    float paddleSpeed = 0.1f;

    while (!WindowShouldClose())
    {
        // Establishing Paddle Bounds
        //  -left
        if(paddleL_X.y < 0) paddleL_X.y = 0;
        if(paddleL_X.y > GetScreenHeight() - paddleSize.y) paddleL_X.y = GetScreenHeight() - paddleSize.y;
        //  -right
        if(paddleR_X.y < 0) paddleR_X.y = 0;
        if(paddleR_X.y > GetScreenHeight() - paddleSize.y) paddleR_X.y = GetScreenHeight() - paddleSize.y;
        
        // Paddle Movement
        //  -left
        if(IsKeyDown(KEY_W)) paddleL_X.y -= paddleSpeed;
        if(IsKeyDown(KEY_S)) paddleL_X.y += paddleSpeed;

        //  -right
        if(IsKeyDown(KEY_UP)) paddleR_X.y -= paddleSpeed;
        if(IsKeyDown(KEY_DOWN)) paddleR_X.y += paddleSpeed;


        BeginDrawing();
        // Drawing
        ClearBackground(BLACK);

        DrawCircleV(ballPos, radius, WHITE);
        DrawRectangleV(paddleL_X, paddleSize, WHITE);
        DrawRectangleV(paddleR_X, paddleSize, WHITE);

        EndDrawing();
    }

    while(!WindowShouldClose){
        WaitTime(5);
        ballVel += 0.01;
    }

    CloseWindow();
    return 0;  
}
