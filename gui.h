#ifndef GUI_H
#define GUI_H

#include "huffman.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <QMediaPlayer>
#include<QString>


namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

private slots:
    void on_NavCompress_bt_clicked();

    void on_Compress_bt_clicked();

    void on_Decopress_bt_clicked();

private:
    Ui::Gui *ui;
    QString Address;
};

#endif // GUI_H
