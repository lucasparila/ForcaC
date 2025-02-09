#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct jogo* T_jogo;
T_jogo create(char* text, char* dica);
void destroi(T_jogo str);
bool compara_letra_palavra(char letra, T_jogo str);
bool letra_ja_palpitada(T_jogo str, char letra);
bool jogo_perdido(T_jogo str);
bool jogo_ganho(T_jogo str);
void recebe_palpite(T_jogo str);
void desenhar_forca(T_jogo str);
void imprime_resultado_final(T_jogo str);
char* getDica(T_jogo jogo);
void tela_inicio();