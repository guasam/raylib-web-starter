/**
 * Raylib Web Starter
 *
 * This project will be usedd for compiling raylib (v3.7.0) for PLATFORM_WEB and PLATFORM_DESKTOP
 * Copyright (c) 2021 Guasam (@guasam)
 **/

#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);
Texture2D iconTexture;
const int screenWidth = 800;
const int screenHeight = 600;
int rotation = 0;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Raylib Web Starter");

    // Load texture (must be after initializing window to get OpenGL Context)
    iconTexture = LoadTexture("resources/icon.png");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else

    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    UnloadTexture(iconTexture);

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Raylib Web Starter", 190, 200, 20, LIGHTGRAY);

    // Increment rotation
    rotation++;

    // Draw icon texture
   /* DrawTexturePro(
        iconTexture,
        Rectangle{ 0.0f, 0.0f, 1000, 1000 },
        Rectangle{ screenWidth / 2, screenHeight / 2, iconTexture.width * 2.0f, iconTexture.height * 2.0f },
        Vector2{ (float)iconTexture.width, (float)iconTexture.height },
        (float)rotation,
        WHITE
    );*/

    float scale = 0.75f;

    DrawTexturePro(
        iconTexture,
        Rectangle{ 0, 0, (float)iconTexture.width, (float)iconTexture.height },
        Rectangle{ screenWidth / 2, screenHeight / 2, (float)iconTexture.width * scale, (float)iconTexture.height * scale },
        Vector2{ (float) iconTexture.width / 2 * scale, (float) iconTexture.height / 2 * scale },
        (float)rotation,
        WHITE
    );

    EndDrawing();
}