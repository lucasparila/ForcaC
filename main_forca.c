#include "forca.h"
#include "T_stack.h"
#include "LinkedList.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 26
#define TAMANHO_MAX_BANCO 100
#define TAMANHO_PALAVRA 20

void mensagem_inicio_jogadorvsmaquina() {
    printf("                                   *** MODO JOGADOR VS MAQUINA ***\n\n");
    printf("                                           Prepare-se!\n\n");
    printf("                      Quanto mais palavras voce acertar, maior eh a sua pontuacao\n."); 
    printf("                               Se nao acertar a palavra eh Fim de Jogo!\n\n\n");
    printf("                                    Pressione ENTER para continuar...");
    getchar();
}

void mensagem_apos_acertar_palavra() {
    printf("Pressione ENTER para advinhar a proxima palavra...");
    getchar();
}

void  mensagem_apos_errar_palavra(){
    printf("Enforcado!\n");
    printf("Pressione ENTER para continuar...");
    getchar();
}

void tela_inicio() {
    printf("\n");
    printf("                        ________\n");
    printf("                       |        |\n");
    printf("                       |        O\n");
    printf("             FORCA C   |       /|\\\n");
    printf("                       |       / \\\n");
    printf("                       |\n");
    printf("                    ________\n");
    
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// Função para limpar a tela e deixar o jogo mais limpo e estático
void limpa_tela() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Para Windows
    #else
        system("clear"); // Para Linux/MacOS
    #endif
}

// Função para capturar a palavra sem exibir no terminal
void capturarPalavra(char* palavra, int max) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < max - 1) { // '\r' é Enter
        if (ch == '\b' && i > 0) { // '\b' é Backspace
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            palavra[i] = ch;
            printf("*"); 
            i++;
        }
    } 
    palavra[i] = '\0'; // Termina a string
    printf("\n");
}

// Função para validação de entrada do menu
int valida_opcao() {
    int opcao;
    printf("Escolha uma opção válida (1-3 ou 0 para sair): ");
    while (scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 3) {
        printf("Opção inválida. Tente novamente: ");
        while (getchar() != '\n'); // Limpa o buffer
    }
    return opcao;
}

// Função para carregar as palavras e dicas de um arquivo TXT
void carregar_palavras(T_Stack stack, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    T_Info temp;
    int count = 0;
    while (fscanf(file, "%s %s", temp.palavra, temp.dica) == 2 && count < MAX) {
        push(stack, temp); // Empilhar a palavra e dica
        count++;
    }

    fclose(file);
}

// Função para o modo Jogador vs Jogador. Define três rodadas por jogo para cada jogador. 
void modo_jogador_vs_jogador() {
    char palavra[MAX];
    char dica[MAX];
    T_jogo jogo = NULL;

    for (int rodadas = 0; rodadas < 6; rodadas++) {
        if (jogo != NULL) {
            destroi(jogo);
        }
        if(getchar()){
            limpa_tela();
            printf("\nRodada %d\n", rodadas + 1);
            printf("Digite a palavra secreta da rodada %d:\n", rodadas + 1);
            capturarPalavra(palavra, MAX);

            printf("Digite a dica para a palavra secreta:\n");
            scanf("%s", dica);
            jogo = create(palavra, dica);
            printf("Pressione ENTER para continuar...");
        }
        
        if(getchar()){
            limpa_tela();
            do {
                printf("                              DICA: %s\n", getDica(jogo));
                desenhar_forca(jogo);
                recebe_palpite(jogo);
                limpa_tela();
            } while (!jogo_ganho(jogo) && !jogo_perdido(jogo));
            limpa_tela();
            desenhar_forca(jogo);
            imprime_resultado_final(jogo);
            if(jogo_ganho(jogo)){
                mensagem_apos_acertar_palavra();         
            }else{
                mensagem_apos_errar_palavra();
            }
        }
    }
    if (jogo != NULL) {
        destroi(jogo);
    }
}

void modo_jogador_vs_maquina(T_Stack fila_jogo, List ranking) {
    char palavra[MAX];
    char dica[MAX];
    int score = 0;
    char nome[7];
    T_jogo jogo = NULL;
    limpa_tela();
    mensagem_inicio_jogadorvsmaquina();
    if(getchar()){
        do {
            T_Info temporario;
            pop(fila_jogo, &temporario);
            jogo = create(temporario.palavra, temporario.dica);
            do {
                limpa_tela();
                printf("                              DICA: %s\n", getDica(jogo));
                desenhar_forca(jogo);
                recebe_palpite(jogo);
            } while (!jogo_ganho(jogo) && !jogo_perdido(jogo));
            limpa_tela();
            desenhar_forca(jogo);
            imprime_resultado_final(jogo);
            if(jogo_ganho(jogo)){
                mensagem_apos_acertar_palavra();
                score += 1;
            }else{
                mensagem_apos_errar_palavra();
            }
            if(getchar()){
                limpa_tela();
            }
            
        } while (!jogo_perdido(jogo));
        limpa_tela();
        printf("Digite seu nome para entrar no Ranking:\n (máx 5 caracteres...)\n");
        scanf("%s", nome);
        insertList(ranking, nome, score);
        getchar();
        printf("Pressione ENTER para continuar...");
        if(getchar()){
            limpa_tela();
            printf("Para ver o Ranking, selecione a opção  no menu inicial.\n");
        }
        if(getchar()){
            printf("Retornando ao Menu Princiapl.\n");
            limpa_tela();
        }
        
    
        if (jogo != NULL) {
            destroi(jogo);
        }

    }
    
}

int main() {
    const char *filename = "BancoDeDados.txt";
    tela_inicio();
    limpa_tela();
    T_Stack fila_jogo = init(TAMANHO_MAX_BANCO);
    carregar_palavras(fila_jogo, filename);
    int opcoes;
    List ranking = createList();
    if(getchar()){
        do {
            printf("\n1- JOGADOR VS JOGADOR\n2- JOGADOR VS MAQUINA\n3- RANKING\n0- SAIR DO JOGO\n");
            opcoes = valida_opcao();
            switch (opcoes) {
            case 1:
                modo_jogador_vs_jogador();
                break;
            case 2:
                modo_jogador_vs_maquina(fila_jogo, ranking);
                break;
            case 3:
                getchar();
                limpa_tela();
                printRanking(ranking);
                printf("Pressione ENTER para voltar ao menu principal...");
                if(getchar()){
                    limpa_tela();
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            }
        } while (opcoes != 0);
        return 0;

    }
   
}