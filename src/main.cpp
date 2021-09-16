/**
 * Raylib Web Starter
 *
 * This project will be usedd for compiling raylib (v3.7.0) for PLATFORM_WEB and PLATFORM_DESKTOP
 * Copyright (c) 2021 Guasam (@guasam)
 **/

#include "raylib.h"
#include <stdio.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);
Texture2D iconTexture;
int screenWidth = 414; // 414
int screenHeight = 686; // 736
int rotation = 0;
Font font;
float fontSize = 22.0f;
float fontSpacing = 2.0f; // For correct alignement?
Vector2 textSize = { 0.0f, 0.0f };
const char* headText = "HELLO RAYLIB WORLD!";
const char* strictText = "Copyright (c) 2021 Guasam";


#if defined(PLATFORM_WEB)
EM_JS(int, get_canvas_width, (), {
return available_screen_width();
    }
);
EM_JS(int, get_canvas_height, (), {
return available_screen_height();
    }
);
#endif

int get_canvas_width();
int get_canvas_height();


extern "C" {
    int my_add(int a, int b);
}

int my_add(int a, int b) {
    return a + b;
}

int main(void)
{

#if defined(PLATFORM_WEB)
    int canvasWidth = get_canvas_width();
    int canvasHeight = get_canvas_height();

    screenWidth = canvasWidth;
    screenHeight = canvasHeight;

    printf("Checking %d %d", canvasWidth, canvasHeight);
#endif

    InitWindow(screenWidth, screenHeight, "Raylib Web Starter");

    // Load texture (must be after initializing window to get OpenGL Context)
    iconTexture = LoadTexture("resources/icon.png");

    // Load Font
    font = LoadFontEx("resources/NotoSans-Regular.ttf", (int)fontSize, 0, 250);


#if defined(PLATFORM_WEB)
    // Must be after initializing window
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
    UnloadFont(font);

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Draw text 
    textSize = MeasureTextEx(font, headText, fontSize, fontSpacing);
    DrawTextEx(font, headText, Vector2{ (screenWidth - textSize.x) / 2.0f, textSize.y + 20 }, fontSize, fontSpacing, GRAY);
    //DrawRectangleLines((screenWidth - textSize.x) / 2.0f, textSize.y, textSize.x, textSize.y, RED);

    // Draw text
    textSize = MeasureTextEx(font, strictText, fontSize, fontSpacing);
    DrawTextEx(font, strictText, Vector2{ (screenWidth - textSize.x) / 2.0f, screenHeight - textSize.y - 20 }, fontSize, fontSpacing, GRAY);
    //DrawRectangleLines((screenWidth - textSize.x) / 2.0f, screenHeight - textSize.y - 20, textSize.x, textSize.y, RED);

    // Increment rotation
    rotation++;

    // Scale image
    float scale = 0.5f;
    float scaleBig = 0.6f;

    DrawTexturePro(
        iconTexture,
        Rectangle{ 0, 0, (float)iconTexture.width, (float)iconTexture.height },
        Rectangle{ screenWidth / 2.0f, screenHeight / 2.0f, iconTexture.width * scaleBig, iconTexture.height * scaleBig },
        Vector2{ iconTexture.width / 2.0f * scaleBig, iconTexture.height / 2.0f * scaleBig },
        (float)rotation,
        LIGHTGRAY
    );

    DrawTexturePro(
        iconTexture,
        Rectangle{ 0, 0, (float)iconTexture.width, (float)iconTexture.height },
        Rectangle{ screenWidth / 2.0f, screenHeight / 2.0f, iconTexture.width * scale, iconTexture.height * scale },
        Vector2{ iconTexture.width / 2.0f * scale, iconTexture.height / 2.0f * scale },
        -(float)rotation,
        WHITE
    );

    EndDrawing();
}