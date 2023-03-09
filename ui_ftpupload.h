/********************************************************************************
** Form generated from reading UI file 'ftpupload.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTPUPLOAD_H
#define UI_FTPUPLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FtpUpload
{
public:
    QGridLayout *gridLayout_3;
    QTreeWidget *treeWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_Refush;
    QPushButton *pushButton_Back;
    QPushButton *uploadButton;
    QPushButton *uploadButton_All;
    QPushButton *downloadButton;
    QPushButton *cancelBtn;
    QHBoxLayout *horizontalLayout_9;
    QLabel *ipLabel_7;
    QLineEdit *lineEdit_DirPath_2;
    QToolButton *toolButton_dir_2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *ipLabel;
    QLabel *ipLabel_2;
    QLabel *ipLabel_3;
    QLabel *ipLabel_4;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit_Host;
    QLineEdit *lineEdit_Port;
    QLineEdit *lineEdit_User;
    QLineEdit *lineEdit_pad;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Login;
    QPushButton *pushButton_Quit;
    QCheckBox *checkBox_AutoLogin;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QRadioButton *radioButtonActive;
    QRadioButton *radioButtonPassive;
    QHBoxLayout *horizontalLayout_4;
    QLabel *ipLabel_5;
    QLineEdit *lineEdit_FilePath;
    QToolButton *toolButton_file;
    QHBoxLayout *horizontalLayout_5;
    QLabel *ipLabel_6;
    QLineEdit *lineEdit_DirPath;
    QToolButton *toolButton_dir;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *setButton;
    QPushButton *minButton;
    QPushButton *closeButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton;
    QComboBox *CB_EncodingFormat;
    QTimeEdit *timeEdit;
    QPushButton *pushButton_ComfirmT;
    QPushButton *pushButton_CancelT;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_1;
    QLabel *statusLabel;
    QTextEdit *textEdit;

    void setupUi(QWidget *FtpUpload)
    {
        if (FtpUpload->objectName().isEmpty())
            FtpUpload->setObjectName(QStringLiteral("FtpUpload"));
        FtpUpload->resize(545, 710);
        FtpUpload->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(FtpUpload);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        treeWidget = new QTreeWidget(FtpUpload);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\345\220\215\347\247\260"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(0, 130));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setAutoExpandDelay(-1);
        treeWidget->setAllColumnsShowFocus(true);
        treeWidget->setExpandsOnDoubleClick(true);
        treeWidget->header()->setDefaultSectionSize(100);
        treeWidget->header()->setMinimumSectionSize(20);

        gridLayout_3->addWidget(treeWidget, 6, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_Refush = new QPushButton(FtpUpload);
        pushButton_Refush->setObjectName(QStringLiteral("pushButton_Refush"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton_Refush->setFont(font);
        pushButton_Refush->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));

        gridLayout_2->addWidget(pushButton_Refush, 0, 0, 1, 1);

        pushButton_Back = new QPushButton(FtpUpload);
        pushButton_Back->setObjectName(QStringLiteral("pushButton_Back"));
        pushButton_Back->setFont(font);
        pushButton_Back->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));

        gridLayout_2->addWidget(pushButton_Back, 0, 1, 1, 1);

        uploadButton = new QPushButton(FtpUpload);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        uploadButton->setMinimumSize(QSize(67, 30));
        uploadButton->setFont(font);
        uploadButton->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(uploadButton, 0, 2, 1, 1);

        uploadButton_All = new QPushButton(FtpUpload);
        uploadButton_All->setObjectName(QStringLiteral("uploadButton_All"));
        uploadButton_All->setMinimumSize(QSize(100, 30));
        uploadButton_All->setFont(font);
        uploadButton_All->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(uploadButton_All, 0, 3, 1, 1);

        downloadButton = new QPushButton(FtpUpload);
        downloadButton->setObjectName(QStringLiteral("downloadButton"));
        downloadButton->setMinimumSize(QSize(67, 30));
        downloadButton->setFont(font);
        downloadButton->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(downloadButton, 0, 4, 1, 1);

        cancelBtn = new QPushButton(FtpUpload);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(67, 30));
        cancelBtn->setFont(font);
        cancelBtn->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(cancelBtn, 0, 5, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 9, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        ipLabel_7 = new QLabel(FtpUpload);
        ipLabel_7->setObjectName(QStringLiteral("ipLabel_7"));
        ipLabel_7->setFont(font);
        ipLabel_7->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_9->addWidget(ipLabel_7);

        lineEdit_DirPath_2 = new QLineEdit(FtpUpload);
        lineEdit_DirPath_2->setObjectName(QStringLiteral("lineEdit_DirPath_2"));
        lineEdit_DirPath_2->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        lineEdit_DirPath_2->setFont(font1);
        lineEdit_DirPath_2->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_DirPath_2->setFrame(true);

        horizontalLayout_9->addWidget(lineEdit_DirPath_2);

        toolButton_dir_2 = new QToolButton(FtpUpload);
        toolButton_dir_2->setObjectName(QStringLiteral("toolButton_dir_2"));
        toolButton_dir_2->setFont(font);
        toolButton_dir_2->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_9->addWidget(toolButton_dir_2);


        gridLayout_3->addLayout(horizontalLayout_9, 5, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ipLabel = new QLabel(FtpUpload);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setFont(font);
        ipLabel->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout_3->addWidget(ipLabel);

        ipLabel_2 = new QLabel(FtpUpload);
        ipLabel_2->setObjectName(QStringLiteral("ipLabel_2"));
        ipLabel_2->setFont(font);
        ipLabel_2->setLayoutDirection(Qt::LeftToRight);
        ipLabel_2->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout_3->addWidget(ipLabel_2);

        ipLabel_3 = new QLabel(FtpUpload);
        ipLabel_3->setObjectName(QStringLiteral("ipLabel_3"));
        ipLabel_3->setFont(font);
        ipLabel_3->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout_3->addWidget(ipLabel_3);

        ipLabel_4 = new QLabel(FtpUpload);
        ipLabel_4->setObjectName(QStringLiteral("ipLabel_4"));
        ipLabel_4->setFont(font);
        ipLabel_4->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout_3->addWidget(ipLabel_4);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lineEdit_Host = new QLineEdit(FtpUpload);
        lineEdit_Host->setObjectName(QStringLiteral("lineEdit_Host"));
        lineEdit_Host->setFont(font1);
        lineEdit_Host->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_Host->setFrame(true);

        verticalLayout_4->addWidget(lineEdit_Host);

        lineEdit_Port = new QLineEdit(FtpUpload);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setFont(font1);
        lineEdit_Port->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_Port->setFrame(true);

        verticalLayout_4->addWidget(lineEdit_Port);

        lineEdit_User = new QLineEdit(FtpUpload);
        lineEdit_User->setObjectName(QStringLiteral("lineEdit_User"));
        lineEdit_User->setFont(font1);
        lineEdit_User->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_User->setFrame(true);

        verticalLayout_4->addWidget(lineEdit_User);

        lineEdit_pad = new QLineEdit(FtpUpload);
        lineEdit_pad->setObjectName(QStringLiteral("lineEdit_pad"));
        lineEdit_pad->setFont(font1);
        lineEdit_pad->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_pad->setFrame(true);

        verticalLayout_4->addWidget(lineEdit_pad);


        horizontalLayout_6->addLayout(verticalLayout_4);


        gridLayout_3->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_Login = new QPushButton(FtpUpload);
        pushButton_Login->setObjectName(QStringLiteral("pushButton_Login"));
        pushButton_Login->setFont(font);
        pushButton_Login->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));

        horizontalLayout->addWidget(pushButton_Login);

        pushButton_Quit = new QPushButton(FtpUpload);
        pushButton_Quit->setObjectName(QStringLiteral("pushButton_Quit"));
        pushButton_Quit->setFont(font);
        pushButton_Quit->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));

        horizontalLayout->addWidget(pushButton_Quit);

        checkBox_AutoLogin = new QCheckBox(FtpUpload);
        checkBox_AutoLogin->setObjectName(QStringLiteral("checkBox_AutoLogin"));
        checkBox_AutoLogin->setFont(font);
        checkBox_AutoLogin->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout->addWidget(checkBox_AutoLogin);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(FtpUpload);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout->addWidget(label_2);

        radioButtonActive = new QRadioButton(FtpUpload);
        radioButtonActive->setObjectName(QStringLiteral("radioButtonActive"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(11);
        radioButtonActive->setFont(font2);
        radioButtonActive->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(radioButtonActive);

        radioButtonPassive = new QRadioButton(FtpUpload);
        radioButtonPassive->setObjectName(QStringLiteral("radioButtonPassive"));
        radioButtonPassive->setFont(font2);
        radioButtonPassive->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
""));

        horizontalLayout->addWidget(radioButtonPassive);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ipLabel_5 = new QLabel(FtpUpload);
        ipLabel_5->setObjectName(QStringLiteral("ipLabel_5"));
        ipLabel_5->setFont(font);
        ipLabel_5->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_4->addWidget(ipLabel_5);

        lineEdit_FilePath = new QLineEdit(FtpUpload);
        lineEdit_FilePath->setObjectName(QStringLiteral("lineEdit_FilePath"));
        lineEdit_FilePath->setFont(font1);
        lineEdit_FilePath->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_FilePath->setFrame(true);

        horizontalLayout_4->addWidget(lineEdit_FilePath);

        toolButton_file = new QToolButton(FtpUpload);
        toolButton_file->setObjectName(QStringLiteral("toolButton_file"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        toolButton_file->setFont(font3);
        toolButton_file->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_4->addWidget(toolButton_file);


        gridLayout_3->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        ipLabel_6 = new QLabel(FtpUpload);
        ipLabel_6->setObjectName(QStringLiteral("ipLabel_6"));
        ipLabel_6->setFont(font);
        ipLabel_6->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_5->addWidget(ipLabel_6);

        lineEdit_DirPath = new QLineEdit(FtpUpload);
        lineEdit_DirPath->setObjectName(QStringLiteral("lineEdit_DirPath"));
        lineEdit_DirPath->setMinimumSize(QSize(0, 0));
        lineEdit_DirPath->setFont(font1);
        lineEdit_DirPath->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_DirPath->setFrame(true);

        horizontalLayout_5->addWidget(lineEdit_DirPath);

        toolButton_dir = new QToolButton(FtpUpload);
        toolButton_dir->setObjectName(QStringLiteral("toolButton_dir"));
        toolButton_dir->setFont(font);
        toolButton_dir->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_5->addWidget(toolButton_dir);


        gridLayout_3->addLayout(horizontalLayout_5, 4, 0, 1, 1);

        widget = new QWidget(FtpUpload);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 60));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(54, 54, 54);"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(101, 21));
        label->setMaximumSize(QSize(111, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setWeight(75);
        label->setFont(font4);
        label->setMouseTracking(true);
        label->setAcceptDrops(true);
        label->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label->setMargin(0);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(278, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        setButton = new QPushButton(widget);
        setButton->setObjectName(QStringLiteral("setButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(setButton->sizePolicy().hasHeightForWidth());
        setButton->setSizePolicy(sizePolicy);
        setButton->setMinimumSize(QSize(23, 23));
        setButton->setMaximumSize(QSize(23, 23));
        setButton->setStyleSheet(QLatin1String("         QPushButton{ border-image:url(:/img/img/Help_btn.png) 66 0 33 0 ;}\n"
"   QPushButton:hover{ border-image:url(:/img/img/Help_btn.png) 33 0 66 0 ;}\n"
" QPushButton:pressed{ border-image:url(:/img/img/Help_btn.png) 66 0 33 0 ;}\n"
"QPushButton:disabled{ border-image:url(:/img/img/Help_btn.png) 99 0 0 0 ;}"));
        setButton->setIconSize(QSize(23, 23));

        horizontalLayout_8->addWidget(setButton);

        minButton = new QPushButton(widget);
        minButton->setObjectName(QStringLiteral("minButton"));
        sizePolicy.setHeightForWidth(minButton->sizePolicy().hasHeightForWidth());
        minButton->setSizePolicy(sizePolicy);
        minButton->setMinimumSize(QSize(23, 23));
        minButton->setMaximumSize(QSize(23, 23));
        minButton->setStyleSheet(QLatin1String("         QPushButton{ border-image:url(:/img/img/min_btn.png) 66 0 33 0 ;}\n"
"   QPushButton:hover{ border-image:url(:/img/img/min_btn.png) 33 0 66 0 ;}\n"
" QPushButton:pressed{ border-image:url(:/img/img/min_btn.png) 66 0 33 0 ;}\n"
"QPushButton:disabled{ border-image:url(:/img/img/min_btn.png) 99 0 0 0 ;}"));

        horizontalLayout_8->addWidget(minButton);

        closeButton = new QPushButton(widget);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);
        closeButton->setMinimumSize(QSize(23, 23));
        closeButton->setMaximumSize(QSize(23, 23));
        closeButton->setStyleSheet(QLatin1String("QPushButton{ border-image:url(:/img/img/close_btn.png) 66 0 33 0 ;}\n"
"QPushButton:hover{ border-image:url(:/img/img/close_btn.png) 33 0 66 0 ;}\n"
" QPushButton:pressed{ border-image:url(:/img/img/close_btn.png) 66 0 33 0 ;}\n"
"QPushButton:disabled{ border-image:url(:/img/img/close_btn.png) 99 0 0 0 ;}"));

        horizontalLayout_8->addWidget(closeButton);


        verticalLayout_6->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_6, 0, 2, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButton = new QRadioButton(FtpUpload);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setMinimumSize(QSize(0, 30));
        radioButton->setFont(font);
        radioButton->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_2->addWidget(radioButton);

        CB_EncodingFormat = new QComboBox(FtpUpload);
        CB_EncodingFormat->setObjectName(QStringLiteral("CB_EncodingFormat"));
        CB_EncodingFormat->setMinimumSize(QSize(0, 30));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font5.setPointSize(11);
        font5.setBold(true);
        font5.setWeight(75);
        CB_EncodingFormat->setFont(font5);

        horizontalLayout_2->addWidget(CB_EncodingFormat);

        timeEdit = new QTimeEdit(FtpUpload);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumSize(QSize(0, 30));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font6.setPointSize(12);
        timeEdit->setFont(font6);
        timeEdit->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_2->addWidget(timeEdit);

        pushButton_ComfirmT = new QPushButton(FtpUpload);
        pushButton_ComfirmT->setObjectName(QStringLiteral("pushButton_ComfirmT"));
        pushButton_ComfirmT->setMinimumSize(QSize(0, 30));
        QFont font7;
        font7.setFamily(QStringLiteral("Arial"));
        font7.setPointSize(12);
        font7.setBold(true);
        font7.setWeight(75);
        pushButton_ComfirmT->setFont(font7);
        pushButton_ComfirmT->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_2->addWidget(pushButton_ComfirmT);

        pushButton_CancelT = new QPushButton(FtpUpload);
        pushButton_CancelT->setObjectName(QStringLiteral("pushButton_CancelT"));
        pushButton_CancelT->setMinimumSize(QSize(0, 30));
        pushButton_CancelT->setFont(font7);
        pushButton_CancelT->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_2->addWidget(pushButton_CancelT);


        gridLayout_3->addLayout(horizontalLayout_2, 10, 0, 1, 1);

        progressBar = new QProgressBar(FtpUpload);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setLayoutDirection(Qt::LeftToRight);
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
        progressBar->setMaximum(100);
        progressBar->setValue(20);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        gridLayout_3->addWidget(progressBar, 11, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_1 = new QLabel(FtpUpload);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setMaximumSize(QSize(16777215, 16777215));
        label_1->setFont(font);
        label_1->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_3->addWidget(label_1);

        statusLabel = new QLabel(FtpUpload);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setMinimumSize(QSize(430, 0));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font8.setPointSize(12);
        font8.setBold(false);
        font8.setWeight(50);
        statusLabel->setFont(font8);
        statusLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(statusLabel);


        gridLayout_3->addLayout(horizontalLayout_3, 12, 0, 1, 1);

        textEdit = new QTextEdit(FtpUpload);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        textEdit->setMinimumSize(QSize(0, 150));
        textEdit->setMaximumSize(QSize(16777215, 16777215));
        textEdit->setFont(font1);
        textEdit->setMouseTracking(true);
        textEdit->setStyleSheet(QStringLiteral("QTextEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout_3->addWidget(textEdit, 13, 0, 1, 1);


        retranslateUi(FtpUpload);

        QMetaObject::connectSlotsByName(FtpUpload);
    } // setupUi

    void retranslateUi(QWidget *FtpUpload)
    {
        FtpUpload->setWindowTitle(QApplication::translate("FtpUpload", "FtpUpload", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("FtpUpload", "\347\273\204", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("FtpUpload", "\346\235\203\351\231\220", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("FtpUpload", "\346\227\245\346\234\237", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("FtpUpload", "\345\244\247\345\260\217", Q_NULLPTR));
        pushButton_Refush->setText(QApplication::translate("FtpUpload", "\345\210\267\346\226\260", Q_NULLPTR));
        pushButton_Back->setText(QApplication::translate("FtpUpload", "\350\277\224\345\233\236\344\270\212\344\270\200\347\272\247", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("FtpUpload", "\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        uploadButton_All->setText(QApplication::translate("FtpUpload", "\346\211\271\351\207\217\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        downloadButton->setText(QApplication::translate("FtpUpload", "\344\270\213\350\275\275", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("FtpUpload", "\345\217\226\346\266\210", Q_NULLPTR));
        ipLabel_7->setText(QApplication::translate("FtpUpload", "  \346\226\207\344\273\266\345\244\271\344\270\212\344\274\240   ", Q_NULLPTR));
        lineEdit_DirPath_2->setText(QString());
        lineEdit_DirPath_2->setPlaceholderText(QApplication::translate("FtpUpload", "\346\226\207\344\273\266\345\244\271\344\270\212\344\274\240", Q_NULLPTR));
        toolButton_dir_2->setText(QApplication::translate("FtpUpload", "...", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("FtpUpload", "  \346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232 ", Q_NULLPTR));
        ipLabel_2->setText(QApplication::translate("FtpUpload", "        \347\253\257\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        ipLabel_3->setText(QApplication::translate("FtpUpload", "        \347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        ipLabel_4->setText(QApplication::translate("FtpUpload", "           \345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        lineEdit_Host->setText(QString());
        lineEdit_Port->setText(QString());
        lineEdit_User->setText(QString());
        lineEdit_pad->setText(QString());
        pushButton_Login->setText(QApplication::translate("FtpUpload", "\347\231\273\345\275\225", Q_NULLPTR));
        pushButton_Quit->setText(QApplication::translate("FtpUpload", "\351\200\200\345\207\272", Q_NULLPTR));
        checkBox_AutoLogin->setText(QApplication::translate("FtpUpload", "\350\207\252\345\212\250\347\231\273\345\275\225", Q_NULLPTR));
        label_2->setText(QApplication::translate("FtpUpload", "\344\274\240\350\276\223\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        radioButtonActive->setText(QApplication::translate("FtpUpload", "\344\270\273\345\212\250", Q_NULLPTR));
        radioButtonPassive->setText(QApplication::translate("FtpUpload", "\350\242\253\345\212\250", Q_NULLPTR));
        ipLabel_5->setText(QApplication::translate("FtpUpload", "  \346\226\207\344\273\266\344\270\212\344\274\240  ", Q_NULLPTR));
        lineEdit_FilePath->setText(QString());
        lineEdit_FilePath->setPlaceholderText(QApplication::translate("FtpUpload", "\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        toolButton_file->setText(QApplication::translate("FtpUpload", "...", Q_NULLPTR));
        ipLabel_6->setText(QApplication::translate("FtpUpload", "  \346\226\207\344\273\266\345\244\271\345\256\232\346\227\266\344\270\212\344\274\240  ", Q_NULLPTR));
        lineEdit_DirPath->setText(QString());
        lineEdit_DirPath->setPlaceholderText(QApplication::translate("FtpUpload", "\346\211\271\351\207\217\346\226\207\344\273\266\344\270\212\344\274\240\343\200\201\345\256\232\346\227\266\344\270\212\344\274\240\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        toolButton_dir->setText(QApplication::translate("FtpUpload", "...", Q_NULLPTR));
        label->setText(QApplication::translate("FtpUpload", "FTP\345\256\242\346\210\267\347\253\257", Q_NULLPTR));
        setButton->setText(QString());
        minButton->setText(QString());
        closeButton->setText(QString());
        radioButton->setText(QApplication::translate("FtpUpload", "\346\211\271\351\207\217\344\270\212\344\274\240", Q_NULLPTR));
        timeEdit->setDisplayFormat(QApplication::translate("FtpUpload", "H:mm:ss", Q_NULLPTR));
        pushButton_ComfirmT->setText(QApplication::translate("FtpUpload", "\347\241\256\350\256\244\345\256\232\346\227\266\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_CancelT->setText(QApplication::translate("FtpUpload", "\345\217\226\346\266\210\345\256\232\346\227\266\344\270\212\344\274\240", Q_NULLPTR));
        label_1->setText(QApplication::translate("FtpUpload", "\347\212\266\346\200\201\357\274\232", Q_NULLPTR));
        statusLabel->setText(QApplication::translate("FtpUpload", "\346\227\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FtpUpload: public Ui_FtpUpload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTPUPLOAD_H
