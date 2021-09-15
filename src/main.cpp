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
Vector2 textSize = { 0.0f, 0.0f };
int fontSize = 20;
int fontSpacing = 2; // For correct alignement?
const char* headText = "Raylib Web Starter";
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

    //screenWidth = a;
    //screenHeight = b;

    //SetWindowSize(screenWidth, screenHeight);

#if defined(PLATFORM_WEB)
    printf("=========================");
#endif
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

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Draw text 
    textSize = MeasureTextEx(GetFontDefault(), headText, fontSize, fontSpacing);
    DrawText(headText, (screenWidth - textSize.x) / 2.0f, textSize.y + 20, fontSize, GRAY);
    //DrawRectangleLines((screenWidth - textSize.x) / 2.0f, textSize.y, textSize.x, textSize.y, RED);

    // Draw text
    textSize = MeasureTextEx(GetFontDefault(), strictText, fontSize, fontSpacing);
    DrawText(strictText, (screenWidth - textSize.x) / 2.0f, screenHeight - textSize.y - 20, fontSize, LIGHTGRAY);
    //DrawRectangleLines((screenWidth - textSize.x) / 2.0f, screenHeight - textSize.y - 20, textSize.x, textSize.y, RED);

    // Increment rotation
    rotation++;

    // Scale image
    float scale = 0.75f;

    DrawTexturePro(
        iconTexture,
        Rectangle{ 0, 0, (float)iconTexture.width, (float)iconTexture.height },
        Rectangle{ screenWidth / 2.0f, screenHeight / 2.0f, iconTexture.width * scale, iconTexture.height * scale },
        Vector2{ iconTexture.width / 2.0f * scale, iconTexture.height / 2.0f * scale },
        (float)rotation,
        WHITE
    );

    EndDrawing();
}