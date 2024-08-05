#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define ARRAY_SIZE 50
#define MAX_VALUE 100

typedef struct {
    int value;
    Color color;
} Element;

Element elements[ARRAY_SIZE];
Camera3D camera = { 0 };

void InitializeElements() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        elements[i].value = GetRandomValue(1, MAX_VALUE);
        elements[i].color = WHITE;
    }
}

void DrawElements() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        DrawCube((Vector3){ i * 3.0f - (ARRAY_SIZE - 1) * 1.5f, elements[i].value, 0 },
                 2.0f, elements[i].value * 2.0f, 2.0f, elements[i].color);
        DrawCubeWires((Vector3){ i * 3.0f - (ARRAY_SIZE - 1) * 1.5f, elements[i].value, 0 },
                      2.0f, elements[i].value * 2.0f, 2.0f, BLACK);
    }
}

void BubbleSort() {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
            elements[j].color = RED;
            elements[j+1].color = RED;
            
            if (elements[j].value > elements[j+1].value) {
                Element temp = elements[j];
                elements[j] = elements[j+1];
                elements[j+1] = temp;
            }
            
            BeginDrawing();
                ClearBackground(RAYWHITE);
                BeginMode3D(camera);
                    DrawElements();
                EndMode3D();
                DrawFPS(10, 10);
                DrawText("Bubble Sort in progress...", 10, 40, 20, BLACK);
            EndDrawing();
            
            elements[j].color = WHITE;
            elements[j+1].color = WHITE;
        }
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AlgoTerm 3D - Sorting Visualizer");

    camera.position = (Vector3){ 0.0f, 100.0f, 180.0f };  
    camera.target = (Vector3){ 0.0f, 90.0f, 0.0f };  
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    InitializeElements();

    bool sorting = false;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed(KEY_SPACE) && !sorting) {
            sorting = true;
            InitializeElements();  
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawElements();
            EndMode3D();
            
            if (sorting) {
                BubbleSort();
                sorting = false;
            } else {
                DrawText("Press SPACE to start Bubble Sort", 10, 40, 20, BLACK);
            }
            
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}