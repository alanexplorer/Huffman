#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui){
    ui->setupUi(this);
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
    Address = filename;

    //File information

    QFileInfo Info(filename);

    NameFile = Info.fileName();
    ui->NameResult->setText(NameFile);
    ui->TypeResult->setText(Info.completeSuffix());

    QString size = QString::number(Info.size());
    size+=" byte";
    ui->SizeResult->setText(size);
}

void Gui::on_NavLocalOut_bt_clicked(){

    LocalOut = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->nav_Out->setText(LocalOut);

}

void Gui::on_Compress_bt_clicked(){
    QMessageBox msgBox;

    if(Address.size()){

        Huffman Huff;

        Huff.comprimir(Address, LocalOut);
        Address.clear();
        LocalOut.clear();
        ui->nav_txt->clear();
        ui->nav_Out->clear();
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

            Huff.descomprimir(Address, LocalOut);
            Address.clear();
            LocalOut.clear();
            ui->nav_txt->clear();
            ui->nav_Out->clear();
            msgBox.setText("Decompressed");
            msgBox.exec();
        }
        else
            QMessageBox::warning( this, tr("Decompress"), tr("this isn't huff file") );

    }
    else
        QMessageBox::warning( this, tr("Decompress"), tr("Enter the file address") );

}

void Gui::on_checkBox_OutNav_clicked(bool checked){
    if(checked){
        ui->nav_Out->setEnabled(true);
        ui->NavLocalOut_bt->setEnabled(true);
    }
    else{
        ui->nav_Out->setDisabled(true);
        ui->NavLocalOut_bt->setDisabled(true);
    }

}
