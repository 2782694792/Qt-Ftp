#include "ftpupload.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QThread>

struct DefaultPath Default;


FtpUpload::FtpUpload(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);

    InitWidget();
}

FtpUpload::~FtpUpload()
{
    m_timer->stop();

    if (group != NULL)
        delete group;

    if (m_timer != NULL)
        delete m_timer;
}

void FtpUpload::InitWidget()
{
    // this->setWindowFlags(Qt::FramelessWindowHint);

    ui.progressBar->setValue(0);
    ui.progressBar->setVisible(false);

    m_ftp = new QFtp();
    m_ftp->setTransferMode(QFtp::Active);

    ReadDefaultPath();

    // 定时器
    m_timer = new QTimer(this);
    m_timer->setSingleShot(
        false); // 非单次触发会造成定时器每10分钟一个间隔不断循环

    // 添加组按钮
    group = new QButtonGroup(this);
    group->addButton(ui.radioButtonActive);
    group->addButton(ui.radioButtonPassive);
    group->setExclusive(true); // 设置为互斥
    ui.radioButtonActive->setChecked(true);

    // 设置背景颜色
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(76, 76, 76));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    ui.treeWidget->setStyleSheet(
        "QTreeView{color: white;background:transparent;border:1px solid;}"
        "QTreeView::item:selected {background: rgb(69, 187, 217);}"
        "QTreeView::item:selected:active{background: rgb(69, 187, 217);}");

    // 设置树列表宽度可调节，设置表头背景透明，标题文字为蓝色,字体大小为12
    header = ui.treeWidget->header();
    header->show();
    QFont font;
    font.setPointSize(12);
    header->setFont(font);
    header->setStyleSheet("QHeaderView::section {background-color: #383838;"
                          "color: rgb(69, 187, 217);border: none;}");

    // 信号与槽
    connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close())); // 关闭
    connect(ui.minButton, SIGNAL(clicked()), this,
            SLOT(showMinimized())); // 最小化

    // 进度条显示
    connect(m_ftp, SIGNAL(dataTransferProgress(qint64, qint64)),
            SLOT(S_upDateProgress(qint64, qint64)));

    // 状态显示
    connect(m_ftp, SIGNAL(commandFinished(int, bool)),
            SLOT(S_commandFinish(int, bool)));

    connect(m_ftp, SIGNAL(commandStarted(int)), this,
            SLOT(ftpCommandStarted(int)));

    // 添加文件项
    connect(m_ftp, SIGNAL(listInfo(const QUrlInfo&)), this,
            SLOT(addToList(const QUrlInfo&)));

    // 返回
    connect(ui.treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this,
            SLOT(processItem(QTreeWidgetItem*, int)));
    ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(on_treeWidget_customContextMenuRequested(QPoint)));

    connect(m_ftp, SIGNAL(stateChanged(int)), this, SLOT(ftpStateChanged(int)));

    ui.pushButton_ComfirmT->setEnabled(true);
    ui.pushButton_CancelT->setEnabled(false);
    ui.timeEdit->setEnabled(true);
    ui.lineEdit_Host->setText(Default.m_HostStr);
    ui.lineEdit_Port->setText(QString("%1").arg(Default.m_port));
    ui.lineEdit_User->setText(Default.UserStr);
    ui.lineEdit_pad->setText(Default.PasswordStr);
    ui.lineEdit_FilePath->setText(Default.m_SourcePath);
    ui.lineEdit_DirPath->setText(Default.m_SourcePath2);
    ui.lineEdit_DirPath_2->setText(Default.m_SourcePath3);
    ui.timeEdit->setTime(QTime(Default.Hour, Default.Minute));
    ui.radioButton->setChecked(Default.isUploadChecked);
    ui.checkBox_AutoLogin->setChecked(Default.isLoginChecked);
    currentPath = Default.m_TargetPath;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(GetTime()));

    IsLogin = false;

    on_checkBox_AutoLogin_clicked(Default.isLoginChecked);

    // fixme:
    {
        initComponent(false);

        ui.minButton->setVisible(false);
        ui.pushButton_Quit->setVisible(false);
        //    ui.statusLabel->setVisible(false);
        ui.setButton->setVisible(false);
        ui.closeButton->setVisible(false);
        ui.ipLabel_7->setVisible(true);
        ui.lineEdit_DirPath_2->setVisible(true);
        ui.toolButton_dir_2->setVisible(true);
        ui.radioButton->setVisible(false);
        ui.downloadButton->setVisible(true);

        ui.radioButtonPassive->setChecked(true);
        ui.radioButtonActive->setChecked(Default.initiative);
        ui.radioButtonPassive->setChecked(Default.passive);
        ui.widget->setBaseSize(500, 1000);
        ui.CB_EncodingFormat->addItem("GBK");
        ui.CB_EncodingFormat->addItem("UTF-8");
        ui.CB_EncodingFormat->setCurrentIndex(0);
        ui.downloadButton->setText(QString::fromLocal8Bit("文件夹上传"));
        ui.CB_EncodingFormat->setCurrentIndex(Default.encoding);
        ui.label_currentpath->setAlignment(Qt::AlignLeft);
        ui.label_currentpath->setAlignment(Qt::AlignVCenter);
    }

}

// 界面关闭重载
void FtpUpload::closeEvent(QCloseEvent* e)
{
    myMessageOutput(QString::fromLocal8Bit("界面关闭"));
    WriteDefaultPath();
    e->accept();
}

// 登录
void FtpUpload::on_pushButton_Login_clicked()
{
    QString str = ui.pushButton_Login->text();
    if (ui.pushButton_Login->text() == "注销") {
        m_ftp->close();
        ui.pushButton_Login->setText(QString::fromLocal8Bit("登录"));
        ui.treeWidget->clear();
        isDirectory.clear();
        initComponent(false);
    }
    else {
        myMessageOutput(QString::fromLocal8Bit("登录"));
        auto ip       = ui.lineEdit_Host->text();
        auto port     = ui.lineEdit_Port->text();
        auto userName = ui.lineEdit_User->text();
        auto psw      = ui.lineEdit_pad->text();
        myMessageOutput(ip);
        myMessageOutput(port);
        myMessageOutput(userName);
        myMessageOutput(psw);
        ui.treeWidget->clear();
        if (!ip.isEmpty() && !port.isEmpty() && !userName.isEmpty() &&
            !psw.isEmpty()) {
            m_ftp->connectToHost(ip, port.toInt());
            m_ftp->login(userName, psw); // 登陆服务器;
            initComponent(true);
        }
        else {
            ui.statusLabel->setText(QString::fromLocal8Bit("参数不能为空"));
        }
    }
}

// 自动登录
void FtpUpload::on_checkBox_AutoLogin_clicked(bool checked)
{
//    bool ret = ui.radioButton->isChecked();
    if (checked == true) {
        myMessageOutput(QString::fromLocal8Bit("自动登录"));
        on_pushButton_Login_clicked();
        ui.pushButton_ComfirmT->setEnabled(false);
        ui.pushButton_CancelT->setEnabled(true);
        ui.timeEdit->setEnabled(false);
        ConfirmT();
    }
}

// 状态显示
void FtpUpload::S_commandFinish(int tmp, bool en)
{
    Q_UNUSED(tmp);

    if (m_ftp->currentCommand() == QFtp::ConnectToHost) {
        if (en) {
            myMessageOutput(QString::fromLocal8Bit("连接服务器出现错误"));
            ui.textEdit->append(QString::fromLocal8Bit("连接服务器出现错误：%1")
                                    .arg(m_ftp->errorString()));
        }
        else {
            myMessageOutput("连接到服务器成功");
            ui.textEdit->append(QString::fromLocal8Bit("连接到服务器成功"));
        }
    }

    if (m_ftp->currentCommand() == QFtp::Login) {
        if (en) {
            myMessageOutput(QString::fromLocal8Bit("登录出现错误"));
            ui.textEdit->append(QString::fromLocal8Bit("登录出现错误：%1")
                                    .arg(m_ftp->errorString()));
        }
        else {
            myMessageOutput(QString::fromLocal8Bit("登录成功"));
            ui.statusLabel->setText(QString::fromLocal8Bit("登录成功"));
            ui.textEdit->append(QString::fromLocal8Bit("登录服务器成功"));
            ui.pushButton_Login->setText(QString::fromLocal8Bit("注销"));

            if (strDirPath != "") {
                ui.lineEdit_DirPath->setText(strDirPath);
            }

            if (strDirPath2 != "") {
                ui.lineEdit_DirPath_2->setText(strDirPath2);
            }

            currentPath = Default.m_TargetPath;
            if (currentPath != "")
                m_ftp->cd(toSpecialEncoding(currentPath));
            ui.treeWidget->clear();
            m_ftp->list();
        }
    }

    if (m_ftp->currentCommand() == QFtp::Cd || m_ftp->currentCommand() == QFtp::List){
        ui.label_currentpath->setText(QString::fromLocal8Bit("当前路径：\\") + currentPath);
    }

    if (m_ftp->currentCommand() == QFtp::Get) {
        if (en) {
            ui.textEdit->append(QString::fromLocal8Bit("下载出现错误：%1")
                                    .arg(m_ftp->errorString()));

            qDebug() << (QString::fromLocal8Bit("下载出现错误：%1")
                             .arg(m_ftp->errorString()));
        }
        else {
            ui.textEdit->append(QString::fromLocal8Bit("已经完成下载"));
            qDebug() << (QString::fromLocal8Bit("已经完成下载"));
        }
        refreshed();
    }
    else if (m_ftp->currentCommand() == QFtp::Put) {
        if (en) {
            myMessageOutput(QString::fromLocal8Bit("上传出现错误：%1")
                                .arg(m_ftp->errorString()));
            ui.textEdit->append(QString::fromLocal8Bit("上传出现错误：%1")
                                    .arg(m_ftp->errorString()));
        }
        else {
            // if(m_loop.isRunning())
            //             m_loop.exit();
            myMessageOutput(QString::fromLocal8Bit("已经完成文件上传"));
        }
    }
    else if (m_ftp->currentCommand() == QFtp::Close) {
        myMessageOutput(QString::fromLocal8Bit("已经关闭连接"));
        ui.textEdit->append(QString::fromLocal8Bit("已经关闭连接"));
    }
    else if (m_ftp->currentCommand() == QFtp::Unconnected) {
        myMessageOutput(QString::fromLocal8Bit("断开连接"));
        ui.textEdit->append(QString::fromLocal8Bit("断开连接"));
    }
    else if (m_ftp->currentCommand() == QFtp::Rename) {
        myMessageOutput(QString::fromLocal8Bit("文件重命名成功"));
        ui.textEdit->append(QString::fromLocal8Bit("文件重命名成功"));
        refreshed();
    }
    else if (m_ftp->currentCommand() == QFtp::Mkdir) {
        myMessageOutput(QString::fromLocal8Bit("新建文件夹成功"));
        ui.textEdit->append(QString::fromLocal8Bit("新建文件夹成功"));
        refreshed();
    }
    else if (m_ftp->currentCommand() == QFtp::Remove) {
        myMessageOutput(QString::fromLocal8Bit("文件删除成功"));
        ui.textEdit->append(QString::fromLocal8Bit("文件删除成功"));
    }
    else if (m_ftp->currentCommand() == QFtp::Rmdir) {
        myMessageOutput(QString::fromLocal8Bit("文件夹删除成功"));
        ui.textEdit->append(QString::fromLocal8Bit("文件夹删除成功"));
    }
}

void FtpUpload::ftpCommandStarted(int tem)
{
    if (m_ftp->currentCommand() == QFtp::ConnectToHost) {
        myMessageOutput(QString::fromLocal8Bit("正在连接到服务器..."));
//        ui.statusLabel->setText(QString::fromLocal8Bit("正在连接到服务器…"));
    }
    if (m_ftp->currentCommand() == QFtp::Login) {
        myMessageOutput(QString::fromLocal8Bit("正在登录..."));
//        ui.statusLabel->setText(QString::fromLocal8Bit("正在登录…"));
    }
    if (m_ftp->currentCommand() == QFtp::Get) {
        myMessageOutput(QString::fromLocal8Bit("正在下载..."));
//        ui.statusLabel->setText(QString::fromLocal8Bit("正在下载…"));
    }
    if (m_ftp->currentCommand() == QFtp::Put) {
        myMessageOutput(QString::fromLocal8Bit("正在上传..."));
//        ui.statusLabel->setText(QString::fromLocal8Bit("正在上传…"));
    }
    else if (m_ftp->currentCommand() == QFtp::Close) {
        myMessageOutput(QString::fromLocal8Bit("正在关闭连接..."));
//        ui.statusLabel->setText(QString::fromLocal8Bit("正在关闭连接…"));
    }
}

void FtpUpload::ftpStateChanged(int state)
{
    if (state == QFtp::Unconnected) {
        IsLogin = false;
        myMessageOutput(QString::fromLocal8Bit("未连接到主机"));
        ui.textEdit->append(QString::fromLocal8Bit("未连接到主机"));
        ui.pushButton_Login->setText(QString::fromLocal8Bit("登录"));
        ui.treeWidget->clear();
        // 登录
        // on_pushButton_Login_clicked();
    }
    if (state == QFtp::Connected) {
        myMessageOutput(QString::fromLocal8Bit("已经连接到主机"));
        ui.textEdit->append(QString::fromLocal8Bit("已经连接到主机"));
    }
    if (state == QFtp::HostLookup) {
        myMessageOutput(QString::fromLocal8Bit("正在查找主机"));
        ui.textEdit->append(QString::fromLocal8Bit("正在查找主机"));
    }
    if (state == QFtp::LoggedIn) {
        myMessageOutput(QString::fromLocal8Bit("已经登录"));
        ui.textEdit->append(QString::fromLocal8Bit("已经登录"));
        IsLogin = true;
    }
    if (state == QFtp::Closing) {
        myMessageOutput(QString::fromLocal8Bit("连接正在关闭"));
        ui.textEdit->append(QString::fromLocal8Bit("连接正在关闭"));
    }
}

// 刷新槽函数
void FtpUpload::addToList(const QUrlInfo& urlInfo)
{
    QString
        fileSize; // 用于存储文件大小，根据文件大小字节，设置文件在树列表的单位
    if (urlInfo.size() >= 0 && urlInfo.size() < 1024) {
        fileSize = QString::number(urlInfo.size()) + "Byte";
    }
    else if (urlInfo.size() >= 1024 && urlInfo.size() < 1024 * 1024) {
        fileSize = QString::number(urlInfo.size() / 1024.0, 'f', 2) + "KB";
    }
    else if (urlInfo.size() >= 1024 * 1024 &&
             urlInfo.size() < 1024 * 1024 * 1024) {
        fileSize =
            QString::number(urlInfo.size() / 1024 / 1024.0, 'f', 2) + "MB";
    }
    else if (urlInfo.size() >= 1024 * 1024 * 1024) {
        fileSize =
            QString::number(urlInfo.size() / 1024 / 1024 / 1024.0, 'f', 2) +
            "GB";
    }

    QTreeWidgetItem* item = new QTreeWidgetItem;

    item->setText(0, fromSpecialEncoding(urlInfo.name()));
    item->setText(1, fileSize);
    item->setText(2, urlInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
    item->setText(3, urlInfo.owner());
    item->setText(4, urlInfo.group());


    QPixmap pixmap(urlInfo.isDir() ? ":/img/img/dir.png" :
                                     ":/img/img/file.png");
    item->setIcon(0, pixmap);
    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui.treeWidget->addTopLevelItem(item);
    if (!ui.treeWidget->currentItem()) {
        ui.treeWidget->setCurrentItem(ui.treeWidget->topLevelItem(0));
        ui.treeWidget->setEnabled(true);
    }
}

// 双击进入
void FtpUpload::processItem(QTreeWidgetItem* item, int column)
{
    myMessageOutput(QString::fromLocal8Bit("双击进入"));
    Q_UNUSED(column) // 解决未使用的变量出现警告的问题
    QString name = item->text(0);
    QString str  = toSpecialEncoding(name);
    qDebug() << name << str << endl;
    if (isDirectory.value(str)) {
        qDebug() << name << str << endl;
        ui.treeWidget->clear();
        isDirectory.clear();
        currentPath += "/" + name;
        m_ftp->cd(str);
        m_ftp->list();
        return;
    }
}

// 刷新
void FtpUpload::on_pushButton_Refush_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("刷新"));
    ui.treeWidget->clear();
    m_ftp->list();
}

// 返回
void FtpUpload::on_pushButton_Back_clicked()
{
    ui.treeWidget->clear();
    isDirectory.clear();
    QString strLeft = currentPath.left(currentPath.lastIndexOf('/'));
    currentPath     = strLeft;
    if (currentPath.isEmpty()) {
        m_ftp->cd(toSpecialEncoding("/"));
    }
    else {
        m_ftp->cd(toSpecialEncoding(currentPath));
    }
    m_ftp->list();
}

// 上传文件
void FtpUpload::on_uploadButton_clicked()
{
    if (IsLogin == false)
        on_pushButton_Login_clicked();

    myMessageOutput(QString::fromLocal8Bit("上传文件"));
    auto   fileName = ui.lineEdit_FilePath->text();
    QFile* m_File   = new QFile(fileName);
    if (QFile::exists(fileName)) {
        ui.progressBar->setVisible(true);

        qDebug()
            << QString::fromLocal8Bit("文件%1的普通上传... ...").arg(fileName);

        // fixme: try...catch...finally
        if (!m_File->isOpen()) {
            QFileInfo fi(fileName);
            QString   filename = fi.fileName();

            uploadStatusEvent(true, "文件 : ", filename);

            m_ftp->put(m_File, toSpecialEncoding(filename)); // 上传
            refreshed();

            uploadStatusEvent(false, "文件 : ", filename);
        }
        else {
            ui.textEdit->append(QString::fromLocal8Bit("文件被占用"));
            QMessageBox::warning(NULL, QString::fromLocal8Bit("文件被占用"),
                                 QString::fromLocal8Bit("文件被占用"));
        }

        m_File->close();
        m_File = NULL;
    }
    WriteDefaultPath();
    return;
}

// 批量上传
void FtpUpload::on_uploadButton_All_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("批量上传"));
    if (strDirPath != "") {
        ui.lineEdit_DirPath->setText(strDirPath);
    }
    if (strDirPath2 != "") {
        ui.lineEdit_DirPath_2->setText(strDirPath2);
    }

    auto path  = ui.lineEdit_DirPath->text();
    auto path2 = ui.lineEdit_DirPath_2->text();
    // getFileName(path);
    // getFileName(path2);
    Batch_upload(path);
    //	Batch_upload2(path2);

    //	WriteDefaultPath();
}

// 选择文件路径
void FtpUpload::on_toolButton_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, QString::fromLocal8Bit("打开文件..."), ".", "*");
    if (fileName.isNull())
        return;

    if (!QFile::exists(fileName)) {
        return;
    }

    ui.lineEdit_FilePath->setText(fileName);
}

// 选择文件夹路径
void FtpUpload::on_toolButton_dir_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this);
    ui.lineEdit_DirPath->setText(path);
}

// 选择文件夹2路径
void FtpUpload::on_toolButton_dir_2_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this);
    ui.lineEdit_DirPath_2->setText(path);
}

void FtpUpload::S_upDateProgress(qint64 _used, qint64 _total)
{
    auto percent = (qreal)_used / _total * 100;
    ui.progressBar->setValue(percent);
}

// 确定定时上传
void FtpUpload::on_pushButton_ComfirmT_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("确定定时上传"));
    ConfirmT();
}

// 取消定时上传
void FtpUpload::on_pushButton_CancelT_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("取消定时上传"));
    CancelT();
}

// 取消下载
void FtpUpload::on_cancelBtn_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("取消下载"));
    m_ftp->abort();
    ui.progressBar->setValue(0);
}

// 退出
void FtpUpload::on_pushButton_Quit_clicked() {}

void FtpUpload::GetTime()
{
    QTime current_time   = QTime::currentTime();
    int   current_hour   = current_time.hour();   // 当前的小时
    int   current_minute = current_time.minute(); // 当前的分
    int   current_second = current_time.second(); // 当前的秒

    int set_hour   = ui.timeEdit->time().hour();
    int set_minute = ui.timeEdit->time().minute();
    qDebug() << "时" << current_hour << "分" << current_minute << "秒"
             << current_second;
    qDebug() << "设置时间" << set_hour << set_minute;

    if (current_hour == (set_hour + 1) && (60 - current_minute) == 3) {
        if (IsLogin == false)
            on_pushButton_Login_clicked();
    }
    else if ((current_hour == set_hour) && (set_minute - current_minute) > 0 &&
             (set_minute - current_minute) == 3) {
        if (IsLogin == false)
            on_pushButton_Login_clicked();
    }

    if (current_hour == (set_hour + 1) && (60 - current_minute) == 2) {
        myMessageOutput(QString::fromLocal8Bit("停止计数1"));
        m_timer->stop();
        myMessageOutput(QString::fromLocal8Bit("执行定时发送1"));
        myMessageOutput(QString::fromLocal8Bit("当前时间：%1:%2:%3")
                            .arg(current_hour)
                            .arg(current_minute)
                            .arg(current_second));
        ScheduledUP();
        m_timer->start(60000);
        myMessageOutput(QString::fromLocal8Bit("开始计数"));
    }
    else if ((current_hour == set_hour) && (set_minute - current_minute) > 0 &&
             (set_minute - current_minute) == 2) {
        myMessageOutput(QString::fromLocal8Bit("停止计数2"));
        m_timer->stop();
        myMessageOutput(QString::fromLocal8Bit("执行定时发送2"));
        myMessageOutput(QString::fromLocal8Bit("当前时间：%1:%2:%3")
                            .arg(current_hour)
                            .arg(current_minute)
                            .arg(current_second));
        ScheduledUP();
        m_timer->start(60000);
        myMessageOutput(QString::fromLocal8Bit("开始计数"));
    }
}

void FtpUpload::on_radioButtonActive_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("主动传输"));
    m_ftp->setTransferMode(QFtp::Active);
}

void FtpUpload::on_radioButtonPassive_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("被动传输"));
    m_ftp->setTransferMode(QFtp::Passive);
}

// 添加菜单
void FtpUpload::on_treeWidget_customContextMenuRequested(const QPoint)
{
    static int status = 1;
    if (status == 1) {
        popMenu = new QMenu(this); // 定义一个右键弹出菜单
        cdToParent = popMenu->addAction(QString::fromLocal8Bit("返回上一级"));
        upload   = popMenu->addAction(QString::fromLocal8Bit("上传"));
        download = popMenu->addAction(QString::fromLocal8Bit("下载"));
        popMenu->addSeparator(); // 插入一个分割线
        reName = popMenu->addAction(QString::fromLocal8Bit("重命名"));
        createFolder = popMenu->addAction(QString::fromLocal8Bit("新建文件夹"));
        popMenu->addSeparator();
        removeFile = popMenu->addAction(QString::fromLocal8Bit("删除文件"));
        removeFolder = popMenu->addAction(QString::fromLocal8Bit("删除文件夹"));
        popMenu->addSeparator();
        refresh = popMenu->addAction(QString::fromLocal8Bit("刷新"));
        if (ui.treeWidget->topLevelItemCount() == 0) // 根节点为空
        {
            upload->setEnabled(false);
            download->setEnabled(false);
            reName->setEnabled(false);
            createFolder->setEnabled(false);
            removeFile->setEnabled(false);
            removeFolder->setEnabled(false);
            refresh->setEnabled(false);
        }
        connect(cdToParent, SIGNAL(triggered()), this,
                SLOT(on_pushButton_Back_clicked()));
        connect(upload, SIGNAL(triggered()), this,
                SLOT(on_uploadButton_clicked()));
        connect(reName, SIGNAL(triggered()), this, SLOT(fileRename()));
        connect(createFolder, SIGNAL(triggered()), this,
                SLOT(createNewFolder()));
        connect(removeFile, SIGNAL(triggered()), this, SLOT(deleteFile()));
        connect(removeFolder, SIGNAL(triggered()), this, SLOT(deleteFolder()));
        connect(refresh, SIGNAL(triggered()), this, SLOT(refreshed()));


        // 设置菜单风格
        popMenu->setStyleSheet(
            "QMenu{background-color: white;}"
            "QMenu::item {background-color: transparent;"
            "padding:6px 30px;}"
            "QMenu::item:selected {background-color: #2dabf9;}");
        popMenu->exec(QCursor::pos()); // 弹出右键菜单，菜单位置为光标位置
        popMenu->clear();
        delete popMenu;
        popMenu = nullptr;
    }
    else {
    }
    status *= -1;
}

// 文件重命名
void FtpUpload::fileRename()
{
    QString oldName = ui.treeWidget->currentItem()->text(0);
    QString str     = toSpecialEncoding(oldName);
    if (isDirectory.value(str)) // 选中的是文件夹，则返回
    {
        QMessageBox::information(
            this, QString::fromLocal8Bit("保存"),
            QString::fromLocal8Bit(
                "<font size='6' color='#008ed5'>文件夹不能重命名！</font>"),
            QMessageBox::Ok);
        return;
    }
    bool    ok;
    QString newName = QInputDialog::getText(
        this, QString::fromLocal8Bit("重命名"),
        QString::fromLocal8Bit("新文件名："), QLineEdit::Normal,
        QString::fromLocal8Bit(""), &ok, Qt::WindowCloseButtonHint);
    if (newName.isEmpty())
        return;
    m_ftp->rename(toSpecialEncoding(oldName), toSpecialEncoding(newName));
}

// 新建文件夹
void FtpUpload::createNewFolder()
{
    bool    ok;
    QString folderName = QInputDialog::getText(
        this, QString::fromLocal8Bit("新建文件夹"),
        QString::fromLocal8Bit("新文件夹名："), QLineEdit::Normal,
        QString::fromLocal8Bit(""), &ok, Qt::WindowCloseButtonHint);
    if (folderName.isEmpty())
        return;
    m_ftp->mkdir(toSpecialEncoding(folderName));

    ui.treeWidget->clear();
    m_ftp->list();
}

// 删除文件
void FtpUpload::deleteFile()
{
    QString deleteFile = ui.treeWidget->currentItem()->text(0);
    QString str        = toSpecialEncoding(deleteFile);
    if (isDirectory.value(str)) // 选中的是文件夹，则返回
    {
        return;
    }
    QTreeWidgetItem* item = ui.treeWidget->currentItem();
    if (item->childCount() > 0) // 如果有子节点，则删除
    {
        for (int i = 0; i < item->childCount(); i++) {
            deleleNode(item->child(i));
        }
    }
    delete item;
    if (ui.treeWidget->topLevelItemCount() <= 0) {
        // ui.pushButton_Back->setEnabled(true);
    }
    m_ftp->remove(toSpecialEncoding(deleteFile));
}

// 刷新
void FtpUpload::refreshed()
{
    m_ftp->cd(currentPath);
    ui.treeWidget->clear();
    m_ftp->list();
}

// 删除子项目节点
void FtpUpload::deleleNode(QTreeWidgetItem* node)
{
    if (node->childCount() > 0) {
        for (int i = 0; i < node->childCount(); i++) {
            deleleNode(node->child(i));
        }
    }
    else {
        delete node;
    }
}

// 删除文件夹
void FtpUpload::deleteFolder()
{
    QString folder = ui.treeWidget->currentItem()->text(0);
    QString str    = toSpecialEncoding(folder);
    if (isDirectory.value(str)) {
        m_ftp->rmdir(toSpecialEncoding(folder));

        QTreeWidgetItem* item = ui.treeWidget->currentItem();
        if (item->childCount() > 0) // 如果有子节点，则删除
        {
            for (int i = 0; i < item->childCount(); i++) {
                deleleNode(item->child(i));
            }
        }
        delete item;
        item = NULL;
    }
}

void FtpUpload::ConfirmT()
{
    m_timer->start(60000); // 启动定时器,1分钟
    ui.pushButton_ComfirmT->setEnabled(false);
    ui.pushButton_CancelT->setEnabled(true);
    ui.timeEdit->setEnabled(false);
}

void FtpUpload::CancelT()
{
    m_timer->stop();
    ui.pushButton_ComfirmT->setEnabled(true);
    ui.pushButton_CancelT->setEnabled(false);
    ui.timeEdit->setEnabled(true);
    ui.uploadButton->setEnabled(true);
    ui.uploadButton_All->setEnabled(true);
}

void FtpUpload::ScheduledUP()
{
    bool ret = ui.radioButton->isChecked();

    if (ret == true) {
        //    	on_uploadButton_clicked();
        on_uploadButton_All_clicked();
    }
    else {
        const QString temp  = ui.lineEdit_DirPath->text();
        QDate         today = QDate::currentDate().addDays(-1);
        int           month = today.month();
        int           day   = today.day();

        QString morningname = QString::fromLocal8Bit("%1月%2日白班")
                                  .arg(QString::number(month))
                                  .arg(QString::number(day));
        QString morning =
            QString::fromLocal8Bit("%1/%2").arg(temp).arg(morningname);

        UploadCustomDir(morning, morningname);

        QString eveningname = QString::fromLocal8Bit("%1月%2日夜班")
                                  .arg(QString::number(month))
                                  .arg(QString::number(day));
        QString evening =
            QString::fromLocal8Bit("%1/%2").arg(temp).arg(eveningname);

        UploadCustomDir(evening, eveningname);
    }
}

// 读取配置文件
void FtpUpload::ReadDefaultPath()
{
    QString    path   = "./device.ini";
    QSettings* config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));
    myMessageOutput(QString::fromLocal8Bit("获取默认配置（上一次设置状态）"));
    QString retStr1   = config->value(QString("Login/Host")).toString();
    Default.m_HostStr = retStr1;

    Default.m_port = config->value(QString("Login/port")).toInt();

    QString retStr2 = config->value(QString("Login/UserName")).toString();
    Default.UserStr = retStr2;

    QString retStr3     = config->value(QString("Login/PassWord")).toString();
    Default.PasswordStr = retStr3;

    Default.Hour   = config->value(QString("Time/Hour")).toInt();
    Default.Minute = config->value(QString("Time/Minute")).toInt();

    QString retStr4      = config->value(QString("Path/SourcePath")).toString();
    Default.m_SourcePath = retStr4;
    QString retStr5 = config->value(QString("Path/SourcePath2")).toString();
    Default.m_SourcePath2 = retStr5;
    QString retStr6 = config->value(QString("Path/SourcePath3")).toString();
    Default.m_SourcePath3 = retStr6;
    QString retStr7      = config->value(QString("Path/TargetPath")).toString();
    Default.m_TargetPath = retStr7;


    Default.isUploadChecked =
        config->value(QString("Checked/UploadChecked")).toInt();
    Default.isLoginChecked =
        config->value(QString("Checked/LoginChecked")).toInt();
    Default.initiative =
        config->value(QString("Checked/ModeCheckedInitiative")).toBool();
    Default.passive =
        config->value(QString("Checked/ModeCheckedPassive")).toBool();
    Default.encoding = config->value(QString("Checked/Encoding")).toInt();

    delete config;
}

// 写入配置文件
void FtpUpload::WriteDefaultPath()
{
    Default.Hour   = ui.timeEdit->time().hour();
    Default.Minute = ui.timeEdit->time().minute();

    QString    path   = "device.ini";
    QSettings* config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));

    myMessageOutput(QString::fromLocal8Bit("保存更改后的默认路径"));
    config->clear();
    QString retStr1         = ui.lineEdit_Host->text();
    Default.m_HostStr       = retStr1;
    Default.m_port          = ui.lineEdit_Port->text().toInt();
    QString retStr2         = ui.lineEdit_User->text();
    Default.UserStr         = retStr2;
    QString retStr3         = ui.lineEdit_pad->text();
    Default.PasswordStr     = retStr3;
    QString retStr4         = ui.lineEdit_FilePath->text();
    Default.m_SourcePath    = retStr4;
    QString retStr5         = ui.lineEdit_DirPath->text();
    Default.m_SourcePath2   = retStr5;
    QString retStr6         = ui.lineEdit_DirPath_2->text();
    Default.m_SourcePath3   = retStr6;
    QString retStr7         = currentPath;
    Default.m_TargetPath    = retStr7;
    Default.isUploadChecked = ui.radioButton->isChecked();
    Default.isLoginChecked  = ui.checkBox_AutoLogin->isChecked();


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
    config->setValue("SourcePath3", Default.m_SourcePath3);
    config->setValue("TargetPath", Default.m_TargetPath);
    config->endGroup();

    config->beginGroup(QString("Checked"));
    config->setValue("UploadChecked", Default.isUploadChecked);
    config->setValue("LoginChecked", Default.isLoginChecked);
    config->setValue("ModeCheckedInitiative", Default.initiative);
    config->setValue("ModeCheckedPassive", Default.passive);
    config->setValue("Encoding", Default.encoding);
    config->endGroup();

    delete config;
}

QString FtpUpload::fromSpecialEncoding(const QString& inputStr)
{
    if (ui.CB_EncodingFormat->currentIndex() == 0) {
        QTextCodec* codec = QTextCodec::codecForName("gbk");
        return codec->toUnicode(inputStr.toLatin1());
    }
    else {
        QTextCodec* codec = QTextCodec::codecForName("utf8");
        return codec->toUnicode(inputStr.toLatin1());
    }
}

QString FtpUpload::toSpecialEncoding(const QString& inputStr)
{
    if (ui.CB_EncodingFormat->currentIndex() == 0) {
        QTextCodec* codec = QTextCodec::codecForName("gbk");
        return QString::fromLatin1(codec->fromUnicode(inputStr));
    }
    else {
        QTextCodec* codec = QTextCodec::codecForName("utf8");
        return QString::fromLatin1(codec->fromUnicode(inputStr));
    }
}

// 批量上传
void FtpUpload::Batch_upload(QString DirPath)
{

    mutex.lock();

    if (DirPath == "") {
        mutex.unlock();
        return;
    }
    myMessageOutput(DirPath);
    QDir dir(DirPath);
    if (dir.exists()) {
        ui.progressBar->setVisible(true);
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it  = fileLst.end();
        for (auto it = fileLst.begin(); it != end_it; it++) {
            QFile* file = new QFile(it->filePath(), this);
            if (!file->open(QIODevice::ReadOnly)) {
                myMessageOutput("file open failed.");
                //				if(m_loop.isRunning())
                //					m_loop.exit();
                continue;
            }
            ui.textEdit->append(QString::fromLocal8Bit("当前正在上传:") +
                                it->fileName());

            uploadStatusEvent(true, "批量文件 : ", it->fileName() );

            m_ftp->put(file, toSpecialEncoding(it->fileName()));
//            sleep(250);
            myMessageOutput(QString::fromLocal8Bit("当前正在上传:") +
                            it->filePath());
            //			m_loop.exec();

            uploadStatusEvent(false, "批量文件 : ", it->fileName());
        }
        ui.progressBar->setValue(0);
        myMessageOutput(QString::fromLocal8Bit("已完成所有文件上传"));
        ui.textEdit->append(QString::fromLocal8Bit("已完成所有文件上传"));
    }

    ui.treeWidget->clear();
    m_ftp->list();

    mutex.unlock();

}

void FtpUpload::Batch_upload2(QString DirPath)
{
    mutex.lock();

    if (DirPath == "") {
        mutex.unlock();
        return;
    }
    myMessageOutput(DirPath);
    QDir dir(DirPath);
    if (dir.exists()) {
        ui.progressBar->setVisible(true);
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it  = fileLst.end();
        for (auto it = fileLst.begin(); it != end_it; it++) {
            QFile*    file = new QFile(it->filePath(), this);
            QFileInfo fileinfo(it->filePath());
            QDateTime create = fileinfo.created();
            QString   _createTime =
                create.toString("yyyy-MM-dd"); // 获取文件创建时间
            QDateTime currentTime = QDateTime::currentDateTime();
            QString   currentTimeStr =
                currentTime.toString("yyyy-MM-dd"); // 获取当前时间
            QString beforeDayTimeStr = currentTime.addDays(-1).toString(
                "yyyy-MM-dd"); // 获取前一天时间

            if (_createTime == currentTimeStr ||
                _createTime == beforeDayTimeStr) {
                if (!file->open(QIODevice::ReadOnly)) {
                    myMessageOutput(
                        QString::fromLocal8Bit("file open failed."));
                    if (m_loop.isRunning())
                        m_loop.exit();
                    continue;
                }

                ui.textEdit->append(QString::fromLocal8Bit("当前正在上传:") +
                                    it->fileName());
                m_ftp->put(file, toSpecialEncoding(it->fileName()));
                sleep(250);
                myMessageOutput(QString::fromLocal8Bit("当前正在上传:") +
                                it->filePath());
                m_loop.exec();
            }
        }
        ui.progressBar->setValue(0);
        myMessageOutput(QString::fromLocal8Bit("已完成所有文件上传"));
        ui.textEdit->append(QString::fromLocal8Bit("已完成所有文件上传"));
    }
    mutex.unlock();
}

void FtpUpload::myMessageOutput(const QString& msg)
{
    // 拼接输出信息
    QString strDateTime =
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString strMessage = QString("时间:%2	%1").arg(msg).arg(strDateTime);

    // 写入日志至文件中（读写、追加形式）
    QFile file("log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();
}

void FtpUpload::getFileName(QString DirPath)
{
    if (DirPath == "")
        return;
    QDir* dirinfo = new QDir(DirPath);
    if (!dirinfo->exists()) {
        delete dirinfo, dirinfo = nullptr;
        return;
    }
    QStringList fileList = dirinfo->entryList(QDir::Files);
    fileList.removeOne(".");
    fileList.removeOne("..");
    myMessageOutput(QString::fromLocal8Bit("获取文件名"));
    for (int i = 0; i < fileList.length(); i++) {
        QString strName = fileList[i];
        myMessageOutput(strName);
    }
}

void FtpUpload::mousePressEvent(QMouseEvent* event)
{
    //    if (event->button() == Qt::LeftButton)
    //    {
    //        dragPosition = event->globalPos() -
    //        this->frameGeometry().topLeft(); event->accept();
    //    }
}

void FtpUpload::mouseMoveEvent(QMouseEvent* event)
{
    //    if (event->buttons() == Qt::LeftButton)
    //    {
    //        move(event->globalPos() - dragPosition);
    //        event->accept();
    //    }
}

#ifndef BIN
/**********************************************  start
 * @projectName   FtpUpload2
 * @brief
 * @param         basePath
 * @return        int
 * @author        bin
 * @date          2023-03-01
 ***********************************************/
// 组件初始化
void FtpUpload::initComponent(bool enable)
{
    ui.CB_EncodingFormat->setEnabled(enable);
    ui.pushButton_Refush->setEnabled(enable);
    ui.pushButton_Back->setEnabled(enable);
    ui.cancelBtn->setEnabled(enable);
    ui.pushButton_ComfirmT->setEnabled(enable);
    ui.pushButton_CancelT->setEnabled(enable);
    ui.uploadButton->setEnabled(enable);
    ui.uploadButton_All->setEnabled(enable);
    ui.downloadButton->setEnabled(enable);
    ui.dateEdit->setEnabled(enable);
    ui.timeEdit->setEnabled(enable);

    ui.treeWidget->setEnabled(enable);

    ui.toolButton_dir->setEnabled(enable);
    ui.toolButton_dir_2->setEnabled(enable);
    ui.toolButton_file->setEnabled(enable);
    ui.lineEdit_DirPath->setEnabled(enable);
    ui.lineEdit_DirPath_2->setEnabled(enable);
    ui.lineEdit_FilePath->setEnabled(enable);

    ui.radioButtonActive->setEnabled(enable);
    ui.radioButtonPassive->setEnabled(enable);
}

// 上传文件夹
void FtpUpload::UpFileList(QString path)
{
    //    QString currentPath = path;
    QDir dir(path);
    if (QFileInfo(path).isDir()) {
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it  = fileLst.end();
        for (auto it = fileLst.begin(); it != end_it; it++) {
            QFile* file = new QFile(it->filePath(), this);
            if (!file->open(QIODevice::ReadOnly)) {
                myMessageOutput("file open failed.");
            }
            m_ftp->put(file, toSpecialEncoding(it->fileName()));
//            sleep(100);
            file->close();
            file = NULL;
        }

        QFileInfoList dirlist = dir.entryInfoList(QDir::Dirs);

        myMessageOutput(QString::number(dirlist.count()));

        if (dirlist.count() > 2) {
            auto it_end = dirlist.end();
            int  i      = 2;
            for (auto it = dirlist.begin() + 2;
                 it != it_end && i <= dirlist.count(); it++, i++) {
                QString temp     = dirlist[i].filePath();
                QString tempname = dirlist[i].fileName();

                if (dirlist[i].isDir()) {
                    m_ftp->mkdir(toSpecialEncoding(tempname));
//                    sleep(100);
                    currentPath += "/" + tempname;
                    m_ftp->cd(toSpecialEncoding(currentPath));
//                    sleep(100);
                }

                UpFileList(temp);
//                sleep(100);

                backUp();
            }
        }
    }
}

// 暂停
void FtpUpload::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < reachTime) {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

// 返回上一级
void FtpUpload::backUp()
{
    QString strLeft = currentPath.left(currentPath.lastIndexOf('/'));
    currentPath     = strLeft;
    if (currentPath.isEmpty()) {
        m_ftp->cd(toSpecialEncoding("/"));
    }
    else {
        m_ftp->cd(toSpecialEncoding(currentPath));
    }
    sleep(100);
    ui.treeWidget->clear();
    m_ftp->list();
}

// 上传自定义文件夹
void FtpUpload::UploadCustomDir(QString path, QString pathname)
{
    if (QDir(path).exists()) {
        m_ftp->mkdir(toSpecialEncoding(pathname));
//        sleep(100);
        if (isDirectory.value(toSpecialEncoding(pathname))) {
            if (true) {
                ui.treeWidget->clear();
                currentPath += "/" + pathname;
                m_ftp->cd(toSpecialEncoding(pathname));
//                sleep(100);
                ui.treeWidget->clear();
            }
        }
        UpFileList(path);
        backUp();
        ui.treeWidget->clear();
        m_ftp->list();
    }
}

// 文件夹上传或下载
void FtpUpload::on_downloadButton_clicked()
{
    if (ui.downloadButton->text() == QString::fromLocal8Bit("文件夹上传")) {
        QString       temp = ui.lineEdit_DirPath_2->text();
        const QString pathname =
            temp.mid(temp.lastIndexOf('/') + 1, temp.length() - 1);

        uploadStatusEvent(true, "文件夹 : " , pathname);

        m_ftp->mkdir(toSpecialEncoding(pathname));
//        sleep(100);
        currentPath += "/" + pathname;
        m_ftp->cd(toSpecialEncoding(currentPath));
//        sleep(100);
        UpFileList(ui.lineEdit_DirPath_2->text());
        backUp();

        uploadStatusEvent(false, "文件夹 : ", pathname);
    }
}

// 上传状态提示
void FtpUpload::uploadStatusEvent(bool ing, const char * prefixnotice, QString content)
{
    ui.downloadButton->setEnabled(!ing);
    ui.uploadButton_All->setEnabled(!ing);
    ui.uploadButton->setEnabled(!ing);
    ui.CB_EncodingFormat->setEnabled(!ing);
    ui.pushButton_Login->setEnabled(!ing);
    ui.pushButton_Quit->setEnabled(!ing);
    ui.treeWidget->setEnabled(!ing);
    ui.toolButton_dir->setEnabled(!ing);
    ui.toolButton_dir_2->setEnabled(!ing);
    ui.toolButton_file->setEnabled(!ing);

    ui.cancelBtn->setEnabled(ing);

    content = QString::fromLocal8Bit(prefixnotice) + content;
    if (ing)
    {
        content += QString::fromLocal8Bit(" 上传中......");
    }
    else
    {
        content += QString::fromLocal8Bit(" 上传成功!!!");
        ui.progressBar->setVisible(false);
    }
    ui.statusLabel->setText(content);

    ui.treeWidget->setFocus();
//    sleep(10);
}

/**********************************************  end
 * @author        bin
 * @date          2023-03-02
 ***********************************************/
#endif
