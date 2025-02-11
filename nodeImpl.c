#include "node.h"
#include "string.h"

struct node {
    Info name;
    int score;
    NodePtr next;
};

NodePtr createNode() {
    NodePtr node;
    node = malloc(sizeof(struct node));
    return node;
}

void destroyNode(NodePtr node) {
    free(node);
}

void setInfo(NodePtr node, Info name) {
    if (node != NULL) {
        strcpy(node->name, name);
    }
}

void setNext(NodePtr node, NodePtr next) {
    if (node != NULL) {
        node->next = next;
    }
}

void setScore(NodePtr node, int score){
    if (node != NULL){
        node->score = score;
    }
}

Info getInfo(NodePtr node) {
    if (node != NULL){
        return node->name;
    }
    return NULL;
}

NodePtr getNext(NodePtr node) {
    if (node != NULL) {
        return node->next;
    }
    return NULL;
}

int getScore(NodePtr node){
    if (node != NULL) {
        return node->score;
    }
    return -1;
}