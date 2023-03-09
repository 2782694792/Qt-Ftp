#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QDialogButtonBox>
#include <QFile>
#include <QDir>
#include <QTreeWidgetItem>
#include <QProgressDialog>
#include <QMessageBox>
#include <QUrl>
#include <QFileDialog>
#include <QTextCodec>
#include <QDropEvent>
#include <QDirModel>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <QThread>
#include <QTcpSocket>
#include "qftp.h"

#pragma execution_character_set("UTF-8")

//extern struct DefaultPath Default;

struct DefaultPath //默认路径
{
    //登录
    QString m_HostStr;
    int m_port;
    QString UserStr;
    QString PasswordStr;

    QString m_SourcePath;
    QString m_SourcePath2;

    int ischecked;

    //定时时间
    int Hour;
    int Minute;
};



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_toolButton_File_clicked();

    void on_toolButton_Dir_clicked();

    void on_pushButton_Upload_clicked();

    void on_pushButton_Upload_2_clicked();

    void on_pushButton_Login_clicked();

    void S_commandFinish(int tmp, bool en);

    void S_list();

    void S_listInfo(QUrlInfo _urInfo);

    void S_upDateProgress(qint64 _used, qint64 _total);

    void addToList(const QUrlInfo &urlInfo);

    void processItem(QTreeWidgetItem *item, int column);


    void on_pushButton_FileList_clicked();

    void on_pushButton_Back_clicked();

    //覆写closeEvent函数
    void closeEvent(QCloseEvent *e);

    void ReadDefaultPath();

    void WriteDefaultPath();

    void GetTime();

    void ConfirmT();

    void CancelT();

    void ScheduledUP();

    void on_pushButton_ComfirmT_clicked();

    void on_pushButton_CancelT_clicked();

private:
    void clearListWidget();


    void myMessageOutput(const QString &msg);
    //转码
    QString fromSpecialEncoding(const QString &inputStr);
    QString toSpecialEncoding(const QString &inputStr);

private:
    Ui::Widget *ui;

    QFtp *m_ftp;
    QString m_curFile;
    QEventLoop m_loop;
    QStringList m_fileList;

    QHash<QString, bool> isDirectory;
    QString currentPath;

    QTimer * m_timer;

};


#endif // WIDGET_H
