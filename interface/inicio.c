#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "inicio.h"

Def def;

int main(void) {
    const int telaLargura = 1000;
    const int telaAltura = 600;

    InitWindow(telaLargura, telaAltura, "space invaders");

    InitAudioDevice();

    def.tela.tipo = 0;

    char path[1024];
    snprintf(path, sizeof(path), "%s/.local/share/spaceInvaders/assets/sons", getenv("HOME"));
    char caminhoMusicaMenu[1024];
    snprintf(caminhoMusicaMenu, sizeof(caminhoMusicaMenu), "%s/musica.mp3", path);

    Music musicaMenu = LoadMusicStream(caminhoMusicaMenu); 

    SetTargetFPS(60);     
    inicializarVariaveis();
    carregarImagens();

    PlayMusicStream(musicaMenu);

    while (!WindowShouldClose()) {
        if(def.tela.tipo == 0) {
            UpdateMusicStream(musicaMenu);
        }
        BeginDrawing();
            ClearBackground(BLACK);
            loop();
        EndDrawing();
    }

    unloadTexture();
    UnloadMusicStream(musicaMenu);
    CloseAudioDevice(); 

    CloseWindow();      

    return 0;
}