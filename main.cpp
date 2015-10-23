#include <QCoreApplication>
#include "huffman.h"
#include "tree.h"
#include <QTime>
#include <QDebug>
#include <QString>

int main(){

    QTime time;
    time.start();
    Huffman Huff;
    //Huff.comprimir("C:/file/music.mid");

    Huff.descomprimir("C:/file/music.huff");

    qDebug( "Tempo decorrido: %d milissegundos", time.elapsed() );

    return 0;
}
