#include "ftpupload.h"
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QThread>

struct DefaultPath Default;

FtpUpload::FtpUpload(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    InitWidget();
}

FtpUpload::~FtpUpload()
{
    m_timer->stop();

    if(group != NULL)
        delete group;

    if(m_timer != NULL)
        delete m_timer;
}

void FtpUpload::InitWidget()
{
    //this->setWindowFlags(Qt::FramelessWindowHint);

    ui.progressBar->setValue(0);
    ui.progressBar->setVisible(false);

    m_ftp = new QFtp();
    m_ftp->setTransferMode(QFtp::Active);

    ReadDefaultPath();

    //瀹氭椂鍣
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);//闈炲崟娆¤Е鍙戜細閫犳垚瀹氭椂鍣ㄦ瘡10鍒嗛挓涓€涓棿闅斾笉鏂惊鐜

    //娣诲姞缁勬寜閽
    group = new QButtonGroup(this);
    group->addButton(ui.radioButtonActive);
    group->addButton(ui.radioButtonPassive);
    group->setExclusive(true);//璁剧疆涓轰簰鏂
    ui.radioButtonActive->setChecked(true);

    //璁剧疆鑳屾櫙棰滆壊
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(76,76,76));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    ui.treeWidget->setStyleSheet("QTreeView{color: white;background:transparent;border:1px solid;}"
        "QTreeView::item:selected {background: rgb(69, 187, 217);}"
        "QTreeView::item:selected:active{background: rgb(69, 187, 217);}");

    //璁剧疆鏍戝垪琛ㄥ搴﹀彲璋冭妭锛岃缃〃澶磋儗鏅€忔槑锛屾爣棰樻枃瀛椾负钃濊壊,瀛椾綋澶у皬涓2
    header = ui.treeWidget->header();
    header->show();
    QFont font;
    font.setPointSize(12);
    header->setFont(font);
    header->setStyleSheet("QHeaderView::section {background-color: #383838;"
        "color: rgb(69, 187, 217);border: none;}");

    //淇″彿涓庢Ы
    connect(ui.closeButton,SIGNAL(clicked()),this,SLOT(close()));				//鍏抽棴
    connect(ui.minButton,SIGNAL(clicked()),this,SLOT(showMinimized()));         //鏈€灏忓寲

    //杩涘害鏉℃樉绀
    connect(m_ftp,SIGNAL(dataTransferProgress(qint64,qint64)),SLOT(S_upDateProgress(qint64,qint64)));

    //鐘舵€佹樉绀
    connect(m_ftp,SIGNAL(commandFinished(int,bool)),SLOT(S_commandFinish(int,bool)));

    connect(m_ftp,SIGNAL(commandStarted(int)),this,SLOT(ftpCommandStarted(int)));

    //娣诲姞鏂囦欢椤
    connect(m_ftp, SIGNAL(listInfo(const QUrlInfo &)),this, SLOT(addToList(const QUrlInfo &)));

    //杩斿洖
    connect(ui.treeWidget, SIGNAL(itemActivated(QTreeWidgetItem *, int)),
        this, SLOT(processItem(QTreeWidgetItem *, int)));
    ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(on_treeWidget_customContextMenuRequested(QPoint)));

    connect(m_ftp,SIGNAL(stateChanged(int)),this,SLOT(ftpStateChanged(int)));

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
    ui.pushButton_Quit->setVisible(false);
    ui.statusLabel->setVisible(false);
    ui.setButton->setVisible(false);
    ui.minButton->setVisible(false);
    ui.closeButton->setVisible(false);
    ui.ipLabel_7->setVisible(true);
    ui.lineEdit_DirPath_2->setVisible(true);
    ui.toolButton_dir_2->setVisible(true);
    ui.radioButton->setVisible(false);
    ui.widget->setBaseSize(500, 1000);
    ui.radioButtonActive->setChecked(Default.initiative);
    ui.radioButtonPassive->setChecked(Default.passive);
    ui.downloadButton->setVisible(true);
    ui.CB_EncodingFormat->addItem("GBK");
    ui.CB_EncodingFormat->addItem("UTF-8");
    ui.CB_EncodingFormat->setCurrentIndex(0);
    ui.radioButtonActive->setChecked(false);
    ui.radioButtonPassive->setChecked(true);
    ui.downloadButton->setText(QString::fromLocal8Bit("锟侥硷拷锟斤拷锟较达拷"));
    ui.CB_EncodingFormat->setCurrentIndex(Default.encoding);
    ui.minButton->setVisible(false);

}

//鐣岄潰鍏抽棴閲嶈浇
void FtpUpload::closeEvent(QCloseEvent *e)
{
    myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷乇锟));
    WriteDefaultPath();
    e->accept();
}

//锟斤拷录
void FtpUpload::on_pushButton_Login_clicked()
{
    QString  str = ui.pushButton_Login->text();
    if(str == QString::fromLocal8Bit("注锟斤拷"))
    {
        m_ftp->close();
        ui.pushButton_Login->setText(QString::fromLocal8Bit("锟斤拷录"));
        ui.treeWidget->clear();
        isDirectory.clear();
    }
    else
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷录"));
        auto ip = ui.lineEdit_Host->text();
        auto port = ui.lineEdit_Port->text();
        auto userName = ui.lineEdit_User->text();
        auto psw = ui.lineEdit_pad->text();
        myMessageOutput(ip);
        myMessageOutput(port);
        myMessageOutput(userName);
        myMessageOutput(psw);
        ui.treeWidget->clear();
        if(!(ip.isEmpty() && port.isEmpty()
             && userName.isEmpty() && psw.isEmpty()))
        {
            int ret = m_ftp->connectToHost(ip,port.toInt());

            if (ret >= QFtp::Connecting)
            {
                int ret2 = m_ftp->login(userName,psw); // 锟斤拷陆锟斤拷锟斤拷锟斤拷

                if (ret2 < QFtp::Connected)
                {
                    return; // 锟斤拷录失锟斤拷
                }
            }
        }
        else
        {
            ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷为锟斤拷"));
        }
    }
}

//锟皆讹拷锟斤拷录
void FtpUpload::on_checkBox_AutoLogin_clicked(bool checked)
{
    bool ret = ui.radioButton->isChecked();
    if(checked == true)
    {
        myMessageOutput(QString::fromLocal8Bit("锟皆讹拷锟斤拷录"));
        on_pushButton_Login_clicked();
        ui.pushButton_ComfirmT->setEnabled(false);
        ui.pushButton_CancelT->setEnabled(true);
        ui.timeEdit->setEnabled(false);
        ConfirmT();
    }
}

//状态锟斤拷示
void FtpUpload::S_commandFinish(int tmp, bool en)
{
    Q_UNUSED(tmp);

    if(m_ftp->currentCommand() == QFtp::ConnectToHost)
    {
        if(en)
        {
            myMessageOutput(QString::fromLocal8Bit("锟斤拷锟接凤拷锟斤拷锟斤拷锟斤拷锟街达拷锟斤拷"));
            ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟接凤拷锟斤拷锟斤拷锟斤拷锟街达拷锟斤拷%1").arg(m_ftp->errorString()));
        }
        else
        {
            myMessageOutput("锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷锟缴癸拷");
            ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷锟缴癸拷"));
        }
    }

    if (m_ftp->currentCommand() == QFtp::Login)
    {

        if(en)
        {
            myMessageOutput(QString::fromLocal8Bit("锟斤拷录锟斤拷锟街达拷锟斤拷"));
            ui.textEdit->append(QString::fromLocal8Bit("锟斤拷录锟斤拷锟街达拷锟斤拷%1").arg(m_ftp->errorString()));
        }
        else
        {
            myMessageOutput(QString::fromLocal8Bit("锟斤拷录锟缴癸拷"));
            ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷录锟缴癸拷"));
            ui.textEdit->append(QString::fromLocal8Bit("锟斤拷录锟斤拷锟斤拷锟斤拷锟缴癸拷"));
            ui.pushButton_Login->setText(QString::fromLocal8Bit("注锟斤拷"));

            if(strDirPath != "")
            {
                ui.lineEdit_DirPath->setText(strDirPath);
            }

            if(strDirPath2 != "")
            {
                ui.lineEdit_DirPath_2->setText(strDirPath2);
            }

            currentPath = Default.m_TargetPath;
            if(currentPath != "")
                m_ftp->cd(toSpecialEncoding(currentPath));
            ui.treeWidget->clear();
            m_ftp->list();
        }
    }

    if (m_ftp->currentCommand() == QFtp::Get)
    {
        if(en)
        {
            ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟截筹拷锟街达拷锟斤拷%1").arg(m_ftp->errorString()));

            qDebug() << (QString::fromLocal8Bit("锟斤拷锟截筹拷锟街达拷锟斤拷%1").arg(m_ftp->errorString()));
        }
        else
        {
            ui.textEdit->append(QString::fromLocal8Bit("锟窖撅拷锟斤拷锟斤拷锟斤拷锟));
            qDebug() << (QString::fromLocal8Bit("锟窖撅拷锟斤拷锟斤拷锟斤拷锟));
        }
        refreshed();
    }

    else if(m_ftp->currentCommand() == QFtp::Put)
    {
        if(en)
        {
            myMessageOutput(QString::fromLocal8Bit("锟较达拷锟斤拷锟街达拷锟斤拷%1").arg(m_ftp->errorString()));
            ui.textEdit->append(QString::fromLocal8Bit("锟较达拷锟斤拷锟街达拷锟斤拷%1").arg(m_ftp->errorString()));
        }
        else
        {
            //if(m_loop.isRunning())
//            m_loop.exit();
            myMessageOutput(QString::fromLocal8Bit("锟窖撅拷锟斤拷锟斤拷募锟斤拷洗锟));
        }
    }

    else if (m_ftp->currentCommand() == QFtp::Close)
    {
        myMessageOutput(QString::fromLocal8Bit("锟窖撅拷锟截憋拷锟斤拷锟斤拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟窖撅拷锟截憋拷锟斤拷锟斤拷"));
    }

    else if (m_ftp->currentCommand() == QFtp::Unconnected)
    {
        myMessageOutput(QString::fromLocal8Bit("锟较匡拷锟斤拷锟斤拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟较匡拷锟斤拷锟斤拷"));
    }

    else if(m_ftp->currentCommand() == QFtp::Rename)
    {
        myMessageOutput(QString::fromLocal8Bit("锟侥硷拷锟斤拷锟斤拷锟斤拷锟缴癸拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟侥硷拷锟斤拷锟斤拷锟斤拷锟缴癸拷"));
        refreshed();
    }

    else if(m_ftp->currentCommand() == QFtp::Mkdir)
    {
        myMessageOutput(QString::fromLocal8Bit("锟铰斤拷锟侥硷拷锟叫成癸拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟铰斤拷锟侥硷拷锟叫成癸拷"));
        refreshed();
    }

    else if(m_ftp->currentCommand() == QFtp::Remove)
    {
        myMessageOutput(QString::fromLocal8Bit("锟侥硷拷删锟斤拷锟缴癸拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟侥硷拷删锟斤拷锟缴癸拷"));
    }

    else if(m_ftp->currentCommand() == QFtp::Rmdir)
    {
        myMessageOutput(QString::fromLocal8Bit("锟侥硷拷锟斤拷删锟斤拷锟缴癸拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟侥硷拷锟斤拷删锟斤拷锟缴癸拷"));
//        refreshed();
    }
}

void FtpUpload::ftpCommandStarted(int tem)
{
    if(m_ftp->currentCommand() == QFtp::ConnectToHost)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷..."));
        ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷锟斤拷"));
    }
    if (m_ftp->currentCommand() == QFtp::Login)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟节碉拷录..."));
        ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷锟节碉拷录锟斤拷"));
    }
    if (m_ftp->currentCommand() == QFtp::Get)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷..."));
        ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟截★拷"));
    }
    if (m_ftp->currentCommand() == QFtp::Put)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟较达拷..."));
        ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷锟斤拷锟较达拷锟斤拷"));
    }
    else if (m_ftp->currentCommand() == QFtp::Close)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟节关憋拷锟斤拷锟斤拷..."));
        ui.statusLabel->setText(QString::fromLocal8Bit("锟斤拷锟节关憋拷锟斤拷锟接★拷"));
    }
}

void FtpUpload::ftpStateChanged(int state)
{
    if(state == QFtp::Unconnected)
    {
        IsLogin = false;
        myMessageOutput(QString::fromLocal8Bit("未锟斤拷锟接碉拷锟斤拷锟斤拷"));
        ui.textEdit->append(QString::fromLocal8Bit("未锟斤拷锟接碉拷锟斤拷锟斤拷"));
        ui.pushButton_Login->setText(QString::fromLocal8Bit("锟斤拷录"));
        ui.treeWidget->clear();
        //锟斤拷录
        //on_pushButton_Login_clicked();
    }
    if(state == QFtp::Connected)
    {
        myMessageOutput(QString::fromLocal8Bit("锟窖撅拷锟斤拷锟接碉拷锟斤拷锟斤拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟窖撅拷锟斤拷锟接碉拷锟斤拷锟斤拷"));
    }
    if(state == QFtp::HostLookup)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟节诧拷锟斤拷锟斤拷锟斤拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟节诧拷锟斤拷锟斤拷锟斤拷"));
    }
    if(state == QFtp::LoggedIn)
    {
        myMessageOutput(QString::fromLocal8Bit("锟窖撅拷锟斤拷录"));
        ui.textEdit->append(QString::fromLocal8Bit("锟窖撅拷锟斤拷录"));
        IsLogin = true;
    }
    if(state == QFtp::Closing)
    {
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟节关憋拷"));
        ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟节关憋拷"));
    }
}

void FtpUpload::addToList(const QUrlInfo &urlInfo)
{
    QString fileSize; //锟斤拷锟节存储锟侥硷拷锟斤拷小锟斤拷锟斤拷锟斤拷锟侥硷拷锟斤拷小锟街节ｏ拷锟斤拷锟斤拷锟侥硷拷锟斤拷锟斤拷锟叫憋拷锟侥碉拷位
    if(urlInfo.size() >=0 && urlInfo.size() < 1024)
    {
        fileSize = QString::number(urlInfo.size()) + "Byte";
    }
    else if(urlInfo.size() >= 1024 && urlInfo.size() < 1024*1024)
    {
        fileSize = QString::number(urlInfo.size()/1024.0,'f',2) + "KB";
    }
    else if(urlInfo.size() >= 1024*1024 && urlInfo.size() < 1024*1024*1024)
    {
        fileSize = QString::number(urlInfo.size()/1024/1024.0,'f',2) + "MB";
    }
    else if(urlInfo.size() >= 1024*1024*1024)
    {
        fileSize = QString::number(urlInfo.size()/1024/1024/1024.0,'f',2) + "GB";
    }

    QTreeWidgetItem *item = new QTreeWidgetItem;

    item->setText(0, fromSpecialEncoding(urlInfo.name()));
    item->setText(1, fileSize);
    item->setText(2, urlInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
    item->setText(3, urlInfo.owner());
    item->setText(4, urlInfo.group());

    QPixmap pixmap(urlInfo.isDir() ? ":/img/img/dir.png" : ":/img/img/file.png");
    item->setIcon(0, pixmap);
    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui.treeWidget->addTopLevelItem(item);
    if (!ui.treeWidget->currentItem())
    {
        ui.treeWidget->setCurrentItem(ui.treeWidget->topLevelItem(0));
        ui.treeWidget->setEnabled(true);
    }
}

//双锟斤拷锟斤拷锟斤拷
void FtpUpload::processItem(QTreeWidgetItem *item, int column)
{
    myMessageOutput(QString::fromLocal8Bit("双锟斤拷锟斤拷锟斤拷"));
    Q_UNUSED(column)//锟斤拷锟轿词癸拷玫谋锟斤拷锟斤拷锟斤拷志锟斤拷锟斤拷锟斤拷锟斤拷
    QString name = item->text(0);
    QString str  = toSpecialEncoding(name);
    qDebug() << name << str << endl;
    if (isDirectory.value(str))
    {
        qDebug() << name << str << endl;
        ui.treeWidget->clear();
        isDirectory.clear();
        currentPath += "/" + name;
        m_ftp->cd(str);
        m_ftp->list();
        return;
    }
}

//刷锟斤拷
void FtpUpload::on_pushButton_Refush_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("刷锟斤拷"));
    ui.treeWidget->clear();
    ui.treeWidget->clear();
    m_ftp->list();
}

//锟斤拷锟斤拷
void FtpUpload::on_pushButton_Back_clicked()
{
    ui.treeWidget->clear();
    isDirectory.clear();
    QString strLeft = currentPath.left(currentPath.lastIndexOf('/'));
    currentPath = strLeft;
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

//锟较达拷锟侥硷拷
void FtpUpload::on_uploadButton_clicked()
{
    if(IsLogin == false)
        on_pushButton_Login_clicked();

    myMessageOutput(QString::fromLocal8Bit("锟较达拷锟侥硷拷"));
    auto fileName = ui.lineEdit_FilePath->text();
    QFile *m_File = new QFile(fileName);
    if (QFile::exists(fileName))
    {
        ui.progressBar->setVisible(true);

        qDebug() << QString::fromLocal8Bit("锟侥硷拷%1锟斤拷锟斤拷通锟较达拷... ...").arg(fileName);

        // fixme: try...catch...finally
        if (!m_File->isOpen()) {
            QFileInfo fi(fileName);
            QString filename = fi.fileName();

            m_ftp->put(m_File,toSpecialEncoding(filename));  //锟较达拷
            refreshed();
        }
        else {
            ui.textEdit->append(QString::fromLocal8Bit("锟侥硷拷锟斤拷占锟斤拷"));
            QMessageBox::warning(NULL, QString::fromLocal8Bit("锟侥硷拷锟较达拷")
                                 , QString::fromLocal8Bit("锟侥硷拷锟斤拷占锟斤拷"));
        }

        m_File->close();
        m_File = NULL;
    }
    WriteDefaultPath();
    return;
}

//锟斤拷锟斤拷锟较达拷
void FtpUpload::on_uploadButton_All_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟较达拷"));
    if(strDirPath != "")
    {
        ui.lineEdit_DirPath->setText(strDirPath);
    }
    if(strDirPath2 != "")
    {
        ui.lineEdit_DirPath_2->setText(strDirPath2);
    }

    auto path = ui.lineEdit_DirPath->text();
    auto path2 = ui.lineEdit_DirPath_2->text();
    //getFileName(path);
    //getFileName(path2);
    Batch_upload(path);
    //    Batch_upload2(path2);

//    WriteDefaultPath();
}

//选锟斤拷锟侥硷拷路锟斤拷
void FtpUpload::on_toolButton_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("锟斤拷锟侥硷拷锟斤拷锟斤拷锟斤拷"), ".", "*");
    if(fileName.isNull())
        return;

    if (!QFile::exists(fileName))
    {
        return;
    }

    ui.lineEdit_FilePath->setText(fileName);
}

//选锟斤拷锟侥硷拷锟斤拷路锟斤拷
void FtpUpload::on_toolButton_dir_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this);
    ui.lineEdit_DirPath->setText(path);
}

//选锟斤拷锟侥硷拷锟斤拷2路锟斤拷
void FtpUpload::on_toolButton_dir_2_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this);
    ui.lineEdit_DirPath_2->setText(path);
}

void FtpUpload::S_upDateProgress(qint64 _used, qint64 _total)
{
    auto percent = (qreal)_used/_total*100;
    ui.progressBar->setValue(percent);
}

//确锟斤拷锟斤拷时锟较达拷
void FtpUpload::on_pushButton_ComfirmT_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("确锟斤拷锟斤拷时锟较达拷"));
    ConfirmT();
}

//取锟斤拷锟斤拷时锟较达拷
void FtpUpload::on_pushButton_CancelT_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("取锟斤拷锟斤拷时锟较达拷"));
    CancelT();
}

//取锟斤拷锟斤拷锟斤拷
void FtpUpload::on_cancelBtn_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("取锟斤拷锟斤拷锟斤拷"));
    m_ftp->abort();
    ui.progressBar->setValue(0);
}

//锟剿筹拷
void FtpUpload::on_pushButton_Quit_clicked()
{

}

void FtpUpload::GetTime()
{
    QTime current_time = QTime::currentTime();
    int current_hour = current_time.hour();//锟斤拷前锟斤拷小时
    int current_minute = current_time.minute();//锟斤拷前锟侥凤拷
    int current_second = current_time.second();//锟斤拷前锟斤拷锟斤拷

    int set_hour = ui.timeEdit->time().hour();
    int set_minute = ui.timeEdit->time().minute();
    qDebug() << "时" << current_hour << "锟斤拷" << current_minute << "锟斤拷" << current_second;
    qDebug() << "锟斤拷锟斤拷时锟斤拷" << set_hour << set_minute;

    if (current_hour == (set_hour + 1) && (60 - current_minute) == 3)
    {
        if(IsLogin == false)
            on_pushButton_Login_clicked();
    }
    else if ((current_hour == set_hour) && (set_minute - current_minute) > 0 && (set_minute - current_minute) == 3)
    {
        if(IsLogin == false)
            on_pushButton_Login_clicked();
    }

    if (current_hour == (set_hour + 1) && (60 - current_minute) == 2)
    {
        myMessageOutput(QString::fromLocal8Bit("停止锟斤拷锟斤拷1"));
        m_timer->stop();
        myMessageOutput(QString::fromLocal8Bit("执锟叫讹拷时锟斤拷锟斤拷1"));
        myMessageOutput(QString::fromLocal8Bit("锟斤拷前时锟戒：%1:%2:%3").arg(current_hour).arg(current_minute).arg(current_second));
        ScheduledUP();
        m_timer->start();
        myMessageOutput(QString::fromLocal8Bit("锟斤拷始锟斤拷锟斤拷"));
    }
    else if ((current_hour == set_hour) && (set_minute - current_minute) > 0 && (set_minute - current_minute) == 2)
    {
        myMessageOutput(QString::fromLocal8Bit("停止锟斤拷锟斤拷2"));
        m_timer->stop();
        myMessageOutput(QString::fromLocal8Bit("执锟叫讹拷时锟斤拷锟斤拷2"));
        myMessageOutput(QString::fromLocal8Bit("锟斤拷前时锟戒：%1:%2:%3").arg(current_hour).arg(current_minute).arg(current_second));
        ScheduledUP();
        m_timer->start();
        myMessageOutput(QString::fromLocal8Bit("锟斤拷始锟斤拷锟斤拷"));
    }
}

void FtpUpload::on_radioButtonActive_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷"));
    m_ftp->setTransferMode(QFtp::Active);
}

void FtpUpload::on_radioButtonPassive_clicked()
{
    myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷"));
    m_ftp->setTransferMode(QFtp::Passive);
}

//锟斤拷锟接菜碉拷
void FtpUpload::on_treeWidget_customContextMenuRequested(const QPoint)
{
    static int status = 1;
    if (status == 1) {
        popMenu = new QMenu(this);           //锟斤拷锟斤拷一锟斤拷锟揭硷拷锟斤拷锟斤拷锟剿碉拷
        cdToParent = popMenu->addAction(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷一锟斤拷"));
        upload = popMenu->addAction(QString::fromLocal8Bit("锟较达拷"));
        download = popMenu->addAction(QString::fromLocal8Bit("锟斤拷锟斤拷"));
        popMenu->addSeparator();        //锟斤拷锟斤拷一锟斤拷锟街革拷锟斤拷
        reName = popMenu->addAction(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷"));
        createFolder = popMenu->addAction(QString::fromLocal8Bit("锟铰斤拷锟侥硷拷锟斤拷"));
        popMenu->addSeparator();
        removeFile = popMenu->addAction(QString::fromLocal8Bit("删锟斤拷锟侥硷拷"));
        removeFolder = popMenu->addAction(QString::fromLocal8Bit("删锟斤拷锟侥硷拷锟斤拷"));
        popMenu->addSeparator();
        refresh = popMenu->addAction(QString::fromLocal8Bit("刷锟斤拷"));
        if(ui.treeWidget->topLevelItemCount() == 0)//锟斤拷锟节碉拷为锟斤拷
        {
            upload->setEnabled(false);
            download->setEnabled(false);
            reName->setEnabled(false);
            createFolder->setEnabled(false);
            removeFile->setEnabled(false);
            removeFolder->setEnabled(false);
            refresh->setEnabled(false);
        }

        connect(cdToParent,SIGNAL(triggered()),this,SLOT(on_pushButton_Back_clicked()));
        connect(upload,SIGNAL(triggered()),this,SLOT(on_uploadButton_clicked()));
        connect(reName,SIGNAL(triggered()),this,SLOT(fileRename()));
        connect(createFolder,SIGNAL(triggered()),this,SLOT(createNewFolder()));
        connect(removeFile,SIGNAL(triggered()),this,SLOT(deleteFile()));
        connect(removeFolder,SIGNAL(triggered()),this,SLOT(deleteFolder()));
        connect(refresh,SIGNAL(triggered()),this,SLOT(refreshed()));


        //锟斤拷锟矫菜碉拷锟斤拷锟
        popMenu->setStyleSheet("QMenu{background-color: white;}"
                               "QMenu::item {background-color: transparent;"
                               "padding:6px 30px;}"
                               "QMenu::item:selected {background-color: #2dabf9;}");
        popMenu->exec(QCursor::pos());//锟斤拷锟斤拷锟揭硷拷锟剿碉拷锟斤拷锟剿碉拷位锟斤拷为锟斤拷锟轿伙拷锟
        popMenu->clear();
        delete popMenu;
        popMenu = nullptr;
    }
    else {

    }
    status *= -1;
}

//锟侥硷拷锟斤拷锟斤拷锟斤拷
void FtpUpload::fileRename()
{
    QString oldName = ui.treeWidget->currentItem()->text(0);
    QString str = toSpecialEncoding(oldName);
    if(isDirectory.value(str))//选锟叫碉拷锟斤拷锟侥硷拷锟叫ｏ拷锟津返伙拷
    {
        QMessageBox::information(this, QString::fromLocal8Bit("锟斤拷锟斤拷"), QString::fromLocal8Bit("<font size='6' color='#008ed5'>锟侥硷拷锟叫诧拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷</font>"), QMessageBox::Ok);
        return;
    }
    bool ok;
    QString newName = QInputDialog::getText(this, QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷"),
                                            QString::fromLocal8Bit("锟斤拷锟侥硷拷锟斤拷锟斤拷"),
                                            QLineEdit::Normal, QString::fromLocal8Bit(""),
                                            &ok,Qt::WindowCloseButtonHint);
    if(newName.isEmpty())
        return;
    m_ftp->rename(toSpecialEncoding(oldName),toSpecialEncoding(newName));
}

//锟铰斤拷锟侥硷拷锟斤拷
void FtpUpload::createNewFolder()
{
    bool ok;
    QString folderName = QInputDialog::getText(this, QString::fromLocal8Bit("锟铰斤拷锟侥硷拷锟斤拷"),
                                               QString::fromLocal8Bit("锟斤拷锟侥硷拷锟斤拷锟斤拷锟斤拷"),
                                               QLineEdit::Normal, QString::fromLocal8Bit(""),
                                               &ok,Qt::WindowCloseButtonHint);
    if(folderName.isEmpty())
        return;
    m_ftp->mkdir(toSpecialEncoding(folderName));

    ui.treeWidget->clear();
    m_ftp->list();
}

//删锟斤拷锟侥硷拷
void FtpUpload::deleteFile()
{
    QString deleteFile = ui.treeWidget->currentItem()->text(0);
    QString str = toSpecialEncoding(deleteFile);
    if(isDirectory.value(str))//选锟叫碉拷锟斤拷锟侥硷拷锟叫ｏ拷锟津返伙拷
    {
        return;
    }
    QTreeWidgetItem* item = ui.treeWidget->currentItem();
    if(item->childCount() > 0)//锟斤拷锟斤拷锟斤拷咏诘悖拷锟缴撅拷锟
    {
        for(int i = 0; i < item->childCount(); i ++)
        {
            deleleNode(item->child(i));
        }
    }
    delete item;
    if(ui.treeWidget->topLevelItemCount()<= 0)
    {
        //ui.pushButton_Back->setEnabled(true);
    }

    m_ftp->remove(toSpecialEncoding(deleteFile));
}

//刷锟斤拷
void FtpUpload::refreshed()
{
    m_ftp->cd(currentPath);
    ui.treeWidget->clear();
    m_ftp->list();
}

//删锟斤拷锟斤拷锟斤拷目锟节碉拷
void FtpUpload::deleleNode(QTreeWidgetItem* node)
{
    if(node->childCount() > 0)
    {
        for(int i = 0; i < node->childCount(); i ++)
        {
            deleleNode(node->child(i));
        }
    }
    else
    {
        delete node;
    }
}

//删锟斤拷锟侥硷拷锟斤拷
void FtpUpload::deleteFolder()
{
    QString folder = ui.treeWidget->currentItem()->text(0);
    QString str = toSpecialEncoding(folder);
    if(isDirectory.value(str))
    {
        m_ftp->rmdir(toSpecialEncoding(folder));
    }
}

void FtpUpload::ConfirmT()
{
    m_timer->start(); //锟斤拷锟斤拷锟斤拷时锟斤拷
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
}

void FtpUpload::ScheduledUP()
{
    bool ret = ui.radioButton->isChecked();

    //锟斤拷锟窖★拷锟斤拷募锟斤拷锟
    if(ret == true)
    {
        myMessageOutput("选锟斤拷锟斤拷锟斤拷锟较达拷锟侥硷拷");
        //    	on_uploadButton_clicked();
        on_uploadButton_All_clicked();
    }
    else  //锟斤拷锟斤拷选锟斤拷锟侥硷拷
    {
        //    myMessageOutput(QString::fromLocal8Bit("选锟斤拷锟斤拷锟斤拷锟较达拷锟侥硷拷"));

        // fixme: 锟皆讹拷锟较达拷锟斤拷锟斤拷锟侥硷拷锟斤拷   2023/2锟斤拷28锟斤拷锟斤拷锟  2023/2锟斤拷29锟斤拷夜锟斤拷

        const QString temp = ui.lineEdit_DirPath->text();
        QDate today = QDate::currentDate().addDays(-1);
        int month = today.month();
        int day = today.day();

        QString morningname = QString::fromLocal8Bit("%1锟斤拷%2锟秸白帮拷")
                .arg(QString::number(month))
                .arg(QString::number(day));
        QString morning = QString::fromLocal8Bit("%1/%2")
                .arg(temp).arg(morningname);
        UploadCustomDir(morning, morningname);

        QString eveningname = QString::fromLocal8Bit("%1锟斤拷%2锟斤拷夜锟斤拷")
                .arg(QString::number(month))
                .arg(QString::number(day));
        QString evening = QString::fromLocal8Bit("%1/%2")
                .arg(temp).arg(eveningname);
        UploadCustomDir(evening, eveningname);
    }
}

//锟斤拷取锟斤拷锟斤拷锟侥硷拷
void FtpUpload::ReadDefaultPath()
{
    QString path = "./device.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));
    myMessageOutput(QString::fromLocal8Bit("锟斤拷取默锟斤拷锟斤拷锟矫ｏ拷锟斤拷一锟斤拷锟斤拷锟斤拷状态锟斤拷"));
    QString retStr1 =  config->value(QString("Login/Host")).toString();
    Default.m_HostStr = retStr1;

    Default.m_port = config->value(QString("Login/port")).toInt();

    QString retStr2 = config->value(QString("Login/UserName")).toString();
    Default.UserStr = retStr2;

    QString retStr3 = config->value(QString("Login/PassWord")).toString();
    Default.PasswordStr = retStr3;

    Default.Hour =config->value(QString("Time/Hour")).toInt();
    Default.Minute =config->value(QString("Time/Minute")).toInt();

    QString retStr4 = config->value(QString("Path/SourcePath")).toString();
    Default.m_SourcePath = retStr4;
    QString retStr5 = config->value(QString("Path/SourcePath2")).toString();
    Default.m_SourcePath2 = retStr5;
    QString retStr6 = config->value(QString("Path/SourcePath3")).toString();
    Default.m_SourcePath3 = retStr6;
    QString retStr7 = config->value(QString("Path/TargetPath")).toString();
    Default.m_TargetPath = retStr7;


    Default.isUploadChecked = config->value(QString("Checked/UploadChecked")).toInt();
    Default.isLoginChecked = config->value(QString("Checked/LoginChecked")).toInt();
    Default.initiative
            = config->value(QString("Checked/ModeCheckedInitiative")).toBool();
    Default.passive
            = config->value(QString("Checked/ModeCheckedPassive")).toBool();
    Default.encoding
            = config->value(QString("Checked/Encoding")).toInt();

    delete config;
}

//写锟斤拷锟斤拷锟斤拷锟侥硷拷
void FtpUpload::WriteDefaultPath()
{
    Default.Hour = ui.timeEdit->time().hour();
    Default.Minute = ui.timeEdit->time().minute();

    QString path = "device.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));

    myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷暮锟斤拷默锟斤拷路锟斤拷"));
    config->clear();
    QString retStr1 = ui.lineEdit_Host->text();
    Default.m_HostStr = retStr1;
    Default.m_port = ui.lineEdit_Port->text().toInt();
    QString retStr2 = ui.lineEdit_User->text();
    Default.UserStr = retStr2;
    QString retStr3 = ui.lineEdit_pad->text();
    Default.PasswordStr = retStr3;
    QString retStr4 = ui.lineEdit_FilePath->text();
    Default.m_SourcePath = retStr4;
    QString retStr5 = ui.lineEdit_DirPath->text();
    Default.m_SourcePath2 = retStr5;
    QString retStr6 = ui.lineEdit_DirPath_2->text();
    Default.m_SourcePath3 = retStr6;
    QString retStr7 = currentPath;
    Default.m_TargetPath = retStr7;
    Default.isUploadChecked = ui.radioButton->isChecked();
    Default.isLoginChecked = ui.checkBox_AutoLogin->isChecked();

    Default.initiative = ui.radioButtonActive->isChecked();
    Default.passive = ui.radioButtonPassive->isChecked();
    Default.encoding = ui.CB_EncodingFormat->currentIndex();


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

//IOS 8859-1 转 UTF_8锟斤拷GBK
QString FtpUpload::fromSpecialEncoding(const QString &inputStr)
{
    if (ui.CB_EncodingFormat->currentIndex() == 0)
    {
        QTextCodec *codec = QTextCodec::codecForName("gbk");
        return codec->toUnicode(inputStr.toLatin1());
    }
    else
    {
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        return codec->toUnicode(inputStr.toLatin1());
    }
}

//UTF_8锟斤拷GBK 转 IOS 8859-1
QString FtpUpload::toSpecialEncoding(const QString &inputStr)
{
    if (ui.CB_EncodingFormat->currentIndex() == 0)
    {
        QTextCodec *codec = QTextCodec::codecForName("gbk");
        return QString::fromLatin1(codec->fromUnicode(inputStr));
    }
    else
    {
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        return QString::fromLatin1(codec->fromUnicode(inputStr));
    }
}

//锟斤拷锟斤拷锟较达拷
void FtpUpload::Batch_upload(QString DirPath)
{
    mutex.lock();

    if(DirPath == "")
    {
        mutex.unlock();
        return;
    }
    myMessageOutput(DirPath);
    QDir dir(DirPath);
    if(dir.exists())
    {
        ui.progressBar->setVisible(true);
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it = fileLst.end();
        for(auto it =  fileLst.begin(); it != end_it; it++)
        {
            QFile *file = new QFile(it->filePath(),this);
            if(!file->open(QIODevice::ReadOnly))
            {
                myMessageOutput("file open failed.");
//                if(m_loop.isRunning())
//                    m_loop.exit();
//                continue;
            }
            ui.textEdit->append(QString::fromLocal8Bit("锟斤拷前锟斤拷锟斤拷锟较达拷:") + it->fileName());
            m_ftp->put(file,toSpecialEncoding(it->fileName()));
            myMessageOutput(QString::fromLocal8Bit("锟斤拷前锟斤拷锟斤拷锟较达拷:") + it->filePath());
//            m_loop.exec();
        }
        ui.treeWidget->clear();
        m_ftp->list();

        ui.progressBar->setValue(0);
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷募锟斤拷洗锟));
        ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷募锟斤拷洗锟));
    }
    mutex.unlock();
}

void FtpUpload::Batch_upload2(QString DirPath)
{
    mutex.lock();

    if(DirPath == "")
    {
        mutex.unlock();
        return;
    }
    myMessageOutput(DirPath);
    QDir dir(DirPath);
    if(dir.exists())
    {
        ui.progressBar->setVisible(true);
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it = fileLst.end();
        for(auto it =  fileLst.begin(); it != end_it; it++)
        {
            QFile *file = new QFile(it->filePath(),this);
            QFileInfo fileinfo(it->filePath());
            QDateTime create = fileinfo.created();
            QString _createTime = create.toString("yyyy-MM-dd");	//锟斤拷取锟侥硷拷锟斤拷锟斤拷时锟斤拷
            QDateTime currentTime = QDateTime::currentDateTime();
            QString currentTimeStr = currentTime.toString("yyyy-MM-dd");			//锟斤拷取锟斤拷前时锟斤拷
            QString beforeDayTimeStr = currentTime.addDays(-1).toString("yyyy-MM-dd");  //锟斤拷取前一锟斤拷时锟斤拷

            if(_createTime == currentTimeStr || _createTime == beforeDayTimeStr)
            {
                if(!file->open(QIODevice::ReadOnly))
                {
                    myMessageOutput(QString::fromLocal8Bit("file open failed."));
                    if(m_loop.isRunning())
                        m_loop.exit();
                    continue;
                }

                ui.textEdit->append(QString::fromLocal8Bit("锟斤拷前锟斤拷锟斤拷锟较达拷:") + it->fileName());
                m_ftp->put(file,toSpecialEncoding(it->fileName()));
                myMessageOutput(QString::fromLocal8Bit("锟斤拷前锟斤拷锟斤拷锟较达拷:") + it->filePath());
                m_loop.exec();
            }
        }
        ui.progressBar->setValue(0);
        myMessageOutput(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷募锟斤拷洗锟));
        ui.textEdit->append(QString::fromLocal8Bit("锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷募锟斤拷洗锟));
    }
    mutex.unlock();
}

void FtpUpload::myMessageOutput(const QString &msg)
{
    // 拼接输出信息
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
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
    if(DirPath == "")
        return;
    QDir* dirinfo = new QDir(DirPath);
    if (!dirinfo->exists())
    {
        delete dirinfo, dirinfo = nullptr;
        return;
    }
    QStringList fileList = dirinfo->entryList(QDir::Files);
    fileList.removeOne(".");
    fileList.removeOne("..");
    myMessageOutput(QString::fromLocal8Bit("获取文件名"));
    for(int i = 0; i<fileList.length();i++ )
    {
        QString strName = fileList[i];
        myMessageOutput(strName);
    }
}

void FtpUpload::mousePressEvent(QMouseEvent *event)
{
//    if (event->button() == Qt::LeftButton)
//    {
//        dragPosition = event->globalPos() - this->frameGeometry().topLeft();
//        event->accept();
//    }
}

void FtpUpload::mouseMoveEvent(QMouseEvent *event)
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
void FtpUpload::UpFileList(QString path)
{
    //    QString currentPath = path;
    QDir dir(path);
    if(QFileInfo(path).isDir())
    {
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it = fileLst.end();
        for(auto it =  fileLst.begin(); it != end_it; it++)
        {
            QFile *file = new QFile(it->filePath(),this);
            if(!file->open(QIODevice::ReadOnly))
            {
                myMessageOutput("file open failed.");
            }
            m_ftp->put(file,toSpecialEncoding(it->fileName()));
            sleep(500);
            file->close();
            file = NULL;
        }
        ui.treeWidget->clear();
        m_ftp->list();

        QFileInfoList dirlist = dir.entryInfoList(QDir::Dirs);
        if (dirlist.count() > 2)
        {
            auto it_end = dirlist.end();
            int i = 2;
            for (auto it = dirlist.begin() + 2; it != it_end && i < dirlist.count()
                 ; it++,i++)
            {
                QString temp = dirlist[i].filePath();
                QString tempname = dirlist[i].fileName();

                if (dirlist[i].isDir())
                {
                    m_ftp->mkdir(toSpecialEncoding(tempname));
                    sleep(100);
                    currentPath += "/" + tempname;

                    m_ftp->cd(toSpecialEncoding(tempname));
                    sleep(100);
                }
                ui.treeWidget->clear();
                m_ftp->list();

                UpFileList(temp);

                backUp();
            }
        }
    }
}

void FtpUpload::sleep(unsigned int msec){
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime()<reachTime)
    {
                QApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void FtpUpload::backUp()
{
    QString strLeft = currentPath.left(currentPath.lastIndexOf('/'));
    currentPath = strLeft;
    if (currentPath.isEmpty())
    {
        m_ftp->cd(toSpecialEncoding("/"));
    }
    else
    {
        m_ftp->cd(toSpecialEncoding(currentPath));
    }
    sleep(100);
    ui.treeWidget->clear();
    m_ftp->list();
}

void FtpUpload::UploadCustomDir(QString path, QString pathname)
{
    if (QDir(path).exists())
    {
        m_ftp->mkdir(toSpecialEncoding(pathname));
        sleep(100);
        if (isDirectory.value(toSpecialEncoding(pathname)))
        {
            if (true)
            {
                ui.treeWidget->clear();
                currentPath += "/" + pathname;
                m_ftp->cd(toSpecialEncoding(pathname));
                sleep(100);
                ui.treeWidget->clear();
            }
        }
        UpFileList(path);
        backUp();
        ui.treeWidget->clear();
        m_ftp->list();
    }
}

void FtpUpload::on_downloadButton_clicked()
{
    if (ui.downloadButton->text() == QString::fromLocal8Bit("文件夹上传")) {
        QString temp = ui.lineEdit_DirPath_2->text();
        const QString pathname = temp.mid(temp.lastIndexOf('/') + 1, temp.length() - 1);

        m_ftp->mkdir(toSpecialEncoding(pathname));
        m_ftp->cd(toSpecialEncoding(pathname));
        UpFileList(ui.lineEdit_DirPath_2->text());
    }
}


/**********************************************  end
 * @author        bin
 * @date          2023-03-02
 ***********************************************/
#endif
