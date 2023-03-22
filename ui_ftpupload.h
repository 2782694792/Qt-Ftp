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
#include <QtWidgets/QFrame>
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
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *setButton;
    QPushButton *minButton;
    QPushButton *closeButton;
    QLabel *label_auto;
    QSpacerItem *horizontalSpacer_9;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_3;
    QLineEdit *lineEdit_factory;
    QLabel *label_4;
    QLineEdit *lineEdit_procedure;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QLineEdit *lineEdit_manufacturer;
    QLabel *label_6;
    QLineEdit *lineEdit_number;
    QLabel *label_7;
    QLineEdit *lineEdit_station;
    QFrame *line_2;
    QLabel *label_currentpath;
    QTreeWidget *treeWidget;
    QFrame *line;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *ipLabel;
    QLabel *ipLabel_3;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit_Host;
    QLineEdit *lineEdit_User;
    QVBoxLayout *verticalLayout;
    QLabel *ipLabel_2;
    QLabel *ipLabel_4;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_Port;
    QLineEdit *lineEdit_pad;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *ipLabel_5;
    QLineEdit *lineEdit_FilePath;
    QToolButton *toolButton_file;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QLabel *ipLabel_7;
    QLineEdit *lineEdit_DirPath_2;
    QToolButton *toolButton_dir_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_1;
    QLabel *statusLabel;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_12;
    QTextEdit *textEdit;
    QTextEdit *textEdit_fail;
    QHBoxLayout *horizontalLayout_5;
    QLabel *ipLabel_6;
    QLineEdit *lineEdit_DirPath;
    QToolButton *toolButton_dir;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Login;
    QPushButton *pushButton_Quit;
    QCheckBox *checkBox_AutoLogin;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_8;
    QComboBox *CB_EncodingFormat;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_2;
    QRadioButton *radioButtonActive;
    QRadioButton *radioButtonPassive;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *uploadButton;
    QPushButton *pushButton_Refush;
    QPushButton *downloadButton;
    QPushButton *cancelBtn;
    QPushButton *uploadButton_All;
    QSpacerItem *horizontalSpacer_7;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_Back;
    QSpacerItem *horizontalSpacer_4;
    QTimeEdit *timeEdit;
    QFrame *line_4;
    QTimeEdit *timeEdit_evening;
    QPushButton *pushButton_ComfirmT;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_CancelT;
    QSpacerItem *verticalSpacer;
    QFrame *line_3;

    void setupUi(QWidget *FtpUpload)
    {
        if (FtpUpload->objectName().isEmpty())
            FtpUpload->setObjectName(QStringLiteral("FtpUpload"));
        FtpUpload->resize(578, 704);
        FtpUpload->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/img/FTP.png"), QSize(), QIcon::Normal, QIcon::Off);
        FtpUpload->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(FtpUpload);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
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
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(90, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setMouseTracking(true);
        label->setAcceptDrops(true);
        label->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label->setMargin(0);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

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


        gridLayout->addLayout(verticalLayout_6, 0, 4, 1, 1);

        label_auto = new QLabel(widget);
        label_auto->setObjectName(QStringLiteral("label_auto"));
        label_auto->setFont(font);
        label_auto->setStyleSheet(QStringLiteral("color: yellow;"));

        gridLayout->addWidget(label_auto, 0, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 0, 3, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_3 = new QLabel(FtpUpload);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_3->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_13->addWidget(label_3);

        lineEdit_factory = new QLineEdit(FtpUpload);
        lineEdit_factory->setObjectName(QStringLiteral("lineEdit_factory"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        lineEdit_factory->setFont(font2);
        lineEdit_factory->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));

        horizontalLayout_13->addWidget(lineEdit_factory);

        label_4 = new QLabel(FtpUpload);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);
        label_4->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_13->addWidget(label_4);

        lineEdit_procedure = new QLineEdit(FtpUpload);
        lineEdit_procedure->setObjectName(QStringLiteral("lineEdit_procedure"));
        lineEdit_procedure->setFont(font2);
        lineEdit_procedure->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));

        horizontalLayout_13->addWidget(lineEdit_procedure);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_5 = new QLabel(FtpUpload);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);
        label_5->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_10->addWidget(label_5);

        lineEdit_manufacturer = new QLineEdit(FtpUpload);
        lineEdit_manufacturer->setObjectName(QStringLiteral("lineEdit_manufacturer"));
        lineEdit_manufacturer->setFont(font2);
        lineEdit_manufacturer->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));

        horizontalLayout_10->addWidget(lineEdit_manufacturer);

        label_6 = new QLabel(FtpUpload);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);
        label_6->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_10->addWidget(label_6);

        lineEdit_number = new QLineEdit(FtpUpload);
        lineEdit_number->setObjectName(QStringLiteral("lineEdit_number"));
        lineEdit_number->setFont(font2);
        lineEdit_number->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));

        horizontalLayout_10->addWidget(lineEdit_number);

        label_7 = new QLabel(FtpUpload);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);
        label_7->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_10->addWidget(label_7);

        lineEdit_station = new QLineEdit(FtpUpload);
        lineEdit_station->setObjectName(QStringLiteral("lineEdit_station"));
        lineEdit_station->setFont(font2);
        lineEdit_station->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));

        horizontalLayout_10->addWidget(lineEdit_station);


        verticalLayout_5->addLayout(horizontalLayout_10);

        line_2 = new QFrame(FtpUpload);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        label_currentpath = new QLabel(FtpUpload);
        label_currentpath->setObjectName(QStringLiteral("label_currentpath"));
        label_currentpath->setMinimumSize(QSize(0, 0));
        label_currentpath->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        label_currentpath->setFont(font3);
        label_currentpath->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_currentpath->setTextFormat(Qt::PlainText);
        label_currentpath->setWordWrap(true);

        verticalLayout_5->addWidget(label_currentpath);

        treeWidget = new QTreeWidget(FtpUpload);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\345\220\215\347\247\260"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(0, 150));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setAutoFillBackground(true);
        treeWidget->setMidLineWidth(50);
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        treeWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        treeWidget->setAutoExpandDelay(-1);
        treeWidget->setIndentation(17);
        treeWidget->setAllColumnsShowFocus(true);
        treeWidget->setExpandsOnDoubleClick(true);
        treeWidget->header()->setVisible(false);
        treeWidget->header()->setDefaultSectionSize(150);
        treeWidget->header()->setHighlightSections(true);
        treeWidget->header()->setMinimumSectionSize(50);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(false));
        treeWidget->header()->setStretchLastSection(true);

        verticalLayout_5->addWidget(treeWidget);


        gridLayout_3->addLayout(verticalLayout_5, 7, 0, 1, 1);

        line = new QFrame(FtpUpload);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ipLabel = new QLabel(FtpUpload);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setFont(font1);
        ipLabel->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout_3->addWidget(ipLabel);

        ipLabel_3 = new QLabel(FtpUpload);
        ipLabel_3->setObjectName(QStringLiteral("ipLabel_3"));
        ipLabel_3->setFont(font1);
        ipLabel_3->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout_3->addWidget(ipLabel_3);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lineEdit_Host = new QLineEdit(FtpUpload);
        lineEdit_Host->setObjectName(QStringLiteral("lineEdit_Host"));
        lineEdit_Host->setFont(font2);
        lineEdit_Host->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_Host->setFrame(true);

        verticalLayout_4->addWidget(lineEdit_Host);

        lineEdit_User = new QLineEdit(FtpUpload);
        lineEdit_User->setObjectName(QStringLiteral("lineEdit_User"));
        lineEdit_User->setFont(font2);
        lineEdit_User->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_User->setFrame(true);

        verticalLayout_4->addWidget(lineEdit_User);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ipLabel_2 = new QLabel(FtpUpload);
        ipLabel_2->setObjectName(QStringLiteral("ipLabel_2"));
        ipLabel_2->setFont(font1);
        ipLabel_2->setLayoutDirection(Qt::LeftToRight);
        ipLabel_2->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout->addWidget(ipLabel_2);

        ipLabel_4 = new QLabel(FtpUpload);
        ipLabel_4->setObjectName(QStringLiteral("ipLabel_4"));
        ipLabel_4->setFont(font1);
        ipLabel_4->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        verticalLayout->addWidget(ipLabel_4);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lineEdit_Port = new QLineEdit(FtpUpload);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setFont(font2);
        lineEdit_Port->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_Port->setFrame(true);

        verticalLayout_2->addWidget(lineEdit_Port);

        lineEdit_pad = new QLineEdit(FtpUpload);
        lineEdit_pad->setObjectName(QStringLiteral("lineEdit_pad"));
        lineEdit_pad->setFont(font2);
        lineEdit_pad->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_pad->setFrame(true);

        verticalLayout_2->addWidget(lineEdit_pad);


        horizontalLayout_6->addLayout(verticalLayout_2);


        gridLayout_3->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        ipLabel_5 = new QLabel(FtpUpload);
        ipLabel_5->setObjectName(QStringLiteral("ipLabel_5"));
        ipLabel_5->setFont(font1);
        ipLabel_5->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_7->addWidget(ipLabel_5);

        lineEdit_FilePath = new QLineEdit(FtpUpload);
        lineEdit_FilePath->setObjectName(QStringLiteral("lineEdit_FilePath"));
        lineEdit_FilePath->setFont(font2);
        lineEdit_FilePath->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_FilePath->setFrame(true);

        horizontalLayout_7->addWidget(lineEdit_FilePath);

        toolButton_file = new QToolButton(FtpUpload);
        toolButton_file->setObjectName(QStringLiteral("toolButton_file"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setItalic(false);
        font4.setWeight(75);
        toolButton_file->setFont(font4);
        toolButton_file->setCursor(QCursor(Qt::OpenHandCursor));
        toolButton_file->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_7->addWidget(toolButton_file);


        horizontalLayout_4->addLayout(horizontalLayout_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        ipLabel_7 = new QLabel(FtpUpload);
        ipLabel_7->setObjectName(QStringLiteral("ipLabel_7"));
        ipLabel_7->setFont(font1);
        ipLabel_7->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_9->addWidget(ipLabel_7);

        lineEdit_DirPath_2 = new QLineEdit(FtpUpload);
        lineEdit_DirPath_2->setObjectName(QStringLiteral("lineEdit_DirPath_2"));
        lineEdit_DirPath_2->setMinimumSize(QSize(0, 0));
        lineEdit_DirPath_2->setFont(font2);
        lineEdit_DirPath_2->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_DirPath_2->setFrame(true);

        horizontalLayout_9->addWidget(lineEdit_DirPath_2);

        toolButton_dir_2 = new QToolButton(FtpUpload);
        toolButton_dir_2->setObjectName(QStringLiteral("toolButton_dir_2"));
        toolButton_dir_2->setFont(font1);
        toolButton_dir_2->setCursor(QCursor(Qt::OpenHandCursor));
        toolButton_dir_2->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_9->addWidget(toolButton_dir_2);


        horizontalLayout_4->addLayout(horizontalLayout_9);


        gridLayout_3->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_1 = new QLabel(FtpUpload);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setMinimumSize(QSize(0, 0));
        label_1->setMaximumSize(QSize(16777215, 16777213));
        label_1->setFont(font1);
        label_1->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_3->addWidget(label_1);

        statusLabel = new QLabel(FtpUpload);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setMinimumSize(QSize(450, 0));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font5.setPointSize(12);
        font5.setBold(false);
        font5.setWeight(50);
        statusLabel->setFont(font5);
        statusLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        statusLabel->setTextFormat(Qt::PlainText);

        horizontalLayout_3->addWidget(statusLabel);


        verticalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(FtpUpload);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font1);
        label_10->setStyleSheet(QStringLiteral("color: green;"));

        horizontalLayout_11->addWidget(label_10);

        label_9 = new QLabel(FtpUpload);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font1);
        label_9->setStyleSheet(QStringLiteral("color: red;"));

        horizontalLayout_11->addWidget(label_9);


        verticalLayout_7->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        textEdit = new QTextEdit(FtpUpload);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font6.setPointSize(8);
        font6.setBold(false);
        font6.setWeight(50);
        textEdit->setFont(font6);
        textEdit->setStyleSheet(QStringLiteral("QTextEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));

        horizontalLayout_12->addWidget(textEdit);

        textEdit_fail = new QTextEdit(FtpUpload);
        textEdit_fail->setObjectName(QStringLiteral("textEdit_fail"));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font7.setPointSize(8);
        font7.setBold(true);
        font7.setWeight(75);
        textEdit_fail->setFont(font7);
        textEdit_fail->setStyleSheet(QStringLiteral("QTextEdit{border:1px solid #828282;color: red;background:transparent;}"));

        horizontalLayout_12->addWidget(textEdit_fail);


        verticalLayout_7->addLayout(horizontalLayout_12);


        gridLayout_3->addLayout(verticalLayout_7, 16, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        ipLabel_6 = new QLabel(FtpUpload);
        ipLabel_6->setObjectName(QStringLiteral("ipLabel_6"));
        ipLabel_6->setFont(font1);
        ipLabel_6->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_5->addWidget(ipLabel_6);

        lineEdit_DirPath = new QLineEdit(FtpUpload);
        lineEdit_DirPath->setObjectName(QStringLiteral("lineEdit_DirPath"));
        lineEdit_DirPath->setMinimumSize(QSize(0, 0));
        lineEdit_DirPath->setFont(font2);
        lineEdit_DirPath->setStyleSheet(QStringLiteral("QLineEdit{border:1px solid #828282;color: rgb(255, 255, 255);background:transparent;}"));
        lineEdit_DirPath->setFrame(true);

        horizontalLayout_5->addWidget(lineEdit_DirPath);

        toolButton_dir = new QToolButton(FtpUpload);
        toolButton_dir->setObjectName(QStringLiteral("toolButton_dir"));
        toolButton_dir->setFont(font1);
        toolButton_dir->setCursor(QCursor(Qt::OpenHandCursor));
        toolButton_dir->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout_5->addWidget(toolButton_dir);


        gridLayout_3->addLayout(horizontalLayout_5, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_Login = new QPushButton(FtpUpload);
        pushButton_Login->setObjectName(QStringLiteral("pushButton_Login"));
        pushButton_Login->setFont(font1);
        pushButton_Login->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));
        pushButton_Login->setAutoDefault(false);

        horizontalLayout->addWidget(pushButton_Login);

        pushButton_Quit = new QPushButton(FtpUpload);
        pushButton_Quit->setObjectName(QStringLiteral("pushButton_Quit"));
        pushButton_Quit->setFont(font1);
        pushButton_Quit->setCursor(QCursor(Qt::ClosedHandCursor));
        pushButton_Quit->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));

        horizontalLayout->addWidget(pushButton_Quit);

        checkBox_AutoLogin = new QCheckBox(FtpUpload);
        checkBox_AutoLogin->setObjectName(QStringLiteral("checkBox_AutoLogin"));
        checkBox_AutoLogin->setFont(font1);
        checkBox_AutoLogin->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout->addWidget(checkBox_AutoLogin);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_8 = new QLabel(FtpUpload);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font1);
        label_8->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout->addWidget(label_8);

        CB_EncodingFormat = new QComboBox(FtpUpload);
        CB_EncodingFormat->setObjectName(QStringLiteral("CB_EncodingFormat"));
        CB_EncodingFormat->setMinimumSize(QSize(0, 0));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font8.setPointSize(11);
        font8.setBold(true);
        font8.setWeight(75);
        CB_EncodingFormat->setFont(font8);
        CB_EncodingFormat->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout->addWidget(CB_EncodingFormat);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        label_2 = new QLabel(FtpUpload);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        horizontalLayout->addWidget(label_2);

        radioButtonActive = new QRadioButton(FtpUpload);
        radioButtonActive->setObjectName(QStringLiteral("radioButtonActive"));
        QFont font9;
        font9.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font9.setPointSize(11);
        radioButtonActive->setFont(font9);
        radioButtonActive->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(radioButtonActive);

        radioButtonPassive = new QRadioButton(FtpUpload);
        radioButtonPassive->setObjectName(QStringLiteral("radioButtonPassive"));
        radioButtonPassive->setFont(font9);
        radioButtonPassive->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
""));

        horizontalLayout->addWidget(radioButtonPassive);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        uploadButton = new QPushButton(FtpUpload);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        uploadButton->setMinimumSize(QSize(50, 0));
        uploadButton->setFont(font1);
        uploadButton->setCursor(QCursor(Qt::PointingHandCursor));
        uploadButton->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(uploadButton, 0, 2, 1, 1);

        pushButton_Refush = new QPushButton(FtpUpload);
        pushButton_Refush->setObjectName(QStringLiteral("pushButton_Refush"));
        pushButton_Refush->setMinimumSize(QSize(0, 0));
        pushButton_Refush->setFont(font1);
        pushButton_Refush->setCursor(QCursor(Qt::OpenHandCursor));
        pushButton_Refush->setStyleSheet(QLatin1String("color: rgb(146, 189, 108);\n"
""));

        gridLayout_2->addWidget(pushButton_Refush, 0, 0, 1, 1);

        downloadButton = new QPushButton(FtpUpload);
        downloadButton->setObjectName(QStringLiteral("downloadButton"));
        downloadButton->setMinimumSize(QSize(50, 0));
        downloadButton->setFont(font1);
        downloadButton->setCursor(QCursor(Qt::PointingHandCursor));
        downloadButton->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(downloadButton, 0, 3, 1, 1);

        cancelBtn = new QPushButton(FtpUpload);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 0));
        cancelBtn->setFont(font5);
        cancelBtn->setCursor(QCursor(Qt::ClosedHandCursor));
        cancelBtn->setStyleSheet(QStringLiteral("color: red;"));

        gridLayout_2->addWidget(cancelBtn, 0, 6, 1, 1);

        uploadButton_All = new QPushButton(FtpUpload);
        uploadButton_All->setObjectName(QStringLiteral("uploadButton_All"));
        uploadButton_All->setMinimumSize(QSize(100, 0));
        uploadButton_All->setFont(font1);
        uploadButton_All->setCursor(QCursor(Qt::PointingHandCursor));
        uploadButton_All->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));

        gridLayout_2->addWidget(uploadButton_All, 0, 4, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 5, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 11, 0, 1, 1);

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

        gridLayout_3->addWidget(progressBar, 14, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_Back = new QPushButton(FtpUpload);
        pushButton_Back->setObjectName(QStringLiteral("pushButton_Back"));
        pushButton_Back->setMinimumSize(QSize(110, 0));
        pushButton_Back->setFont(font1);
        pushButton_Back->setCursor(QCursor(Qt::OpenHandCursor));
        pushButton_Back->setStyleSheet(QLatin1String("color: rgb(0, 142, 213);\n"
""));

        horizontalLayout_2->addWidget(pushButton_Back);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        timeEdit = new QTimeEdit(FtpUpload);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumSize(QSize(50, 0));
        QFont font10;
        font10.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font10.setPointSize(12);
        timeEdit->setFont(font10);
        timeEdit->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));
        timeEdit->setMaximumTime(QTime(23, 54, 59));
        timeEdit->setMinimumTime(QTime(0, 0, 0));
        timeEdit->setTime(QTime(0, 0, 0));

        horizontalLayout_2->addWidget(timeEdit);

        line_4 = new QFrame(FtpUpload);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setMinimumSize(QSize(20, 0));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_4);

        timeEdit_evening = new QTimeEdit(FtpUpload);
        timeEdit_evening->setObjectName(QStringLiteral("timeEdit_evening"));
        timeEdit_evening->setMinimumSize(QSize(50, 0));
        timeEdit_evening->setFont(font5);
        timeEdit_evening->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));
        timeEdit_evening->setTime(QTime(0, 0, 0));

        horizontalLayout_2->addWidget(timeEdit_evening);

        pushButton_ComfirmT = new QPushButton(FtpUpload);
        pushButton_ComfirmT->setObjectName(QStringLiteral("pushButton_ComfirmT"));
        pushButton_ComfirmT->setMinimumSize(QSize(100, 0));
        pushButton_ComfirmT->setFont(font1);
        pushButton_ComfirmT->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_ComfirmT->setStyleSheet(QStringLiteral("color: rgb(0, 142, 213);"));
        pushButton_ComfirmT->setAutoRepeatInterval(100);

        horizontalLayout_2->addWidget(pushButton_ComfirmT);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButton_CancelT = new QPushButton(FtpUpload);
        pushButton_CancelT->setObjectName(QStringLiteral("pushButton_CancelT"));
        pushButton_CancelT->setMinimumSize(QSize(110, 0));
        pushButton_CancelT->setFont(font1);
        pushButton_CancelT->setCursor(QCursor(Qt::ClosedHandCursor));
        pushButton_CancelT->setStyleSheet(QStringLiteral("color: rgb(245, 134, 45);"));

        horizontalLayout_2->addWidget(pushButton_CancelT);


        gridLayout_3->addLayout(horizontalLayout_2, 12, 0, 1, 1);

        verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer, 6, 0, 1, 1);

        line_3 = new QFrame(FtpUpload);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 13, 0, 1, 1);


        retranslateUi(FtpUpload);

        pushButton_Login->setDefault(false);


        QMetaObject::connectSlotsByName(FtpUpload);
    } // setupUi

    void retranslateUi(QWidget *FtpUpload)
    {
        FtpUpload->setWindowTitle(QApplication::translate("FtpUpload", "FtpUpload", Q_NULLPTR));
        label->setText(QApplication::translate("FtpUpload", "FTP\345\256\242\346\210\267\347\253\257", Q_NULLPTR));
        setButton->setText(QString());
        minButton->setText(QString());
        closeButton->setText(QString());
        label_auto->setText(QString());
        label_3->setText(QApplication::translate("FtpUpload", "  \345\267\245\345\216\202  ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_factory->setToolTip(QApplication::translate("FtpUpload", "\345\220\215\347\247\260\344\270\215\350\203\275\345\214\205\345\220\253\344\273\273\344\275\225\345\255\227\347\254\246:\n"
"\\\\/:*?\"<>|", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit_factory->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        lineEdit_factory->setAccessibleDescription(QApplication::translate("FtpUpload", "\345\220\215\347\247\260\344\270\215\350\203\275\345\214\205\345\220\253\344\273\273\344\275\225\345\255\227\347\254\246:\n"
"\\\\/:*?\"<>|", Q_NULLPTR));
#endif // QT_NO_ACCESSIBILITY
        lineEdit_factory->setPlaceholderText(QString());
        label_4->setText(QApplication::translate("FtpUpload", "  \345\267\245\345\272\217  ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_procedure->setToolTip(QApplication::translate("FtpUpload", "\345\220\215\347\247\260\344\270\215\350\203\275\345\214\205\345\220\253\344\273\273\344\275\225\345\255\227\347\254\246:\n"
"\\\\/:*?\"<>|", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("FtpUpload", "  \350\256\276\345\244\207\345\216\202\345\256\266", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_manufacturer->setToolTip(QApplication::translate("FtpUpload", "\345\220\215\347\247\260\344\270\215\350\203\275\345\214\205\345\220\253\344\273\273\344\275\225\345\255\227\347\254\246:\n"
"\\\\/:*?\"<>|", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_6->setText(QApplication::translate("FtpUpload", " \350\256\276\345\244\207\347\274\226\345\217\267", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_number->setToolTip(QApplication::translate("FtpUpload", "\345\220\215\347\247\260\344\270\215\350\203\275\345\214\205\345\220\253\344\273\273\344\275\225\345\255\227\347\254\246:\n"
"\\\\/:*?\"<>|", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("FtpUpload", " \345\257\271\345\272\224\345\267\245\344\275\215", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_station->setToolTip(QApplication::translate("FtpUpload", "\345\220\215\347\247\260\344\270\215\350\203\275\345\214\205\345\220\253\344\273\273\344\275\225\345\255\227\347\254\246:\n"
"\\\\/:*?\"<>|", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_currentpath->setText(QApplication::translate("FtpUpload", "  \345\275\223\345\211\215\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("FtpUpload", "\347\273\204", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("FtpUpload", "\346\235\203\351\231\220", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("FtpUpload", "\346\227\245\346\234\237", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("FtpUpload", "\345\244\247\345\260\217", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("FtpUpload", "  \346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232 ", Q_NULLPTR));
        ipLabel_3->setText(QApplication::translate("FtpUpload", "        \347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        lineEdit_Host->setText(QString());
        lineEdit_User->setText(QString());
        ipLabel_2->setText(QApplication::translate("FtpUpload", "        \347\253\257\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        ipLabel_4->setText(QApplication::translate("FtpUpload", "           \345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        lineEdit_Port->setText(QString());
        lineEdit_pad->setText(QString());
        ipLabel_5->setText(QApplication::translate("FtpUpload", "  \346\226\207\344\273\266:  ", Q_NULLPTR));
        lineEdit_FilePath->setText(QString());
        lineEdit_FilePath->setPlaceholderText(QApplication::translate("FtpUpload", "\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        toolButton_file->setText(QApplication::translate("FtpUpload", "...", Q_NULLPTR));
        ipLabel_7->setText(QApplication::translate("FtpUpload", "    \346\226\207\344\273\266\345\244\271:  ", Q_NULLPTR));
        lineEdit_DirPath_2->setText(QString());
        lineEdit_DirPath_2->setPlaceholderText(QApplication::translate("FtpUpload", "\346\226\207\344\273\266\345\244\271\344\270\212\344\274\240", Q_NULLPTR));
        toolButton_dir_2->setText(QApplication::translate("FtpUpload", "...", Q_NULLPTR));
        label_1->setText(QApplication::translate("FtpUpload", "  \347\212\266\346\200\201\357\274\232", Q_NULLPTR));
        statusLabel->setText(QApplication::translate("FtpUpload", "\346\227\240", Q_NULLPTR));
        label_10->setText(QApplication::translate("FtpUpload", "  \346\223\215\344\275\234\345\206\205\345\256\271\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("FtpUpload", "  \345\274\202\345\270\270\344\277\241\346\201\257\357\274\232", Q_NULLPTR));
        ipLabel_6->setText(QApplication::translate("FtpUpload", "  \345\256\232\346\227\266\346\226\207\344\273\266\345\244\271: ", Q_NULLPTR));
        lineEdit_DirPath->setText(QString());
        lineEdit_DirPath->setPlaceholderText(QApplication::translate("FtpUpload", "\345\256\232\346\227\266\344\270\212\344\274\240\346\226\207\344\273\266\345\244\271\343\200\201\346\211\271\351\207\217\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        toolButton_dir->setText(QApplication::translate("FtpUpload", "...", Q_NULLPTR));
        pushButton_Login->setText(QApplication::translate("FtpUpload", "\347\231\273\345\275\225", Q_NULLPTR));
        pushButton_Quit->setText(QApplication::translate("FtpUpload", "\351\200\200\345\207\272", Q_NULLPTR));
        checkBox_AutoLogin->setText(QApplication::translate("FtpUpload", "\350\207\252\345\212\250\347\231\273\345\275\225", Q_NULLPTR));
        label_8->setText(QApplication::translate("FtpUpload", "\347\274\226\347\240\201:", Q_NULLPTR));
        label_2->setText(QApplication::translate("FtpUpload", "\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        radioButtonActive->setText(QApplication::translate("FtpUpload", "\344\270\273\345\212\250", Q_NULLPTR));
        radioButtonPassive->setText(QApplication::translate("FtpUpload", "\350\242\253\345\212\250", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("FtpUpload", "\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_Refush->setText(QApplication::translate("FtpUpload", "\345\210\267\346\226\260", Q_NULLPTR));
        downloadButton->setText(QApplication::translate("FtpUpload", "\344\270\213\350\275\275", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("FtpUpload", "\345\217\226\346\266\210", Q_NULLPTR));
        uploadButton_All->setText(QApplication::translate("FtpUpload", "\346\211\271\351\207\217\346\226\207\344\273\266\344\270\212\344\274\240", Q_NULLPTR));
        progressBar->setFormat(QApplication::translate("FtpUpload", "\345\275\223\345\211\215\344\270\212\344\274\240: %p%", Q_NULLPTR));
        pushButton_Back->setText(QApplication::translate("FtpUpload", "\350\277\224\345\233\236\344\270\212\344\270\200\347\272\247", Q_NULLPTR));
        timeEdit->setDisplayFormat(QApplication::translate("FtpUpload", "H:mm", Q_NULLPTR));
        pushButton_ComfirmT->setText(QApplication::translate("FtpUpload", "\347\241\256\350\256\244\345\256\232\346\227\266\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_CancelT->setText(QApplication::translate("FtpUpload", "\345\217\226\346\266\210\345\256\232\346\227\266\344\270\212\344\274\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FtpUpload: public Ui_FtpUpload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTPUPLOAD_H
