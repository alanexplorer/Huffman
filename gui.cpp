#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui){
    ui->setupUi(this);

    //Image
    QPixmap pex("C:/Users/conta/Documents/GitHub/Huffman/data/mk.png");
    ui->label_picture->setPixmap(pex);
    //Sound

    QMediaPlaylist *playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl::fromLocalFile("C:/Users/conta/Documents/GitHub/Huffman/data/mk.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setCurrentIndex(1);
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setPlaylist(playlist);
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
    //File information

    QFileInfo Info(filename);

    ui->NameResult->setText(Info.fileName());
    ui->TypeResult->setText(Info.completeSuffix());

    QString size = QString::number(Info.size());
    size+=" byte";
    ui->SizeResult->setText(size);
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
