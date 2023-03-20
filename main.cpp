#include <QApplication>
#include <QFont>
#include <QTextCodec>
#include <QDir>
#include <QSettings>
#include <QtWidgets>

#include "ftpupload.h"

//设置程序自启动 appPath程序路径
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
//#define AUTO_RUN "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
void setProcessAutoRunSelf(bool isstart)
{
    //注册表路径需要使用双反斜杠，如果是32位系统，要使用QSettings::Registry32Format;64位系统 QSettings::Registry64Format
     QSettings *settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);

    //以程序名称作为注册表中的键
    //根据键获取对应的值（程序路径）
    QString application_name = QApplication::applicationName();//获取应用名称
    QString path = settings->value(application_name).toString();

    //如果注册表中的路径和当前程序路径不一样，
    //则表示没有设置自启动或自启动程序已经更换了路径
    //toNativeSeparators的意思是将"/"替换为"\"
    if(isstart)
    {
        QString appPath = QApplication::applicationFilePath();//找到应用的目录
        QString newPath = QDir::toNativeSeparators(appPath);
        if (path != newPath)
        {
            settings->setValue(application_name, newPath);
        }
    }
    else settings->remove(application_name);
}

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)) // 分辨率适应
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);

    setProcessAutoRunSelf(true);

    FtpUpload w;
//    w.setWindowIcon(QIcon(":/img/img/FTP.png"));
    w.show();

    return a.exec();
}
