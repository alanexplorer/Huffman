#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui){
    ui->setupUi(this);

    //Image
    QPixmap pex("data/mk.png");
    ui->label_picture->setPixmap(pex);
    //Sound

    QMediaPlaylist *playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl::fromLocalFile("data/mk.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setCurrentIndex(1);
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setPlaylist(playlist);
    player->setVolume(30);
    player->play();
}

Gui::~Gui(){
    delete ui;
}

void Gui::on_NavCompress_bt_clicked(){
    QMessageBox msgBox;
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);; Text File (*.txt)"
                );
    ui->nav_txt->setText(filename);
    if(filename != ""){
        msgBox.setText("File Added");
        msgBox.exec();
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
    QMessageBox msgBox;

    if(Address.size()){

        Huffman Huff;
        Huff.comprimir(Address, "");
        Address.clear();
        ui->nav_txt->clear();
        msgBox.setText("Compressed");
        msgBox.exec();
    }
    else
        QMessageBox::warning( this, tr("Compress"), tr("Enter the file address") );
}

void Gui::on_Decopress_bt_clicked(){
    QMessageBox msgBox;
    Huffman Huff;
    if(Address.size()){
        if(Huff.IfHuff(Address)){


            Huff.descomprimir(Address, "");
            Address.clear();
            ui->nav_txt->clear();
            msgBox.setText("Decompressed");
            msgBox.exec();
        }
        else
            QMessageBox::warning( this, tr("Compress"), tr("this isn't huff file") );

    }
    else
        QMessageBox::warning( this, tr("Compress"), tr("Enter the file address") );

}
