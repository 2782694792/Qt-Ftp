#include "ftpupload.h"
#include <QApplication>
#include <QFont>
#include <QTextCodec>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)) // 分辨率适应
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    FtpUpload w;
//    w.setWindowIcon(QIcon(":/img/img/FTP.png"));
    w.show();

    return a.exec();
}
