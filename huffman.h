#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "tree.h"
#include "node.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QBitArray>
#include <iostream>
#include <QList>
#include <QtAlgorithms>
#include <QVector>
#include <QDir>

using namespace std;

class Huffman{
public:
    Huffman();
    void comprimir(QString entrada);
    void descomprimir (QString saida);
    QByteArray fileCod(QByteArray data, QVector<QByteArray> codes);
    void Size(QByteArray &codification, QByteArray &Data, QByteArray &represent);
    QString NameOut(QString Out);
    void print(Node *node,int depth); //imprime a arvore
    void getHead(QByteArray bytes, int &sizeTrash, int &sizeTree, int &sizeName);
    void decode(QBitArray &bit,QByteArray bytes, int index);
    void NewFile(QString Out, Tree &arvore, Node *node, QBitArray bit, QByteArray &code, int trash);

};

#endif // HUFFMAN_H
