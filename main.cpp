﻿#include "ftpupload.h"
#include <QApplication>
#include <QFont>

#include <QTextCodec>  //添加头文件
int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    FtpUpload w;
    w.show();

    return a.exec();
}