#ifndef FTPUPLOAD_H
#define FTPUPLOAD_H

#include "qftp.h"
#include "ui_ftpupload.h"
#include <QButtonGroup>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>
#include <QMouseEvent>
#include <QMutex>
#include <QPoint>
#include <QTextCodec>
#include <QTimer>
#include <QTreeWidgetItem>
#include <QWidget>

extern struct DefaultPath Default;

struct DefaultPath // Ĭ��·��
{
    // ��¼
    QString m_HostStr;
    int     m_port;
    QString UserStr;
    QString PasswordStr;

    // �ļ�·��
    QString m_SourcePath;
    QString m_SourcePath2;
    QString m_SourcePath3;
    QString m_TargetPath;

    int isUploadChecked;
    int isLoginChecked;

    // ��ʱʱ��
    int Hour;
    int Minute;
    int Hour_Evening;
    int Minute_Evening;

    // ģʽ
    bool initiative; // ����ģʽ
    bool passive;    // ����ģʽ

    // �����ʽ
    int encoding;

    // �ϴ���Ϣ
    QString factory;      // ����
    QString procedure;    // ����
    QString manufacturer; // �豸����
    QString number;       // �豸���
    QString station;      // ��Ӧ��λ
};


class FtpUpload : public QWidget
{
    Q_OBJECT

  public:
    FtpUpload(QWidget* parent = 0);
    ~FtpUpload();

    void InitWidget();

  private:
    Ui::FtpUpload ui;

    QPoint dragPosition;

    QString     m_curFile;
    QEventLoop  m_loop;
    QStringList m_fileList;

    QHash<QString, bool> isDirectory;
    QString              currentPath;

    QFtp*   m_ftp;
    QTimer* m_timer;

    QHeaderView* header;

    QButtonGroup* group;

    QMenu*   popMenu;
    QAction* cdToParent;
    QAction* upload;
    QAction* download;
    QAction* reName;
    QAction* createFolder;
    QAction* removeFile;
    QAction* removeFolder;
    QAction* refresh;

  public:
    QString            strDirPath;
    QString            strDirPath2;
    struct DefaultPath Default;

  private slots:
    // ��дcloseEvent����
    void closeEvent(QCloseEvent* e);

    // ��¼
    void on_pushButton_Login_clicked();

    // �Զ���¼
    void on_checkBox_AutoLogin_clicked(bool checked);

    // ״̬
    void S_commandFinish(int tmp, bool en);

    void ftpCommandStarted(int tem);

    void ftpStateChanged(int state);

    // ����ļ���
    void addToList(const QUrlInfo& urlInfo);

    // ����
    void processItem(QTreeWidgetItem* item, int column);

    // ˢ��
    void on_pushButton_Refush_clicked();

    // ����
    void on_pushButton_Back_clicked();

    // �ϴ�
    void on_uploadButton_clicked();

    // �����ϴ�
    void on_uploadButton_All_clicked();

    // ѡ���ļ�·��
    void on_toolButton_file_clicked();

    // ѡ���ļ���·��
    void on_toolButton_dir_clicked();

    // ѡ���ļ���2·��
    void on_toolButton_dir_2_clicked();

    // ��������ʾ
    void S_upDateProgress(qint64 _used, qint64 _total);

    // ȷ����ʱ�ϴ�
    void on_pushButton_ComfirmT_clicked();

    // ȡ����ʱ�ϴ�
    void on_pushButton_CancelT_clicked();

    // ȡ������
    void on_cancelBtn_clicked();

    // �˳�
    void on_pushButton_Quit_clicked();

    // ��ȡʱ��
    void GetTime();

    // ��������ģʽ
    void on_radioButtonActive_clicked();

    // ���ñ���ģʽ
    void on_radioButtonPassive_clicked();

    // ��Ӳ˵�
    void on_treeWidget_customContextMenuRequested(const QPoint);

    // �ļ�������
    void fileRename();

    // �½��ļ���
    void createNewFolder();

    // ɾ���ļ�
    void deleteFile();

    // ˢ��
    void refreshed();

    // ɾ������Ŀ�ڵ�
    void deleleNode(QTreeWidgetItem* node);

    // ɾ���ļ���
    void deleteFolder();

    void on_downloadButton_clicked();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_timeEdit_evening_timeChanged(const QTime &time);

public:
    // ��ʱ�ϴ�
    void ConfirmT();

    void CancelT();


    // ��д�����ļ�
    void ReadDefaultPath();
    void WriteDefaultPath();

    // ת��
    QString fromSpecialEncoding(const QString& inputStr);
    QString toSpecialEncoding(const QString& inputStr);

    void Batch_upload(QString DirPath);

    void Batch_upload2(QString DirPath);

    void myMessageOutput(const QString& msg);

    void getFileName(QString DirPath);

    bool IsLogin;

    QMutex mutex;

    /**********************************************
     * @projectName   FtpUpload2
     * @brief         �ϴ��ļ���
     * @author        bin
     * @date          2023-03-01
     */
  public:
    void initComponent(bool enable);
    void UploadCustomDir(const QString& path, const QString& pathname);
    void UpFileList(const QString& path);
    void sleep(unsigned int msec); // ��ʱ����
    bool backUp();                 // ��һ�������أ� ��Ŀ¼Ϊ true
    void uploadStatusEvent(bool           ing,
                           const char*    prefixnotice,
                           const QString& content);
    bool qstrIsEffective(const QString& str);
    void mkdir_cd_update(const QString& dirname);
    void ScheduledUP(bool evening, int hour, int minute);
    void timeChanged(const QString& content, int id);


  protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

  private:
    QPoint mousePoint;
    bool   mouse_press;

    /**********************************************/
};

#endif // FTPUPLOAD_H
