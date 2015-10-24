#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <iostream>
#include <QVector>
#include <QByteArray>

using namespace std;

class Tree{
    Node *root;
public:
    Tree();
    void add(Node *node); //Cria a arvore
    Node *getRoot(); // retorna a raiz
    bool leaf(Node *node); //verifica se é folha
    QByteArray buildTree(Node *node, QVector<QByteArray> &cod);
    void mountTree(Node *node, QByteArray &data);


};

#endif // TREE_H
