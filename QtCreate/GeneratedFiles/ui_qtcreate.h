/********************************************************************************
** Form generated from reading UI file 'qtcreate.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCREATE_H
#define UI_QTCREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtCreateClass
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionExit;
    QWidget *centralWidget;
    QGroupBox *ScheduleGroupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *EDFpushButton;
    QPushButton *RMSpushButton;
    QPushButton *DMSpushButton;
    QPushButton *LSTpushButton;
    QPushButton *MFPSpushButton;
    QGroupBox *ConsoleGroupBox;
    QTextEdit *ConsoleTextEdit;
    QGroupBox *GantGroupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *DataGroupBox;
    QTextEdit *DataTextEdit;
    QGroupBox *ResultGroupBox;
    QTextEdit *ResultTextEdit;
    QPushButton *FileOpenButton;
    QPushButton *FileSaveButton;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtCreateClass)
    {
        if (QtCreateClass->objectName().isEmpty())
            QtCreateClass->setObjectName(QStringLiteral("QtCreateClass"));
        QtCreateClass->resize(1158, 642);
        QtCreateClass->setStyleSheet(QStringLiteral("background-image: url(:/QtCreate/Logo.jpg);"));
        actionLoad = new QAction(QtCreateClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionSave = new QAction(QtCreateClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(QtCreateClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(QtCreateClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ScheduleGroupBox = new QGroupBox(centralWidget);
        ScheduleGroupBox->setObjectName(QStringLiteral("ScheduleGroupBox"));
        ScheduleGroupBox->setGeometry(QRect(10, 10, 211, 281));
        verticalLayoutWidget = new QWidget(ScheduleGroupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 30, 191, 221));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        EDFpushButton = new QPushButton(verticalLayoutWidget);
        EDFpushButton->setObjectName(QStringLiteral("EDFpushButton"));

        verticalLayout_2->addWidget(EDFpushButton);

        RMSpushButton = new QPushButton(verticalLayoutWidget);
        RMSpushButton->setObjectName(QStringLiteral("RMSpushButton"));

        verticalLayout_2->addWidget(RMSpushButton);

        DMSpushButton = new QPushButton(verticalLayoutWidget);
        DMSpushButton->setObjectName(QStringLiteral("DMSpushButton"));

        verticalLayout_2->addWidget(DMSpushButton);

        LSTpushButton = new QPushButton(verticalLayoutWidget);
        LSTpushButton->setObjectName(QStringLiteral("LSTpushButton"));

        verticalLayout_2->addWidget(LSTpushButton);

        MFPSpushButton = new QPushButton(verticalLayoutWidget);
        MFPSpushButton->setObjectName(QStringLiteral("MFPSpushButton"));

        verticalLayout_2->addWidget(MFPSpushButton);

        ConsoleGroupBox = new QGroupBox(centralWidget);
        ConsoleGroupBox->setObjectName(QStringLiteral("ConsoleGroupBox"));
        ConsoleGroupBox->setGeometry(QRect(230, 10, 531, 281));
        ConsoleTextEdit = new QTextEdit(ConsoleGroupBox);
        ConsoleTextEdit->setObjectName(QStringLiteral("ConsoleTextEdit"));
        ConsoleTextEdit->setGeometry(QRect(10, 20, 511, 251));
        GantGroupBox = new QGroupBox(centralWidget);
        GantGroupBox->setObjectName(QStringLiteral("GantGroupBox"));
        GantGroupBox->setGeometry(QRect(170, 300, 591, 281));
        label = new QLabel(GantGroupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 31, 16));
        label_2 = new QLabel(GantGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(520, 20, 54, 12));
        label_3 = new QLabel(GantGroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 30, 16, 16));
        DataGroupBox = new QGroupBox(centralWidget);
        DataGroupBox->setObjectName(QStringLiteral("DataGroupBox"));
        DataGroupBox->setGeometry(QRect(770, 10, 361, 281));
        DataTextEdit = new QTextEdit(DataGroupBox);
        DataTextEdit->setObjectName(QStringLiteral("DataTextEdit"));
        DataTextEdit->setGeometry(QRect(10, 20, 341, 251));
        ResultGroupBox = new QGroupBox(centralWidget);
        ResultGroupBox->setObjectName(QStringLiteral("ResultGroupBox"));
        ResultGroupBox->setGeometry(QRect(770, 300, 361, 281));
        ResultTextEdit = new QTextEdit(ResultGroupBox);
        ResultTextEdit->setObjectName(QStringLiteral("ResultTextEdit"));
        ResultTextEdit->setGeometry(QRect(10, 20, 341, 241));
        ResultTextEdit->setAutoFillBackground(false);
        ResultTextEdit->setFrameShape(QFrame::NoFrame);
        ResultTextEdit->setFrameShadow(QFrame::Plain);
        ResultTextEdit->setLineWidth(0);
        FileOpenButton = new QPushButton(centralWidget);
        FileOpenButton->setObjectName(QStringLiteral("FileOpenButton"));
        FileOpenButton->setEnabled(false);
        FileOpenButton->setGeometry(QRect(40, 580, 75, 23));
        FileSaveButton = new QPushButton(centralWidget);
        FileSaveButton->setObjectName(QStringLiteral("FileSaveButton"));
        FileSaveButton->setEnabled(false);
        FileSaveButton->setGeometry(QRect(40, 610, 75, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 310, 121, 231));
        label_4->setStyleSheet(QStringLiteral("background-image: url(:/QtCreate/logo8.png);"));
        QtCreateClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtCreateClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1158, 23));
        QtCreateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtCreateClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtCreateClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtCreateClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtCreateClass->setStatusBar(statusBar);

        retranslateUi(QtCreateClass);
        QObject::connect(FileOpenButton, SIGNAL(clicked()), QtCreateClass, SLOT(LoadAction()));
        QObject::connect(FileSaveButton, SIGNAL(clicked()), QtCreateClass, SLOT(SaveAction()));
        QObject::connect(LSTpushButton, SIGNAL(clicked()), QtCreateClass, SLOT(LSTBtn_Click()));
        QObject::connect(RMSpushButton, SIGNAL(clicked()), QtCreateClass, SLOT(RMSBtn_Click()));
        QObject::connect(MFPSpushButton, SIGNAL(clicked()), QtCreateClass, SLOT(MFPSBtn_Click()));
        QObject::connect(EDFpushButton, SIGNAL(clicked()), QtCreateClass, SLOT(EDFBtn_Click()));
        QObject::connect(DMSpushButton, SIGNAL(clicked()), QtCreateClass, SLOT(DMSBtn_Click()));

        QMetaObject::connectSlotsByName(QtCreateClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtCreateClass)
    {
        QtCreateClass->setWindowTitle(QApplication::translate("QtCreateClass", "QtCreate", 0));
        actionLoad->setText(QApplication::translate("QtCreateClass", "Load", 0));
        actionSave->setText(QApplication::translate("QtCreateClass", "Save", 0));
        actionExit->setText(QApplication::translate("QtCreateClass", "Exit", 0));
        ScheduleGroupBox->setTitle(QApplication::translate("QtCreateClass", "\350\260\203\345\272\246\347\255\226\347\225\245", 0));
        EDFpushButton->setText(QApplication::translate("QtCreateClass", "\347\233\270\345\257\271\347\237\255\346\210\252\346\255\242\346\227\266\351\227\264\344\274\230\345\205\210\350\260\203\345\272\246(EDF)", 0));
        RMSpushButton->setText(QApplication::translate("QtCreateClass", "\345\215\225\350\260\203\351\200\237\347\216\207\350\260\203\345\272\246(RMS)", 0));
        DMSpushButton->setText(QApplication::translate("QtCreateClass", "\347\237\255\346\210\252\346\255\242\346\227\266\351\227\264\350\260\203\345\272\246(DMS)", 0));
        LSTpushButton->setText(QApplication::translate("QtCreateClass", "\346\234\200\345\260\217\346\235\276\345\274\233\346\227\266\351\227\264\350\260\203\345\272\246(LST)", 0));
        MFPSpushButton->setText(QApplication::translate("QtCreateClass", "\346\234\200\345\260\217\347\251\272\351\227\262\346\227\266\351\227\264\345\205\261\344\272\253\345\210\206\345\214\272\350\260\203\345\272\246(MFPS)", 0));
        ConsoleGroupBox->setTitle(QApplication::translate("QtCreateClass", "\345\256\236\346\227\266\350\260\203\345\272\246\344\277\241\346\201\257", 0));
        GantGroupBox->setTitle(QApplication::translate("QtCreateClass", "\350\277\220\350\241\214\347\212\266\346\200\201\345\233\276", 0));
        label->setText(QApplication::translate("QtCreateClass", "Task", 0));
        label_2->setText(QApplication::translate("QtCreateClass", "Timeslice", 0));
        label_3->setText(QApplication::translate("QtCreateClass", "ID", 0));
        DataGroupBox->setTitle(QApplication::translate("QtCreateClass", "\350\260\203\345\272\246\346\225\260\346\215\256", 0));
        ResultGroupBox->setTitle(QApplication::translate("QtCreateClass", "\350\277\220\350\241\214\347\273\223\346\236\234", 0));
        FileOpenButton->setText(QApplication::translate("QtCreateClass", "FileOpen", 0));
        FileSaveButton->setText(QApplication::translate("QtCreateClass", "FileSave", 0));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtCreateClass: public Ui_QtCreateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCREATE_H
