#ifndef FTPUPLOAD_H
#define FTPUPLOAD_H

#include <QWidget>
#include "ui_ftpupload.h"
#include <QFile>
#include <QTreeWidgetItem>
#include <QTextCodec>
#include <QMouseEvent>
#include <QPoint>
#include <QButtonGroup>
#include <QMenu>
#include <QHeaderView>
#include <QEventLoop>
#include <QHash>
#include "qftp.h"
#include <QTimer>
#include <QFileInfo>
#include <QDir>
#include <QInputDialog>
#include <QMutex>

extern struct DefaultPath Default;

struct DefaultPath//默认路径
{
	//登录
	QString m_HostStr;
	int m_port; 
	QString UserStr;
	QString PasswordStr;

	//文件路径
	QString m_SourcePath;
	QString m_SourcePath2;
	QString m_SourcePath3;
	QString m_TargetPath;

	int isUploadChecked;
	int isLoginChecked;

	//定时时间
	int Hour;
	int Minute;

    // 模式
    bool initiative; // 主动模式
    bool passive; // 被动模式

    // 编码格式
    int encoding;

    // 上传信息

};


class FtpUpload : public QWidget
{
	Q_OBJECT

public:
	FtpUpload(QWidget *parent = 0);
	~FtpUpload();

	void InitWidget();
private:
	Ui::FtpUpload ui;

	QPoint dragPosition;

	QString m_curFile;
	QEventLoop m_loop;
	QStringList m_fileList;

	QHash<QString, bool> isDirectory;
	QString currentPath;

	QFtp *m_ftp;
	QTimer * m_timer;

	QHeaderView *header;

	QButtonGroup *group;

	QMenu *popMenu;
	QAction *cdToParent;
	QAction *upload;
	QAction *download;
	QAction *reName;
	QAction *createFolder;
	QAction *removeFile;
	QAction *removeFolder;
	QAction *refresh;

public:
	QString strDirPath;
	QString strDirPath2;
    //struct DefaultPath Default;

private slots:
	//覆写closeEvent函数
	void closeEvent(QCloseEvent *e);

	//登录
	 void on_pushButton_Login_clicked();

	 //自动登录
	 void on_checkBox_AutoLogin_clicked(bool checked);

	 //状态
	 void S_commandFinish(int tmp, bool en);

	 void ftpCommandStarted(int tem);

	 void ftpStateChanged(int state);

	 //添加文件项
	 void addToList(const QUrlInfo &urlInfo);

	 //返回
	 void processItem(QTreeWidgetItem *item, int column);

	 //刷新
	 void on_pushButton_Refush_clicked();

	 //返回
	 void on_pushButton_Back_clicked();

	 //上传
	 void on_uploadButton_clicked();

	 //批量上传
	 void on_uploadButton_All_clicked();

	 //选择文件路径
	 void on_toolButton_file_clicked();

	 //选择文件夹路径
	 void on_toolButton_dir_clicked();

	 //选择文件夹2路径
	 void on_toolButton_dir_2_clicked();

	 //进度条显示
	  void S_upDateProgress(qint64 _used, qint64 _total);

	  //确定定时上传
	  void on_pushButton_ComfirmT_clicked();

	  //取消定时上传
	  void on_pushButton_CancelT_clicked();

	  //取消下载
	  void on_cancelBtn_clicked();

	  //退出
	  void on_pushButton_Quit_clicked();

	  //获取时间
	  void GetTime();

	  //设置主动模式
	  void on_radioButtonActive_clicked();

	  //设置被动模式
	  void on_radioButtonPassive_clicked();

	  //添加菜单
	  void on_treeWidget_customContextMenuRequested(const QPoint);

	  //文件重命名
	  void fileRename();

	  //新建文件夹
	  void createNewFolder();

	  //删除文件
	  void deleteFile();

	  //刷新
	  void refreshed();

	  //删除子项目节点
	  void deleleNode(QTreeWidgetItem* node);

	  //删除文件夹
      void deleteFolder();

      void on_downloadButton_clicked();

public:
	//定时上传
	
	void ConfirmT();

	void CancelT();

	void ScheduledUP();


	//读写配置文件
	void ReadDefaultPath();
	void WriteDefaultPath();

	//转码
	QString fromSpecialEncoding(const QString &inputStr);
	QString toSpecialEncoding(const QString &inputStr);

	void Batch_upload(QString DirPath);

	void Batch_upload2(QString DirPath);

	void myMessageOutput(const QString &msg);

	void getFileName(QString DirPath);

	bool IsLogin;

	
	QMutex mutex;




    /**********************************************
     * @projectName   FtpUpload2
     * @brief         上传文件夹
     * @author        bin
     * @date          2023-03-01
     */
    void UploadCustomDir(QString path, QString pathname);
    void UpFileList(QString path);
    void sleep(unsigned int msec); // 延时功能
    void backUp();
    /**********************************************/


protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif // FTPUPLOAD_H
