# Space Invaders

![C](https://img.shields.io/badge/C-03599C?style=for-the-badge&logo=c&logoColor=white)
![raylib](https://img.shields.io/badge/raylib-black?style=for-the-badge)

## Sobre

Space Invaders é um clássico jogo de tiro em 2D lançado em 1978 pela empresa japonesa Taito. O jogador controla um canhão laser na parte inferior da tela e deve atirar em ondas de naves alienígenas que descem lentamente, enquanto se esconde atrás de escudos destrutíveis.

Nessa versão, o usuário controla uma nave espacial, que deve atirar nos alienígenas na parte superior da tela. A cada inimigo eliminado, a velocidade de movimentação dos aliens é multiplicada.

## Funcionalidades

Clique em "Novo Jogo" ou aperte "Enter" para começar.

![image](./assets/imagens/github/github(1).png)

A nave se movimenta apenas para os lados, use as setas do teclado para se mover e a tecla de espaço para atirar. Cada alien tem 3 vidas, atinja-o três vezes e ele será eliminado.

![image](./assets/imagens/github/github(2).png)

Se uma das balas inimigas te atingir, você perde!

![image](./assets/imagens/github/github(3).gif)

Derrote todos os inimigos e vença o jogo.

![image](./assets/imagens/github/github(4).gif)

## Tecnologias

| Tecnologia | Uso |
|---|---|
| C | Mecânica das funcionalidades do jogo |
| Raylib | Criação visual |

## Como usar? 

> Primeiro, instale as dependências necessárias (se a sua distro for diferente das abaixo, procure na respectiva wiki/fóruns):

```bash
# Ubuntu/Debian
sudo apt install libraylib-dev

# Arch
sudo pacman -S raylib

# Fedora
sudo dnf install raylib-devel
```

> No terminal, rode os seguintes comandos:

```bash
 git clone https://github.com/luizagsoaress/spaceInvaders.git

 cd spaceInvaders

 make install
```

## Run

> Depois da instalação, rode com: 

```bash
 make run
```

