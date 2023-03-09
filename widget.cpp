//#pragma execution_character_set("gbk")
//#pragma execution_character_set("UTF-8")
#include "widget.h"
#include "ui_widget.h"
#include <QSettings>
#include <QTextCodec>
#include <QByteArray>

struct DefaultPath Default;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("FTP上传");

    ui->progressBar->setVisible(false);

    m_ftp = new QFtp(this);

    //定时器
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);//非单次触发会造成定时器每10分钟一个间隔不断循环

    connect(m_timer, SIGNAL(timeout()), this, SLOT(GetTime()));

    ReadDefaultPath();

    connect(m_ftp,&QFtp::dataTransferProgress,this,[=](qint64 readBytes,
            qint64 totalBytes){
        auto percent = (qreal)readBytes/totalBytes;
        ui->progressBar->setValue(percent);
        if(percent == 1){
            if(m_loop.isRunning())
                m_loop.exit();
        }
    });

    connect(m_ftp, &QFtp::stateChanged,this,[=](int state){
        qDebug() << "ftp stateChanged state=" << state;
        if(state == QFtp::LoggedIn){
            ui->label_info->setText("登录成功");
        }
    });

    //文件列表
    connect(m_ftp,SIGNAL(listInfo(QUrlInfo)),SLOT(S_listInfo(QUrlInfo)));

    //进度条显示
    connect(m_ftp,SIGNAL(dataTransferProgress(qint64,qint64)),
            SLOT(S_upDateProgress(qint64,qint64)));

    //状态显示
    connect(m_ftp,SIGNAL(commandFinished(int,bool)),
            SLOT(S_commandFinish(int,bool)));


    connect(m_ftp, SIGNAL(listInfo(const QUrlInfo &)),this, SLOT(addToList(const QUrlInfo &)));

    connect(ui->treeWidget, SIGNAL(itemActivated(QTreeWidgetItem *, int)),
            this, SLOT(processItem(QTreeWidgetItem *, int)));

    ui->pushButton_ComfirmT->setEnabled(true);
    ui->pushButton_CancelT->setEnabled(false);
    ui->timeEdit->setEnabled(true);

    ui->lineEdit_Host->setText(Default.m_HostStr);
    ui->lineEdit_Port->setText(QString("%1").arg(Default.m_port));
    ui->lineEdit_User->setText(Default.UserStr);
    ui->lineEdit_pad->setText(Default.PasswordStr);

    ui->lineEdit_FilePath->setText(Default.m_SourcePath);
    ui->lineEdit_DirPath->setText(Default.m_SourcePath2);

    ui->timeEdit->setTime(QTime(Default.Hour, Default.Minute));
}

Widget::~Widget()
{
    delete m_ftp;
    delete ui;
}

//选择文件
void Widget::on_toolButton_File_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("打开文件。。。"),".","*");
    if(fileName.isNull()) return;

    if (!QFile::exists(fileName))
    {
        return;
    }

    ui->lineEdit_FilePath->setText(fileName);
}

//选择文件夹
void Widget::on_toolButton_Dir_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this);
    ui->lineEdit_DirPath->setText(path);
}

//上传文件
void Widget::on_pushButton_Upload_clicked()
{
    auto fileName = ui->lineEdit_FilePath->text();
    QFile *m_File = new QFile(fileName);
    if (QFile::exists(fileName))
    {
        ui->progressBar->setVisible(true);

        qDebug() << tr("文件%1的普通上传... ...").arg(fileName);

        QFileInfo fi(fileName);
        QString filename = fi.fileName();

        m_ftp->put(m_File,filename);                                     //上传
        return;
    }
}

//上传文件夹
void Widget::on_pushButton_Upload_2_clicked()
{
    auto path = ui->lineEdit_DirPath->text();
    QDir dir(path);
    if(dir.exists())
    {
        ui->progressBar->setVisible(true);
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it = fileLst.end();
        for(auto it =  fileLst.begin(); it != end_it; ++it)
        //for(const auto& it : fileLst)
        {

            QFile *file = new QFile(it->filePath(),this);
            if(!file->open(QIODevice::ReadOnly))
            {
                qDebug() << __FUNCTION__ <<"file open failed.";
                if(m_loop.isRunning())
                    m_loop.exit();
                continue;
            }
            ui->label_tips->setText("当前正在上传:" + it->fileName());
            m_ftp->put(file,it->fileName());
            m_loop.exec();
        }
        ui->label_tips->setText("已完成所有文件上传");
    }
}

//登录
void Widget::on_pushButton_Login_clicked()
{
    auto ip = ui->lineEdit_Host->text();
    auto port = ui->lineEdit_Port->text();
    auto userName = ui->lineEdit_User->text();
    auto psw = ui->lineEdit_pad->text();
    if(!ip.isEmpty() && !port.isEmpty() && !userName.isEmpty() && !psw.isEmpty())
    {
        m_ftp->connectToHost(ip,port.toInt());
    }
    else
    {
        ui->label_info->setText("参数不能为空");
    }
}

void Widget::S_commandFinish(int tmp, bool en)
{
    Q_UNUSED(tmp);

    if(m_ftp->currentCommand() == QFtp::ConnectToHost)
    {

        if(en)
        {
            ui->label_tips->setText(tr("连接服务器出现错误：%1").arg(m_ftp->errorString()));
            qDebug() << (tr("连接服务器出现错误：%1").arg(m_ftp->errorString()));
        }
        else
        {
            qDebug() << (tr("连接到服务器成功"));
            ui->label_tips->setText(tr("连接到服务器成功"));
            QString userName = ui->lineEdit_User->text();
            QString psw = ui->lineEdit_pad->text();
            m_ftp->login(userName,psw);//登陆服务器;
        }
    }

    if (m_ftp->currentCommand() == QFtp::Login)
    {
        if(en)
        {
            ui->label_tips->setText(tr("登录出现错误：%1").arg(m_ftp->errorString()));
            qDebug() << (tr("登录出现错误：%1").arg(m_ftp->errorString()));
        }
        else
        {
            ui->label_tips->setText(tr("登录服务器成功"));

            qDebug() << (tr("登录服务器成功"));
        }
    }

    if (m_ftp->currentCommand() == QFtp::Get)
    {
        if(en)
        {
            ui->label_tips->setText(tr("下载出现错误：%1").arg(m_ftp->errorString()));

            qDebug() << (tr("下载出现错误：%1").arg(m_ftp->errorString()));
        }
        else
        {
            ui->label_tips->setText(tr("已经完成下载"));
            qDebug() << (tr("已经完成下载")); 
        }
    }
    else if(m_ftp->currentCommand() == QFtp::Put)
    {
        if(en)
        {
            ui->label_tips->setText(tr("上传出现错误：%1").arg(m_ftp->errorString()));

            qDebug() << (tr("上传出现错误：%1").arg(m_ftp->errorString()));
        }
        else
        {
            ui->label_tips->setText(tr("已经完成文件上传"));     
            qDebug() << (tr("已经完成文件上传"));
        }
    }
    else if (m_ftp->currentCommand() == QFtp::Close)
    {

        qDebug() << (tr("已经关闭连接"));
        ui->label_tips->setText(tr("已经关闭连接"));
    }
    else if (m_ftp->currentCommand() == QFtp::Unconnected)
    {
        ui->label_tips->setText(tr("断开连接"));
    }
}

void Widget::S_list()
{
     m_ftp->list();
}

void Widget::S_listInfo(QUrlInfo _urInfo)
{
    qDebug() << _urInfo.name() <<" "<<_urInfo.size()<<" " <<_urInfo.owner();
}

void Widget::S_upDateProgress(qint64 _used, qint64 _total)
{
    int tmpVal = _used / (double)_total * 100;
    ui->progressBar->setValue(tmpVal);
}


void Widget::addToList(const QUrlInfo &urlInfo)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;

    item->setText(0, fromSpecialEncoding(urlInfo.name()));
    item->setText(1, QString::number(urlInfo.size()));
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));

    QPixmap pixmap(urlInfo.isDir() ? ":/new/prefix1/images/dir.png" : ":/new/prefix1/images/file.png");
    item->setIcon(0, pixmap);
    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui->treeWidget->addTopLevelItem(item);
    if (!ui->treeWidget->currentItem())
    {
        ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(0));
        ui->treeWidget->setEnabled(true);
    }
}

void Widget::processItem(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)//解决未使用的变量出现警告的问题
    QString name = item->text(0);
    QString str  = toSpecialEncoding(name);
    qDebug() << name << str << endl;
    if (isDirectory.value(str))
    {
        qDebug() << name << str << endl;
        ui->treeWidget->clear();
        isDirectory.clear();
        currentPath += "/" + name;
        m_ftp->cd(str);
        m_ftp->list();
        return;
    }
}

//刷新
void Widget::on_pushButton_FileList_clicked()
{
    ui->treeWidget->clear();
    this->S_list();
}

//返回
void Widget::on_pushButton_Back_clicked()
{
    ui->treeWidget->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty())
    {
        m_ftp->cd(toSpecialEncoding("/"));
    }
    else
    {
        m_ftp->cd(toSpecialEncoding(currentPath));
    }
    m_ftp->list();
}

void Widget::closeEvent(QCloseEvent *e)
{
    WriteDefaultPath();
    e->accept();
}

void Widget::ReadDefaultPath()
{
    QString path = "./device.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));
    qDebug("获取默认配置（上一次设置状态）");

    Default.m_HostStr =config->value(QString("Login/Host")).toString();
    Default.m_port =config->value(QString("Login/port")).toInt();
    Default.UserStr =config->value(QString("Login/UserName")).toString();
    Default.PasswordStr =config->value(QString("Login/PassWord")).toString();

    Default.Hour =config->value(QString("Time/Hour")).toInt();
    Default.Minute =config->value(QString("Time/Minute")).toInt();

    Default.m_SourcePath =config->value(QString("Path/SourcePath")).toString();
    Default.m_SourcePath2 =config->value(QString("Path/SourcePath2")).toString();

    delete config;
}

void Widget::WriteDefaultPath()
{
    Default.Hour = ui->timeEdit->time().hour();
    Default.Minute = ui->timeEdit->time().minute();

    QString path = "device.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));

    qDebug("保存更改后的默认路径");
    config->clear();
    Default.m_HostStr = ui->lineEdit_Host->text();
    Default.m_port = ui->lineEdit_Port->text().toInt();
    Default.UserStr = ui->lineEdit_User->text();
    Default.PasswordStr = ui->lineEdit_pad->text();
    Default.m_SourcePath = ui->lineEdit_FilePath->text();
    Default.m_SourcePath2 = ui->lineEdit_DirPath->text();


    config->beginGroup(QString("Login"));
    config->setValue("Host", Default.m_HostStr);
    config->setValue("port", Default.m_port);
    config->setValue("UserName", Default.UserStr);
    config->setValue("PassWord", Default.PasswordStr);
    config->endGroup();

    config->beginGroup(QString("Time"));
    config->setValue("Hour", Default.Hour);
    config->setValue("Minute", Default.Minute);
    config->endGroup();

    config->beginGroup(QString("Path"));
    config->setValue("SourcePath", Default.m_SourcePath);
    config->setValue("SourcePath2", Default.m_SourcePath2);
    config->endGroup();

    delete config;
}

void Widget::GetTime()
{
    QTime current_time = QTime::currentTime();
    int current_hour = current_time.hour();//当前的小时
    int current_minute = current_time.minute();//当前的分
    int current_second = current_time.second();//当前的秒

    int set_hour = ui->timeEdit->time().hour();
    int set_minute = ui->timeEdit->time().minute();
    qDebug() << "时" << current_hour << "分" << current_minute << "秒" << current_second;
    qDebug() << "设置时间" << set_hour << set_minute;

    if (current_hour == (set_hour - 1) && (60 - current_minute) <= 3)
    {
        m_timer->stop();
        qDebug("189执行定时发送");
        ScheduledUP();
    }
    else if ((current_hour == set_hour) && (set_minute - current_minute) > 0 && (set_minute - current_minute) <= 3)
    {
        m_timer->stop();
        qDebug("196执行定时发送");
        ScheduledUP();
    }
}

void Widget::ConfirmT()
{
    m_timer->start(180000); //启动定时器,3分钟
    ui->pushButton_ComfirmT->setEnabled(false);
    ui->pushButton_CancelT->setEnabled(true);
    ui->timeEdit->setEnabled(false);
}

void Widget::CancelT()
{
    m_timer->stop();
    ui->pushButton_ComfirmT->setEnabled(true);
    ui->pushButton_CancelT->setEnabled(false);
    ui->timeEdit->setEnabled(true);
}

//执行定时上传内容
void Widget::ScheduledUP()
{
    bool ret = ui->radioButton->isChecked();

    //如果选择文件夹
    if(ret == false)
    {
        on_pushButton_Upload_clicked();
    }
    else  //否则选择文件
    {
        on_pushButton_Upload_2_clicked();
    }
}

//确认定时上传
void Widget::on_pushButton_ComfirmT_clicked()
{
     ConfirmT();
}

//取消定时上传
void Widget::on_pushButton_CancelT_clicked()
{
    CancelT();
}


void Widget::myMessageOutput(const QString &msg)
{
    // 拼接输出信息
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString strMessage = QString("%1  DateTime:%2").arg(msg).arg(strDateTime);

    // 写入日志至文件中（读写、追加形式）
    QFile file("log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();
}

QString Widget::fromSpecialEncoding(const QString &inputStr)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    if (codec)
    {
        return codec->toUnicode(inputStr.toLatin1());
    }
    else
    {
        return QString("");
    }
}

QString Widget::toSpecialEncoding(const QString &inputStr)
{
    QTextCodec *codec= QTextCodec::codecForName("utf8");
    if (codec)
    {
        return QString::fromLatin1(codec->fromUnicode(inputStr));
    }
    else
    {
        return QString("");
    }
}
