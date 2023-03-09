/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_Host;
    QLabel *label_4;
    QLineEdit *lineEdit_Port;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_User;
    QLabel *label_3;
    QLineEdit *lineEdit_pad;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Login;
    QLabel *label_info;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *lineEdit_FilePath;
    QToolButton *toolButton_File;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QLineEdit *lineEdit_DirPath;
    QToolButton *toolButton_Dir;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_FileList;
    QPushButton *pushButton_Back;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_Upload;
    QPushButton *pushButton_Upload_2;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radioButton;
    QTimeEdit *timeEdit;
    QPushButton *pushButton_ComfirmT;
    QPushButton *pushButton_CancelT;
    QLabel *label_tips;
    QProgressBar *progressBar;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(510, 653);
        gridLayout_3 = new QGridLayout(Widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(label);

        lineEdit_Host = new QLineEdit(groupBox);
        lineEdit_Host->setObjectName(QStringLiteral("lineEdit_Host"));
        lineEdit_Host->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(lineEdit_Host);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(label_4);

        lineEdit_Port = new QLineEdit(groupBox);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(lineEdit_Port);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(40, 0));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_User = new QLineEdit(groupBox);
        lineEdit_User->setObjectName(QStringLiteral("lineEdit_User"));
        lineEdit_User->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(lineEdit_User);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(40, 0));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_pad = new QLineEdit(groupBox);
        lineEdit_pad->setObjectName(QStringLiteral("lineEdit_pad"));
        lineEdit_pad->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(lineEdit_pad);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_Login = new QPushButton(groupBox);
        pushButton_Login->setObjectName(QStringLiteral("pushButton_Login"));
        pushButton_Login->setMinimumSize(QSize(90, 40));

        horizontalLayout_4->addWidget(pushButton_Login);

        label_info = new QLabel(groupBox);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setMinimumSize(QSize(20, 0));

        horizontalLayout_4->addWidget(label_info);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_5->addWidget(label_8);

        lineEdit_FilePath = new QLineEdit(groupBox_2);
        lineEdit_FilePath->setObjectName(QStringLiteral("lineEdit_FilePath"));
        lineEdit_FilePath->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(lineEdit_FilePath);

        toolButton_File = new QToolButton(groupBox_2);
        toolButton_File->setObjectName(QStringLiteral("toolButton_File"));
        toolButton_File->setMinimumSize(QSize(30, 30));

        horizontalLayout_5->addWidget(toolButton_File);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_6->addWidget(label_9);

        lineEdit_DirPath = new QLineEdit(groupBox_2);
        lineEdit_DirPath->setObjectName(QStringLiteral("lineEdit_DirPath"));
        lineEdit_DirPath->setMinimumSize(QSize(0, 30));

        horizontalLayout_6->addWidget(lineEdit_DirPath);

        toolButton_Dir = new QToolButton(groupBox_2);
        toolButton_Dir->setObjectName(QStringLiteral("toolButton_Dir"));
        toolButton_Dir->setMinimumSize(QSize(30, 30));

        horizontalLayout_6->addWidget(toolButton_Dir);


        gridLayout_2->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton_FileList = new QPushButton(groupBox_2);
        pushButton_FileList->setObjectName(QStringLiteral("pushButton_FileList"));
        pushButton_FileList->setMinimumSize(QSize(80, 30));

        horizontalLayout_7->addWidget(pushButton_FileList);

        pushButton_Back = new QPushButton(groupBox_2);
        pushButton_Back->setObjectName(QStringLiteral("pushButton_Back"));
        pushButton_Back->setMinimumSize(QSize(80, 30));

        horizontalLayout_7->addWidget(pushButton_Back);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        treeWidget = new QTreeWidget(groupBox_2);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout_2->addWidget(treeWidget, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);

        pushButton_Upload = new QPushButton(Widget);
        pushButton_Upload->setObjectName(QStringLiteral("pushButton_Upload"));
        pushButton_Upload->setMinimumSize(QSize(120, 40));

        horizontalLayout_9->addWidget(pushButton_Upload);

        pushButton_Upload_2 = new QPushButton(Widget);
        pushButton_Upload_2->setObjectName(QStringLiteral("pushButton_Upload_2"));
        pushButton_Upload_2->setMinimumSize(QSize(120, 40));

        horizontalLayout_9->addWidget(pushButton_Upload_2);


        gridLayout_3->addLayout(horizontalLayout_9, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        radioButton = new QRadioButton(Widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout_8->addWidget(radioButton);

        timeEdit = new QTimeEdit(Widget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumSize(QSize(120, 34));

        horizontalLayout_8->addWidget(timeEdit);

        pushButton_ComfirmT = new QPushButton(Widget);
        pushButton_ComfirmT->setObjectName(QStringLiteral("pushButton_ComfirmT"));
        pushButton_ComfirmT->setMinimumSize(QSize(120, 40));

        horizontalLayout_8->addWidget(pushButton_ComfirmT);

        pushButton_CancelT = new QPushButton(Widget);
        pushButton_CancelT->setObjectName(QStringLiteral("pushButton_CancelT"));
        pushButton_CancelT->setMinimumSize(QSize(120, 40));

        horizontalLayout_8->addWidget(pushButton_CancelT);


        gridLayout_3->addLayout(horizontalLayout_8, 3, 0, 1, 1);

        label_tips = new QLabel(Widget);
        label_tips->setObjectName(QStringLiteral("label_tips"));
        label_tips->setMinimumSize(QSize(0, 25));

        gridLayout_3->addWidget(label_tips, 4, 0, 1, 1);

        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QLatin1String("QProgressBar{\n"
"	\n"
"        border: none;\n"
"        text-align: center;\n"
"        background: rgb(210, 225, 240);\n"
"}\n"
"QProgressBar::chunk {\n"
"        background: rgb(0, 142, 213);\n"
"	\n"
"}"));
        progressBar->setValue(0);

        gridLayout_3->addWidget(progressBar, 5, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Widget", "\350\277\236\346\216\245\347\275\221\347\273\234", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\347\275\221\347\273\234", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "\347\253\257\345\217\243", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\347\224\250\346\210\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "\345\257\206\347\240\201", Q_NULLPTR));
        pushButton_Login->setText(QApplication::translate("Widget", "\350\277\236\346\216\245", Q_NULLPTR));
        label_info->setText(QString());
        groupBox_2->setTitle(QApplication::translate("Widget", "\346\226\207\344\273\266\351\200\211\346\213\251", Q_NULLPTR));
        label_8->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\272\220\346\226\207\344\273\266", Q_NULLPTR));
        toolButton_File->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
        label_9->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\272\220\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        toolButton_Dir->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
        pushButton_FileList->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", Q_NULLPTR));
        pushButton_Back->setText(QApplication::translate("Widget", "\350\277\224\345\233\236", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "\345\217\214\345\207\273\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271\350\277\233\345\205\245\345\205\266\344\270\255\357\274\214\347\204\266\345\220\216\350\277\233\350\241\214\344\270\212\344\274\240", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("Widget", "\346\227\245\346\234\237", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("Widget", "\347\273\204", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("Widget", "\346\235\203\351\231\220", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("Widget", "\345\244\247\345\260\217", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("Widget", "\345\220\215\347\247\260", Q_NULLPTR));
        pushButton_Upload->setText(QApplication::translate("Widget", "\344\270\212\344\274\240\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_Upload_2->setText(QApplication::translate("Widget", "\344\270\212\344\274\240\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        radioButton->setText(QApplication::translate("Widget", "\344\270\212\344\274\240\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        timeEdit->setDisplayFormat(QApplication::translate("Widget", "H:mm:ss", Q_NULLPTR));
        pushButton_ComfirmT->setText(QApplication::translate("Widget", "\347\241\256\350\256\244\345\256\232\346\227\266\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_CancelT->setText(QApplication::translate("Widget", "\345\217\226\346\266\210\345\256\232\346\227\266\344\270\212\344\274\240", Q_NULLPTR));
        label_tips->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
