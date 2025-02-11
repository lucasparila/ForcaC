#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_PALAVRA 20

typedef struct T_Info {
    char palavra[TAMANHO_PALAVRA];
    char dica[TAMANHO_PALAVRA];
} T_Info;
typedef struct stack* T_Stack;


void destroy(T_Stack stack);
T_Stack init(int maxsize);
bool isFull(T_Stack stack);
bool isEmpty(T_Stack stack);
bool push(T_Stack stack, T_Info element);
bool pop(T_Stack stack, T_Info* element);

