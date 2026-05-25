#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef INICIO_H
#define INICIO_H

typedef struct {
    Texture2D meteoro;
    Texture2D planeta;
    Texture2D background;
} Assets;

typedef struct {
    float frameTimer;
    float x;
    float y;
} Meteoro;

typedef struct {
    float pontos;
    float x;
    float y;
    Texture2D img;
} Escudo;

typedef struct {
    float dano;
    float x; 
    float y;
    Texture2D img;
    bool verificador;
    float timerBala;
} Bala;

typedef struct {
    float pontos;
    float x;
    float y;
    Texture2D img;
    Bala bala;
    float frameTimer;
} Alien;

typedef struct {
    float pontos;
    float x;
    float y;
    Texture2D img;
    Bala bala;
} Heroi;

typedef struct {
    int tipo;
    float frameTimerCount;
} Tela;

typedef struct {
    Sound somHeroiBala;
    Sound somAlienBala;
    Sound danoAlien;
    Sound danoHeroi;
} Sons;

typedef struct {
    Assets assets;
    Meteoro meteoro;
    Tela tela;
    Escudo escudo[3];
    Alien alien[7];
    Heroi heroi;
    Sons sons;
    int alienQtd;
} Def;

extern Def def;
extern int direcao = 1;
extern int acelerador = 15;

void inicializarVariaveis();
void carregarImagens();
void carregarSons();
void desenharFrames();
void unloadTexture();
void verificarClique();
void spaceInvaders();
void atualizacaoHeroi();
void desenharHeroi();
void movimentarAliens();
void desenharEscudos();
void atualizarImpacto();
void verificaVitoria();
void verificaDerrota();
void atualizarBalaHeroi();
void atualizarBalaAlien();
void loop();

void inicializarVariaveis() {
    char buf[1024];
    getcwd(buf, sizeof(buf));

    char path[1024];
    snprintf(path, sizeof(path), "%s/.local/share/spaceInvaders/assets/imagens", getenv("HOME"));

    direcao = 1;
    acelerador = 15;
    def.tela.frameTimerCount = 0;
    def.meteoro.x = 1050;
    def.meteoro.y = 0;
    def.meteoro.frameTimer = 0;
    def.alienQtd = 7;

    int u = 0;
    for(int i = 0; i < 3; i++) {
        char caminho[1024];
        snprintf(caminho, sizeof(caminho), "%s/escudo_1.png", path);
        def.escudo[i].pontos = 75;
        def.escudo[i].x = u;
        def.escudo[i].y = 300;
        def.escudo[i].img = LoadTexture(caminho); 
        u += 420;
    }

    u = 100;
    for(int i = 0; i < def.alienQtd; i++) {
        char caminhoAlien[1024];
        snprintf(caminhoAlien, sizeof(caminhoAlien), "%s/alien.png", path);
        char caminhoBala[1024];
        snprintf(caminhoBala, sizeof(caminhoBala), "%s/balaA.png", path);
        def.alien[i].pontos = 150;
        def.alien[i].x = u;
        def.alien[i].y = 30;
        def.alien[i].frameTimer = 0;
        def.alien[i].img = LoadTexture(caminhoAlien); 
        def.alien[i].bala.x = 0;
        def.alien[i].bala.y = 0;
        def.alien[i].bala.timerBala = 0;
        def.alien[i].bala.img = LoadTexture(caminhoBala); 
        def.alien[i].bala.verificador = false;
        u += 120;
    }

    char caminhoShip[1024];
    snprintf(caminhoShip, sizeof(caminhoShip), "%s/ship.png", path);
    def.heroi.pontos = 150;
    def.heroi.x = 470;
    def.heroi.y = 550;
    def.heroi.img = LoadTexture(caminhoShip); 

    char caminhoBala[1024];
    snprintf(caminhoBala, sizeof(caminhoBala), "%s/balaH.png", path);
    def.heroi.bala.x = 0;
    def.heroi.bala.y = 0;
    def.heroi.bala.img = LoadTexture(caminhoBala); 
    def.heroi.bala.verificador = false;
}

void carregarImagens() {
    char path[1024];
    snprintf(path, sizeof(path), "%s/.local/share/spaceInvaders/assets/imagens", getenv("HOME"));

    char caminhoMeteoro[1024];
    snprintf(caminhoMeteoro, sizeof(caminhoMeteoro), "%s/meteoro.png", path);

    char caminhoPlaneta[1024];
    snprintf(caminhoPlaneta, sizeof(caminhoPlaneta), "%s/planeta.png", path);

    char caminhoFundo[1024];
    snprintf(caminhoFundo, sizeof(caminhoFundo), "%s/fundo.png", path);

    def.assets.meteoro = LoadTexture(caminhoMeteoro); 
    def.assets.planeta = LoadTexture(caminhoPlaneta); 
    def.assets.background = LoadTexture(caminhoFundo); 
    carregarSons();
}

void carregarSons() {
    char path[1024];
    snprintf(path, sizeof(path), "%s/.local/share/spaceInvaders/assets/sons", getenv("HOME"));

    char caminhoSomH[1024];
    snprintf(caminhoSomH, sizeof(caminhoSomH), "%s/balaH.mp3", path);

    char caminhoSomA[1024];
    snprintf(caminhoSomA, sizeof(caminhoSomA), "%s/balaA.wav", path);

    char caminhoSomGO[1024];
    snprintf(caminhoSomGO, sizeof(caminhoSomGO), "%s/gameover.mp3", path);

    char caminhoSomDano[1024];
    snprintf(caminhoSomDano, sizeof(caminhoSomDano), "%s/danoA.mp3", path);

    def.sons.somHeroiBala = LoadSound(caminhoSomH); 
    def.sons.somAlienBala = LoadSound(caminhoSomA); 
    def.sons.danoHeroi = LoadSound(caminhoSomGO); 
    def.sons.danoAlien = LoadSound(caminhoSomDano); 
}

void unloadTexture() {
    UnloadTexture(def.heroi.img);
    UnloadTexture(def.heroi.bala.img);
    for(int i = 0; i < def.alienQtd; i++) {
        UnloadTexture(def.alien[i].img);
        UnloadTexture(def.alien[i].bala.img);
    }
    for(int i = 0; i < 3; i++) {
        UnloadTexture(def.escudo[i].img);
    }
    UnloadTexture(def.assets.meteoro);
    UnloadTexture(def.assets.planeta);
    UnloadTexture(def.assets.background);
}

void desenharFrames() {
    def.meteoro.frameTimer += GetFrameTime();
    DrawTexture(def.assets.meteoro, def.meteoro.x, def.meteoro.y, WHITE); 
    if(def.meteoro.frameTimer >= 0.5f) {
        if(def.meteoro.y < 0) {
            return;
        }
        def.meteoro.x -= 15;
        def.meteoro.y += 15;
        DrawTexture(def.assets.meteoro, def.meteoro.x, def.meteoro.y, WHITE);
        def.meteoro.frameTimer = 0;
    }
}

void movimentarAliens() {
    def.alien[0].frameTimer += GetFrameTime(); 
    if(def.alien[0].frameTimer >= 0.1f) {
        for(int i = 0; i < def.alienQtd; i++) {
            if(def.alien[i].pontos <= 0) continue;
            def.alien[i].x += direcao * acelerador; 
        }
        for(int i = 0; i < def.alienQtd; i++) {
            if(def.alien[i].pontos <= 0) continue;
            if(def.alien[i].x < 0 || def.alien[i].x > 940) {
                direcao *= -1; 
                break;       
            }
        }
        def.alien[0].frameTimer = 0;
    }
    for(int i = 0; i < def.alienQtd; i++) {
        if(def.alien[i].pontos > 0) DrawTexture(def.alien[i].img, def.alien[i].x, def.alien[i].y, WHITE);
    }
}

void verificarClique() {
    int x = GetMouseX();  
    int y = GetMouseY();  
    if(((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && x >= 455 && x <= 560 && y >= 450 && y <= 475) || IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER) || IsKeyDown(KEY_ENTER)) && def.tela.tipo == 0) {
        inicializarVariaveis();
        def.tela.tipo = 1;
        return;
    } else if((IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER) || IsKeyDown(KEY_ENTER)) && (def.tela.tipo == 2 || def.tela.tipo == 3)) {
        inicializarVariaveis();
        def.tela.tipo = 1;
        return;
    }
}

void atualizarImpacto() {
    for(int i = 0; i < def.alienQtd; i++) {
        if(!def.heroi.bala.verificador) continue;
        if(def.alien[i].pontos <= 0) continue;
        Rectangle balaHeroi = {def.heroi.bala.x, def.heroi.bala.y, 30, 30};
        Rectangle alien = {def.alien[i].x, def.alien[i].y, 60, 30};
        if(CheckCollisionRecs(balaHeroi, alien)) {
            def.alien[i].pontos -= 50;
            if(def.alien[i].pontos <= 0) acelerador += 10;
            verificaVitoria();
            PlaySound(def.sons.danoAlien);
            DrawTexture(def.alien[i].img, def.alien[i].x, def.alien[i].y, BLACK);
            DrawTexture(def.alien[i].img, def.alien[i].x, def.alien[i].y, WHITE);
            DrawTexture(def.alien[i].img, def.alien[i].x, def.alien[i].y, BLACK);
            DrawTexture(def.alien[i].img, def.alien[i].x, def.alien[i].y, WHITE);
            DrawTexture(def.alien[i].img, def.alien[i].x, def.alien[i].y, BLACK);
            def.heroi.bala.verificador = false;
            return;
        }
    }

    for(int i = 0; i < def.alienQtd; i++) {
        if(def.heroi.pontos <= 0) continue;
        if(def.alien[i].pontos <= 0) continue; 
        if(!def.alien[i].bala.verificador) continue;
        Rectangle balaAlien = { def.alien[i].bala.x, def.alien[i].bala.y, 30, 30 };
        Rectangle heroi = { def.heroi.x, def.heroi.y, 60, 30 }; 
        if(CheckCollisionRecs(balaAlien, heroi)) {
            def.heroi.pontos = 0;
            verificaDerrota();
            PlaySound(def.sons.danoHeroi);
            return;
        }
    }

    if(def.heroi.bala.verificador) {
        for(int j = 0; j < 3; j++) {
            if(def.escudo[j].pontos <= 0) continue;
            Rectangle balaHeroi = {def.heroi.bala.x, def.heroi.bala.y, 30, 30};
            Rectangle escudo = { def.escudo[j].x, def.escudo[j].y, 120, 120 };
            if(CheckCollisionRecs(balaHeroi, escudo)) {
                def.escudo[j].pontos -= 25;
                int x = (int)def.escudo[j].pontos;
                char path[1024];
                snprintf(path, sizeof(path), "%s/.local/share/spaceInvaders/assets/imagens", getenv("HOME"));

                char caminhoEscudo1[1024];
                snprintf(caminhoEscudo1, sizeof(caminhoEscudo1), "%s/escudo_1.png", path);

                char caminhoEscudo2[1024];
                snprintf(caminhoEscudo2, sizeof(caminhoEscudo2), "%s/escudo_2.png", path);

                char caminhoEscudo3[1024];
                snprintf(caminhoEscudo3, sizeof(caminhoEscudo3), "%s/escudo_3.png", path);

                switch(x) {
                    case 50: def.escudo[j].img = LoadTexture(caminhoEscudo2); break;
                    case 25: def.escudo[j].img = LoadTexture(caminhoEscudo3); break;
                    default: def.escudo[j].img = LoadTexture(caminhoEscudo1); break;
                }
                def.heroi.bala.verificador = false;
                return;
            }
        }
    }

    for(int i = 0; i < def.alienQtd; i++) {
        if(!def.alien[i].bala.verificador) continue;
        if(def.alien[i].pontos <= 0) continue;
        for(int j = 0; j < 3; j++) {
            if(def.escudo[j].pontos <= 0) continue;
            Rectangle balaAlien = { def.alien[i].bala.x, def.alien[i].bala.y, 30, 30 };
            Rectangle escudo = { def.escudo[j].x, def.escudo[j].y, 120, 120 };
            if(CheckCollisionRecs(balaAlien, escudo)) {
                def.escudo[j].pontos -= 25;
                int x = (int)def.escudo[j].pontos;
                char path[1024];
                snprintf(path, sizeof(path), "%s/.local/share/spaceInvaders/assets/imagens", getenv("HOME"));

                char caminhoEscudo1[1024];
                snprintf(caminhoEscudo1, sizeof(caminhoEscudo1), "%s/escudo_1.png", path);

                char caminhoEscudo2[1024];
                snprintf(caminhoEscudo2, sizeof(caminhoEscudo2), "%s/escudo_2.png", path);

                char caminhoEscudo3[1024];
                snprintf(caminhoEscudo3, sizeof(caminhoEscudo3), "%s/escudo_3.png", path);

                switch(x) {
                    case 50: def.escudo[j].img = LoadTexture(caminhoEscudo2); break;
                    case 25: def.escudo[j].img = LoadTexture(caminhoEscudo3); break;
                    default: def.escudo[j].img = LoadTexture(caminhoEscudo1); break;
                }
                def.alien[i].bala.verificador = false;
                return;
            }
        }
    }
}

void verificaVitoria() {
    int count = 0;
    for(int i = 0; i < def.alienQtd; i++) {
        if(def.alien[i].pontos <= 0) count++; 
    }
    if(count == def.alienQtd) {
        def.tela.tipo = 2;
    }
}

void verificaDerrota() {
    if(def.heroi.pontos <= 0) {
        def.tela.tipo = 3;
    }
}

void atualizarBalaHeroi() {
    if(def.heroi.bala.verificador) {
        DrawTexture(def.heroi.bala.img, def.heroi.bala.x, def.heroi.bala.y, WHITE); 
        def.heroi.bala.y -= 10;
        if(def.heroi.bala.y <= 0) {
            def.heroi.bala.verificador = false;
        }
    }
}

void atualizarBalaAlien() {
    for(int i = 0; i < def.alienQtd; i++) {
        if(def.alien[i].pontos <= 0) continue;
        def.alien[i].bala.timerBala += GetFrameTime();
        if(def.alien[i].bala.timerBala >= 0.2f && !def.alien[i].bala.verificador) {
            def.alien[i].bala.x = def.alien[i].x + 15;
            def.alien[i].bala.y = def.alien[i].y + 25;
            def.alien[i].bala.verificador = true;
            def.alien[i].bala.timerBala = 0;
            PlaySound(def.sons.somAlienBala);
        } if(def.alien[i].bala.verificador) {
            DrawTexture(def.alien[i].bala.img, def.alien[i].bala.x, def.alien[i].bala.y, WHITE); 
            def.alien[i].bala.y += 10;
            if(def.alien[i].bala.y >= 600) {
                def.alien[i].bala.verificador = false;
            }
        }
    }
}

void desenharHeroi() {
    if(def.heroi.pontos > 0) DrawTexture(def.heroi.img, def.heroi.x, def.heroi.y, WHITE); 
}

void desenharEscudos() {
    for(int i = 0; i < 3; i++) {
        if(def.escudo[i].pontos > 0) DrawTexture(def.escudo[i].img, def.escudo[i].x, def.escudo[i].y, WHITE); 
    }
}

void atualizacaoHeroi() {
    if((IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT) || IsKeyDown(KEY_LEFT)) && def.heroi.x > 0) {
        def.heroi.x -= 10;
    } if((IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) && def.heroi.x < 940) {
        def.heroi.x += 10;
    } if((IsKeyPressed(KEY_SPACE) || IsKeyPressedRepeat(KEY_SPACE) || IsKeyDown(KEY_SPACE)) && !def.heroi.bala.verificador) {
        def.heroi.bala.x = def.heroi.x + 13;
        def.heroi.bala.y = def.heroi.y - 25;
        PlaySound(def.sons.somHeroiBala);
        def.heroi.bala.verificador = true;
    }
}

void spaceInvaders() {
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(def.assets.background, 0, 0, WHITE); 
        movimentarAliens();
        desenharEscudos();
        desenharHeroi();
        atualizacaoHeroi();
        atualizarBalaHeroi();
        atualizarBalaAlien();
        atualizarImpacto();
    EndDrawing();
}

void loop() {
    verificarClique();
    if(def.tela.tipo == 1) {
        spaceInvaders();
        return;
    } else if(def.tela.tipo == 2) {
        ClearBackground(WHITE);
        DrawTexture(def.assets.background, 0, 0, WHITE); 
        DrawText("Vitória", (1000 - MeasureText("vitoria", 85)) / 2, 105, 85, GREEN);
        DrawText("Jogar Novamente", (1000 - MeasureText("Jogar Novamente", 20)) / 2, 490, 20, WHITE);
        def.tela.frameTimerCount += GetFrameTime();
        if(def.tela.frameTimerCount >= 1.0f) {
            DrawText("Jogar Novamente", (1000 - MeasureText("Jogar Novamente", 20)) / 2, 490, 20, BLACK);
            if(def.tela.frameTimerCount >= 1.5f) {
                def.tela.frameTimerCount = 0;
            }
        }
        verificarClique();
        return;
    } else if(def.tela.tipo == 3) {
        ClearBackground(BLACK);
        DrawTexture(def.assets.background, 0, 0, WHITE); 
        DrawText("GAME OVER", (1000 - MeasureText("GAME OVER", 70)) / 2, 105, 70, RED);
        DrawText("Jogar Novamente", (1000 - MeasureText("Jogar Novamente", 20)) / 2, 490, 20, WHITE);
        def.tela.frameTimerCount += GetFrameTime();
        if(def.tela.frameTimerCount >= 2.0f) {
            DrawText("Jogar Novamente", (1000 - MeasureText("Jogar Novamente", 20)) / 2, 490, 20, BLACK);
            if(def.tela.frameTimerCount >= 3.0f) {
                def.tela.frameTimerCount = 0;
            }
        }
        verificarClique();
        return;
    } 
    DrawTexture(def.assets.background, 0, 0, WHITE); 
    desenharFrames();
    DrawTexture(def.assets.planeta, 700, 350, WHITE); 
    DrawText("Space Invaders", (1000 - MeasureText("Space Invaders", 70)) / 2, 0, 70, GREEN);
    DrawText("Space Invaders", (1000 - MeasureText("Space Invaders", 70)) / 2, 7, 70, WHITE);
    DrawText("Novo jogo", (1000 - MeasureText("Novo jogo", 23)) / 2, 450, 23, WHITE);
}

#endif