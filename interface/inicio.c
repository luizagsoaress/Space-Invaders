#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "inicio.h"

int main(void) {
    const int telaLargura = 1000;
    const int telaAltura = 600;

    InitWindow(telaLargura, telaAltura, "space invaders");

    InitAudioDevice();

    Def def;

    SetTargetFPS(60);     
    
    inicializarVariaveis();
    carregarImagens();

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(BLACK);
            loop();

        EndDrawing();
    }

    unloadTexture();

    CloseAudioDevice(); 

    CloseWindow();      

    return 0;
}