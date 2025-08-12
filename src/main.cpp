#include <iostream>

#include "raylib.h"

void test_window() {
    InitWindow(1280, 720, "Test Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    test_window();
    return 0;
}