#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "tree.h"
#include "node.h"
#include <QString>
#include <QFile>
#include <QFileInfo>
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
    void comprimir(QString Input, QString exit);
    void descomprimir (QString exit, QString local);
    QByteArray FileCode(QByteArray data, QByteArray &trash, QHash<int, QByteArray> codes);
    void Size(QByteArray &codification, QByteArray &Data, QByteArray &represent);
    QString NameOut(QString Out);
    void print(Node *node,int depth); //imprime a arvore
    void getHead(QByteArray bytes, int &sizeTrash, int &sizeTree, int &sizeName);
    void Decoding(Tree &arvore, Node *node, QBitArray bit, QByteArray &code, int SizeTrash);
    bool IfHuff(QString Huffman);

};
#endif // HUFFMAN_H
