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
#include <QHash>
#include <QDir>

using namespace std;

class Huffman{
public:
    Huffman();
    void comprimir(QString entrada, QString saida);
    void descomprimir (QString saida, QString local);
    QByteArray fileCod(QByteArray data, QByteArray &trash, QHash<int, QByteArray> codes);
    void Size(QByteArray &codification, QByteArray &Data, QByteArray &represent);
    QString NameOut(QString Out);
    void print(Node *node,int depth); //imprime a arvore
    void getHead(QByteArray bytes, int &sizeTrash, int &sizeTree, int &sizeName);
    void NewFile(QString Out, Tree &arvore, Node *node, QBitArray bit, QByteArray &code, int trash);
    bool ifHuffman(QString Huffman);

};

#endif // HUFFMAN_H
