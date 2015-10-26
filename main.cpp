#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "huffman.h"
#include "tree.h"
#include <QTime>
#include <QDebug>
#include <QString>


int main(int argc, char *argv[]){

    QTime time;
    time.start();

    Huffman Huff;

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Huffman");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file.x", QCoreApplication::translate("main", "File being"));
    parser.addPositionalArgument("file.huff", QCoreApplication::translate("main", "name to save"));
    parser.addPositionalArgument("local", QCoreApplication::translate("main", "Local to save archive."));

    QCommandLineOption compress("c",QCoreApplication::translate("main","Compress file.x."),
                                QCoreApplication::translate("main","file.x"));
    parser.addOption(compress);
    QCommandLineOption outName("o",QCoreApplication::translate("main","Save as file.huff."),
                               QCoreApplication::translate("main","file.huff"));
    parser.addOption(outName);
    QCommandLineOption local("d",QCoreApplication::translate("main","Decompress in local."),
                             QCoreApplication::translate("main","local"));
    parser.addOption(local);
    parser.process(app);

    //ARGUMENTS

    if(parser.isSet(compress))
        Huff.comprimir(parser.value(compress), parser.value(outName));
    else{
        if(parser.isSet(local)){
            if(Huff.ifHuffman(app.arguments().at(1)))
                Huff.descomprimir(app.arguments().at(1), parser.value(local));
            else
                qDebug()<<"Esse n eh um arquivo .huff";
        }
        else if(app.arguments().size() > 0 && Huff.ifHuffman(app.arguments().at(1)) ){
            Huff.descomprimir(app.arguments().at(1), parser.value(local));
        }
        else
            qDebug()<<qPrintable(parser.helpText());

    }
    qDebug( "Tempo decorrido: %d milissegundos", time.elapsed() );

    return app.exec();
}
