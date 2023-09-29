/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

void applyFriction(float *acc, float *vel, float frictionValue){
    const float maxVelFriction = 0.1;
    if (*vel > maxVelFriction){
        *acc = frictionValue*(-1);
    } else if (*vel < (-1)*maxVelFriction){
        *acc = frictionValue;
    } else {
        *acc = 0;
        *vel = 0;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    const int circleSize = 50;

    const float frictionValue = 0.5;
    const float accelerationValue = 0.5;
    const float gravityValue = 1.5;

    Vector2 acceleration = { 0, 0 };
    Vector2 velocity = { 0, 0 };

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            static Vector2 previous;
            previous = ballPosition;

            ballPosition.x = GetMouseX();
            ballPosition.y = GetMouseY();

            velocity.x = (ballPosition.x - previous.x)/2;
            velocity.y = (ballPosition.y - previous.y)/2;
        } else {
            if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){
                acceleration.x = accelerationValue;
            } else if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
                acceleration.x = accelerationValue*(-1);
            } else {
                applyFriction(&acceleration.x, &velocity.x, frictionValue);
            }

            if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)){
                // Add gravity so we can win it to move the ball
                acceleration.y = (accelerationValue + gravityValue)*(-1);
            } else if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) {
                acceleration.y = accelerationValue;
            } else {
                applyFriction(&acceleration.y, &velocity.y, frictionValue);
            }
            // Always include gravity
            acceleration.y += gravityValue;

            velocity.x += acceleration.x/3;
            velocity.y += acceleration.y/3;

            ballPosition.x += velocity.x;
            ballPosition.y += velocity.y;

            if (ballPosition.x < (float)circleSize) {
                ballPosition.x = (float)circleSize;
                velocity.x *= (-1);
                acceleration.x *= (-1);
            }
            if (ballPosition.x > screenWidth - (float)circleSize) {
                ballPosition.x = screenWidth - (float)circleSize;
                velocity.x *= (-1);
                acceleration.x *= (-1);
            }
            if (ballPosition.y < (float)circleSize) {
                ballPosition.y = (float)circleSize;
                velocity.y *= (-1);
                acceleration.y *= (-1);
            }
            if (ballPosition.y > screenHeight - (float)circleSize) {
                ballPosition.y = screenHeight - (float)circleSize;
                velocity.y *= (-1);
                acceleration.y *= (-1);
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ballPosition, circleSize, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
