#include "gui.h"
#include "huffman.h"
#include "tree.h"
#include <QApplication>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[]){


    QApplication app(argc, argv);
    Gui w;
    w.setFixedSize(500,225);


    Huffman Huff;

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
    QCommandLineOption startGui("gui", QApplication::translate("main", "Start Gui."));
    parser.addOption(startGui);
    parser.process(app);




    //ARGUMENTS



    if(app.arguments().size() == 1){
        w.show();
    }
    else if(parser.isSet(startGui))
        w.show();
    else if(parser.isSet(compress)){
        Huff.comprimir(parser.value(compress), parser.value(outName));
        qDebug()<<"Compressão realizada!";
        exit(0);
    }
    else if(Huff.IfHuff(app.arguments().at(1))){
        Huff.descomprimir(app.arguments().at(1), parser.value(local));
        qDebug()<<"Descompressão realizada !";
        exit(0);
    }
    else{
        qDebug()<<qPrintable(parser.helpText());
    }



    return app.exec();
}
