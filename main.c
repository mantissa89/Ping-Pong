#include "raylib.h"
#include "stdlib.h"

int score_L = 0;
int score_R = 0;

int screenWidth = 600;
int screenHeight = 500;

float ballVel = 0.03f;
float ballYVel = 0.02f;
 
float paddleSpeed = 0.1f;

int main(){

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

    InitWindow(screenWidth, screenHeight, "Ping Pong");

    Rectangle paddleL = {paddleL_X.x, paddleL_X.y, paddleSize.x, paddleSize.y};
    Rectangle paddleR = {paddleR_X.x, paddleR_X.y, paddleSize.x, paddleSize.y};
    

    while (!WindowShouldClose())
    {
        // Ball movement
        ballPos.x += ballVel;
        ballPos.y += ballYVel;

        // Ball-Paddle Collision detection
        if(CheckCollisionCircleRec(ballPos, radius, paddleL) || CheckCollisionCircleRec(ballPos, radius, paddleR)){
            if(ballVel < 0){
                ballVel = 0 - (ballVel - 0.005); 
                ballYVel -= 0.00025;
            } else if(ballVel > 0){
                ballVel = 0 - (ballVel + 0.005);
                ballYVel += 0.00025;
            }
        }
        
        // Establishing Ball Bounds
        //  -bottom
        if(ballPos.y < 0 + radius){
            ballPos.y = 0 + radius;
            ballYVel = 0 - ballYVel;
        }
        //  -top
        if(ballPos.y > GetScreenHeight() - radius){
            ballPos.y = GetScreenHeight() - radius;
            ballYVel = 0 - ballYVel;
        }

        // Score keeping
        if(ballPos.x <= 0 + radius){
            score_R += 1; // a point to the right player
            ballPos.x = 0.5 * screenWidth;
            ballPos.y = 0.5 * screenHeight;
            
            ballVel = 0.03f;
            ballYVel = 0.02f;
            
        } else if (ballPos.x >= GetScreenWidth() - radius){
            score_L += 1; // a point to the left player
            ballPos.x = 0.5 * screenWidth;
            ballPos.y = 0.5 * screenHeight;
            
            ballVel = -0.03f; 
            ballYVel = -0.02f;
        }

        // Establishing Paddle Bounds
        //  -left
        if(paddleL.y < 0) paddleL.y = 0;
        if(paddleL.y > GetScreenHeight() - paddleSize.y) paddleL.y = GetScreenHeight() - paddleSize.y;
        //  -right
        if(paddleR.y < 0) paddleR.y = 0;
        if(paddleR.y > GetScreenHeight() - paddleSize.y) paddleR.y = GetScreenHeight() - paddleSize.y;
        
        // Paddle Movement
        //  -left
        if(IsKeyDown(KEY_W)) paddleL.y -= paddleSpeed;
        if(IsKeyDown(KEY_S)) paddleL.y += paddleSpeed;

        //  -right
        if(IsKeyDown(KEY_UP)) paddleR.y -= paddleSpeed;
        if(IsKeyDown(KEY_DOWN)) paddleR.y += paddleSpeed;



        BeginDrawing();
        // Drawing
        ClearBackground(BLACK);

        // "SCORE BOARD" - vietnamese guy
        //  -left
        DrawText(TextFormat("%i", score_R), screenWidth / 4 * 3, screenHeight / 2 - 32, 64, GRAY);
        //  -right
        DrawText(TextFormat("%i", score_L), screenWidth / 4, screenHeight / 2 - 32, 64, GRAY);
        
        // DEBUG TEXT
        DrawText(TextFormat("Ball x speed: %f", ballVel), 20, screenHeight - 20, 10, GRAY);
        DrawText(TextFormat("Ball y speed: %f", ballYVel), 20, screenHeight - 40, 10, GRAY);

        DrawText(TextFormat("Ball x position: %f", ballPos.x), 20, screenHeight - 80, 10, GRAY);
        DrawText(TextFormat("Ball y position: %f", ballPos.y), 20, screenHeight - 60, 10, GRAY);

        // SHAPES
        DrawCircleV(ballPos, radius, WHITE);
        DrawRectangleRec(paddleL, WHITE);
        DrawRectangleRec(paddleR, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;  
}