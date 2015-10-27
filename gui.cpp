#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui){
    ui->setupUi(this);

    //Image
    QPixmap pex("C:/Users/conta/Documents/Huffman/data/mk.png");
    ui->label_picture->setPixmap(pex);
    //Sound
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("C:/Users/conta/Documents/Huffman/data/mk.wav"));
    player->setVolume(50);
    player->play();

}

Gui::~Gui(){
    delete ui;
}

void Gui::on_NavCompress_bt_clicked(){
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);; Text File (*.txt)"
                );
    ui->nav_txt->setText(filename);
    if(filename != ""){
        QMessageBox::information(this, "Compress", "File Added");
        Address = filename;
    }
}

void Gui::on_Compress_bt_clicked(){

    if(Address.size()){

        Huffman Huff;
        Huff.comprimir(Address, "");
    }
    else
        QMessageBox::information(this, "Compress", "File Added");
}

void Gui::on_Decopress_bt_clicked(){
    if(Address.size()){
        Huffman Huff;
        Huff.descomprimir(Address, "");
      }
    else
        QMessageBox::information(this, "Descompress", "File Added");

}
