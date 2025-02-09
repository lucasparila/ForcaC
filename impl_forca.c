#include "forca.h"
#define TAMANHO_PALAVRA 20
// lógica jogo
struct jogo {
    char *palavra;
    char *dica;
    char *palpites;
    int tamanho;
    int palpites_indice;
    int erros;
};

T_jogo create(char *text, char *dica) {
    T_jogo str = malloc(sizeof(struct jogo));
    if (str != NULL) {
        str->tamanho = strlen(text);
        str->palavra = malloc(sizeof(char) * (str->tamanho + 1));
        str->palpites = malloc(sizeof(char) * 26);
        str->dica = malloc(sizeof(char) * (strlen(dica) + 1));
        if (str->palavra == NULL || str->palpites == NULL) {
            free(str->palavra);
            free(str->palpites);
            free(str);
            return NULL;
        }
        strcpy(str->palavra, text);
        strcpy(str->dica, dica);
        str->palpites_indice = 0;
        str->erros = 0;
        memset(str->palpites, 0, 26); 
    }
    return str;
}


void recebe_palpite(T_jogo str) {
    char palpite;
    printf("Qual letra? ");
    scanf(" %c", &palpite);
    if(!letra_ja_palpitada(str, palpite)){
         str->palpites[str->palpites_indice] = palpite;
        str->palpites_indice += 1;
        if(!compara_letra_palavra(palpite, str)){
            str->erros +=1;
        }
    }
   
}
char* getDica(T_jogo jogo) {
    return jogo->dica;
}


// Essa funcção percorre a string (palavra secreta da rodada) poição por posição no array para acessar cada letra. Compara cada letra com a letra palpitada pelo jogador, retornando falso caso a letra não exista na palavra e retornando verdadeiro caso exista.
bool compara_letra_palavra(char letra, T_jogo str) {
    bool existe = false;
    for (int j = 0; j < str->tamanho; j++) {
        if (letra == str->palavra[j]) {
            existe = true;
        }
    }
    return existe;
}


bool letra_ja_palpitada(T_jogo str, char letra) {

    for (int j = 0; j < str->palpites_indice; j++) {
        if (str->palpites[j] == letra) {
            return true;
        }
    }
     return false;
}

bool jogo_ganho(T_jogo str) {
    for (int i = 0; i < str->tamanho; i++) {
        if (!letra_ja_palpitada(str, str->palavra[i])) {
            return false;
        }
    }
    return true;
}

bool jogo_perdido(T_jogo str) {
    return str->erros == 6;
}

void desenhar_forca(T_jogo str) {
    char palavra_secreta[str->tamanho + 1];
    for (int i = 0; i < str->tamanho; i++) {
        if (letra_ja_palpitada(str, str->palavra[i])) {
            palavra_secreta[i] = str->palavra[i];
        } else {
            palavra_secreta[i] = '_';
        }
    }
    palavra_secreta[str->tamanho] = '\0';
    printf("                                                                   _______       \n");
    printf("                                                                  |/      |      \n");
    printf("                                                                  |      %c%c%c   \n", (str->erros >= 1 ? '(' : ' '), (str->erros >= 1 ? '_' : ' '), (str->erros >= 1 ? ')' : ' '));
    printf("                                                                  |      %c%c%c   \n", (str->erros >= 3 ? '\\' : ' '), (str->erros >= 2 ? '|' : ' '), (str->erros >= 4 ? '/' : ' '));
    printf("                                                                  |       %c     \n", (str->erros >= 2 ? '|' : ' '));
    printf("                                                                  |      %c  %c   \n", (str->erros >= 5 ? '/' : ' '), (str->erros >= 6 ? '\\' : ' '));
    printf("                                                                  |              \n");
    printf("                                                                  | %s           \n", palavra_secreta);
    printf("\n\n");
}


void destroi(T_jogo str) {
    if (str != NULL) {
        free(str->palavra);
        free(str->palpites);
        free(str->dica);
        free(str);
    }
}
void imprime_resultado_final(T_jogo str){
     if(jogo_ganho(str)) {
        printf("\nVocê adivinhou a palavrava Secreta! Parabens!\n\n");
        
    } else {
        printf("Voce foi enforcado! A palavra era: %s\n", str->palavra);
    }
}


    