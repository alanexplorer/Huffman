#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "tree.h"
#include "node.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <iostream>
#include <QList>
#include <QtAlgorithms>
#include <QVector>

using namespace std;

class Huffman
{
public:
    Huffman();
    void comprimir(QString entrada, QString saida);
    QByteArray fileCod(QByteArray data, QVector<QByteArray> codes);
    void generateFileCod(QByteArray &codification, QByteArray &fileData, QByteArray &treeSize);
    QString NameOut(QString Out);
    void print(Node *node,int depth); //imprime a arvore

};

#endif // HUFFMAN_H
