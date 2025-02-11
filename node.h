#include <stdlib.h>

typedef struct node* NodePtr;
typedef char* Info;

NodePtr createNode();

void destroyNode(NodePtr node);

void setInfo(NodePtr node, Info element);

void setNext(NodePtr node, NodePtr next);

void setScore(NodePtr node, int score);

Info getInfo(NodePtr node);

NodePtr getNext(NodePtr node);

int getScore(NodePtr node);