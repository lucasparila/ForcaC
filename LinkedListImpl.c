#include "LinkedList.h"
#include "node.h"
#include "stdio.h"

struct node {
    Info name;
    int score;
    struct node *next;
};

struct simple_linked_list {
    NodePtr head;
};

List createList() {
    List list = malloc(sizeof(struct simple_linked_list));
    list->head = NULL;
    return list;
}

void destroyList(List list) {
    NodePtr rip, walker;
    if (list != NULL) {
        rip = list->head;
        while(rip != NULL) {
            walker = getNext(rip);
            destroyNode(rip);
            rip = walker;
        }
        free(list);
    }
}

bool insertList(List list, Info element, int score) {
    NodePtr node, walker;
    bool result = false;

    if (list != NULL) {
        node = createNode();
        setInfo(node, element);
        setNext(node, NULL);
        setScore(node, score);

        walker = list->head;

        if (isEmptyList(list) || node->score > walker->score) {
            insertAtBeginning(list, element, score);
        } else {

            NodePtr caramelo = list->head;
            walker = getNext(walker);

            while (walker != NULL && !result) {

                if(node->score > walker->score){
                    result = true;
                }else{
                    caramelo = walker;
                    walker = getNext(walker);
                }
                
            }
            setNext(node, walker);
            setNext(caramelo, node);
            
        }
        result = true;
    }
    return result;
}

bool insertAtBeginning(List list, Info element, int score){
    NodePtr node;
    bool result = false;

    if (list != NULL) {
        NodePtr node = createNode();
        setInfo(node, element);
        setScore(node, score);
        setNext(node, NULL);

        if (isEmptyList(list)) {
            list->head = node;
            result = true;
        } else {
            setNext(node, list->head);
            list->head = node;
        }
        result = true;
    }
    return result;
}

Info getInfoAt(List list, int position) {
    NodePtr walker;
    int counter;

    if (list != NULL) {
        if (position >= 0 && !isEmptyList(list)){
            walker = list->head;
            counter = 0;

            while (counter < position && getNext(walker) != NULL) {
                walker = getNext(walker);
                counter += 1;
            }

            if (counter == position) {
                return getInfo(walker);
            }
        }
    }
    return NULL;
}

bool isEmptyList(List list) {
    bool result = true;
    if (list != NULL) {
        if (list->head != NULL) {
            result = false;
        }
    }
    return result;
}

int size(List list) {
    NodePtr walker;
    int counter = 0;

    if (list != NULL) {
        walker = list->head;
        while(walker != NULL){
            counter += 1;
            walker = getNext(walker);
        }
    }

    return counter;
}

void printRanking(List list){

    int counter = 1;
    NodePtr walker = list->head;
    if(walker == NULL){
        printf("Ranking Vazio :// \n");
    }else{
        printf("Ranking:\n");
        while(walker != NULL && counter <=5){
            printf("%dº lugar: %s \t %d pontos\n", counter, walker->name, walker->score);
            counter++;
            walker = getNext(walker);
        }
    }

}