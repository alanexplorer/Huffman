/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gui
{
public:
    QWidget *centralWidget;
    QLabel *label_picture;
    QLabel *labelCompress;
    QPushButton *NavCompress_bt;
    QTextEdit *nav_txt;
    QPushButton *Decopress_bt;
    QLabel *labelEnter;
    QPushButton *Compress_bt;
    QFrame *line;
    QLabel *NameFile;
    QLabel *Type;
    QLabel *Size;
    QLabel *NameResult;
    QLabel *TypeResult;
    QLabel *SizeResult;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName(QStringLiteral("Gui"));
        Gui->resize(500, 270);
        centralWidget = new QWidget(Gui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_picture = new QLabel(centralWidget);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setGeometry(QRect(390, 85, 85, 85));
        labelCompress = new QLabel(centralWidget);
        labelCompress->setObjectName(QStringLiteral("labelCompress"));
        labelCompress->setGeometry(QRect(130, 10, 211, 16));
        NavCompress_bt = new QPushButton(centralWidget);
        NavCompress_bt->setObjectName(QStringLiteral("NavCompress_bt"));
        NavCompress_bt->setGeometry(QRect(390, 40, 80, 21));
        nav_txt = new QTextEdit(centralWidget);
        nav_txt->setObjectName(QStringLiteral("nav_txt"));
        nav_txt->setEnabled(true);
        nav_txt->setGeometry(QRect(80, 40, 300, 23));
        Decopress_bt = new QPushButton(centralWidget);
        Decopress_bt->setObjectName(QStringLiteral("Decopress_bt"));
        Decopress_bt->setGeometry(QRect(250, 80, 80, 21));
        labelEnter = new QLabel(centralWidget);
        labelEnter->setObjectName(QStringLiteral("labelEnter"));
        labelEnter->setGeometry(QRect(30, 50, 47, 13));
        Compress_bt = new QPushButton(centralWidget);
        Compress_bt->setObjectName(QStringLiteral("Compress_bt"));
        Compress_bt->setGeometry(QRect(130, 80, 80, 21));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 170, 471, 41));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        NameFile = new QLabel(centralWidget);
        NameFile->setObjectName(QStringLiteral("NameFile"));
        NameFile->setGeometry(QRect(31, 121, 45, 16));
        Type = new QLabel(centralWidget);
        Type->setObjectName(QStringLiteral("Type"));
        Type->setGeometry(QRect(31, 140, 24, 16));
        Size = new QLabel(centralWidget);
        Size->setObjectName(QStringLiteral("Size"));
        Size->setGeometry(QRect(31, 159, 19, 16));
        NameResult = new QLabel(centralWidget);
        NameResult->setObjectName(QStringLiteral("NameResult"));
        NameResult->setGeometry(QRect(90, 120, 241, 16));
        TypeResult = new QLabel(centralWidget);
        TypeResult->setObjectName(QStringLiteral("TypeResult"));
        TypeResult->setGeometry(QRect(90, 140, 241, 16));
        SizeResult = new QLabel(centralWidget);
        SizeResult->setObjectName(QStringLiteral("SizeResult"));
        SizeResult->setGeometry(QRect(90, 160, 241, 16));
        Gui->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Gui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Gui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Gui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Gui->setStatusBar(statusBar);
        menuBar = new QMenuBar(Gui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 20));
        Gui->setMenuBar(menuBar);

        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QMainWindow *Gui)
    {
        Gui->setWindowTitle(QApplication::translate("Gui", "Huffman", 0));
        label_picture->setText(QString());
        labelCompress->setText(QApplication::translate("Gui", "Enter with file to compress or descompress", 0));
        NavCompress_bt->setText(QApplication::translate("Gui", "Browser", 0));
#ifndef QT_NO_TOOLTIP
        nav_txt->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        nav_txt->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_ACCESSIBILITY
        nav_txt->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        Decopress_bt->setText(QApplication::translate("Gui", "Decompress", 0));
        labelEnter->setText(QApplication::translate("Gui", "File", 0));
        Compress_bt->setText(QApplication::translate("Gui", "Compress", 0));
        NameFile->setText(QApplication::translate("Gui", "File name", 0));
        Type->setText(QApplication::translate("Gui", "Type", 0));
        Size->setText(QApplication::translate("Gui", "Size", 0));
        NameResult->setText(QString());
        TypeResult->setText(QString());
        SizeResult->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
