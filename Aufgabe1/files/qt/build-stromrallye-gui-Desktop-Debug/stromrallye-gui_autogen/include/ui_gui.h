/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QAction *actionSolve;
    QWidget *centralwidget;
    QLineEdit *inBattNum;
    QCheckBox *slant;
    QTextBrowser *textBrowser;
    QPushButton *start;
    QPushButton *generate;
    QPushButton *browse;
    QLabel *label;
    QLabel *label_3;
    QTextBrowser *generated;
    QPushButton *saveAs;
    QPushButton *saveBattNum;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QString::fromUtf8("GUI"));
        GUI->resize(800, 655);
        actionSolve = new QAction(GUI);
        actionSolve->setObjectName(QString::fromUtf8("actionSolve"));
        centralwidget = new QWidget(GUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        inBattNum = new QLineEdit(centralwidget);
        inBattNum->setObjectName(QString::fromUtf8("inBattNum"));
        inBattNum->setGeometry(QRect(660, 70, 71, 21));
        slant = new QCheckBox(centralwidget);
        slant->setObjectName(QString::fromUtf8("slant"));
        slant->setGeometry(QRect(20, 120, 171, 31));
        slant->setLayoutDirection(Qt::RightToLeft);
        slant->setIconSize(QSize(32, 32));
        slant->setTristate(false);
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 230, 431, 371));
        start = new QPushButton(centralwidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(20, 170, 141, 41));
        generate = new QPushButton(centralwidget);
        generate->setObjectName(QString::fromUtf8("generate"));
        generate->setGeometry(QRect(480, 110, 131, 41));
        browse = new QPushButton(centralwidget);
        browse->setObjectName(QString::fromUtf8("browse"));
        browse->setGeometry(QRect(20, 60, 141, 41));
        browse->setIconSize(QSize(32, 32));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 70, 251, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(480, 70, 171, 17));
        generated = new QTextBrowser(centralwidget);
        generated->setObjectName(QString::fromUtf8("generated"));
        generated->setGeometry(QRect(630, 110, 161, 41));
        saveAs = new QPushButton(centralwidget);
        saveAs->setObjectName(QString::fromUtf8("saveAs"));
        saveAs->setGeometry(QRect(480, 180, 131, 41));
        saveBattNum = new QPushButton(centralwidget);
        saveBattNum->setObjectName(QString::fromUtf8("saveBattNum"));
        saveBattNum->setGeometry(QRect(740, 70, 31, 25));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 771, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);

        horizontalLayout->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        GUI->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GUI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GUI->setStatusBar(statusbar);

        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QMainWindow *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "Stromrallye", nullptr));
        actionSolve->setText(QCoreApplication::translate("GUI", "Solve", nullptr));
        slant->setText(QCoreApplication::translate("GUI", "Schr\303\244ge \303\234berg\303\244nge    ", nullptr));
        start->setText(QCoreApplication::translate("GUI", "Start", nullptr));
        generate->setText(QCoreApplication::translate("GUI", "Generate", nullptr));
        browse->setText(QCoreApplication::translate("GUI", "Browse", nullptr));
        label->setText(QCoreApplication::translate("GUI", "W\303\244hle ein Beispiel aus", nullptr));
        label_3->setText(QCoreApplication::translate("GUI", "Die Anzahl der Batterien", nullptr));
        saveAs->setText(QCoreApplication::translate("GUI", "Save As", nullptr));
        saveBattNum->setText(QCoreApplication::translate("GUI", "OK", nullptr));
        label_4->setText(QCoreApplication::translate("GUI", "                            L\303\266sen", nullptr));
        label_5->setText(QString());
        label_2->setText(QCoreApplication::translate("GUI", "     Generator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
