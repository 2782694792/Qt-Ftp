#include "ftpupload.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QTextStream>
#include <QThread>
#include <string>
#include <QApplication>
#include <io.h>

static const QString GetIniPath()
{
//    QString path = QDir::currentPath() + "/FtpUpload.ini";
    const QString path = QCoreApplication::applicationDirPath() + "/FtpUpload.ini";

    return path;
}

static const QString GetLogPath()
{
//    QString path = QDir::currentPath() + "/FtpUpload.ini";
    const QString path = QCoreApplication::applicationDirPath() + "/FtpUpload.log";

    return path;
}

static const QString GetSciUploadLog()
{
    const QString path = QCoreApplication::applicationDirPath() + "/SciFtpUpload.log";

    return path;
}

FtpUpload::FtpUpload(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);

    InitWidget();
}

FtpUpload::~FtpUpload()
{
    m_timer->stop();

    if (group != NULL) {
        delete group;
        group = NULL;
    }

    if (m_timer != NULL) {
        delete m_timer;
        m_timer = NULL;
    }
}

void FtpUpload::InitWidget()
{
    // ԭ��
    {
        this->setWindowFlags(Qt::FramelessWindowHint);

        ui.progressBar->setValue(0);
        ui.progressBar->setVisible(false);

        m_ftp = new QFtp();
        m_ftp->setTransferMode(QFtp::Active);

        ReadDefaultPath();

        // ��ʱ��
        m_timer = new QTimer(this);
        m_timer->setSingleShot(
            false); // �ǵ��δ�������ɶ�ʱ��ÿ10����һ���������ѭ��

        // ����鰴ť
        group = new QButtonGroup(this);
        group->addButton(ui.radioButtonActive);
        group->addButton(ui.radioButtonPassive);
        group->setExclusive(true); // ����Ϊ����
        ui.radioButtonActive->setChecked(true);

        QPalette palette;
        palette.setColor(QPalette::Background, QColor(76, 76, 76));
        this->setAutoFillBackground(true);
        this->setPalette(palette);

        ui.treeWidget->setStyleSheet(
            "QTreeView{color: white;background:transparent;border:1px solid;}"
            "QTreeView::item:selected {background: rgb(69, 187, 217);}"
            "QTreeView::item:selected:active{background: rgb(69, 187, 217);}"
            "QTreeView::item {height: 20px;width:50px;}");

        // �������б��ȿɵ��ڣ����ñ�ͷ����͸������������Ϊ��ɫ,�����СΪ12
        header = ui.treeWidget->header();
        header->show();
        QFont font;
        font.setPointSize(12);
        header->setFont(font);
        header->setDefaultSectionSize(120);
        header->setStyleSheet("QHeaderView::section {background-color: #383838;"
                              "color: rgb(69, 187, 217);border: none;}");

        connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close())); // �ر�
        connect(ui.minButton, SIGNAL(clicked()), this,
                SLOT(showMinimized())); // ��С��

        connect(m_ftp, SIGNAL(dataTransferProgress(qint64, qint64)),
                SLOT(S_upDateProgress(qint64, qint64))); // ��������ʾ

        connect(m_ftp, SIGNAL(commandFinished(int, bool)),
                SLOT(S_commandFinish(int, bool))); // ״̬��ʾ

        connect(m_ftp, SIGNAL(commandStarted(int)), this,
                SLOT(ftpCommandStarted(int)));

        connect(m_ftp, SIGNAL(listInfo(const QUrlInfo&)), this,
                SLOT(addToList(const QUrlInfo&))); // ����ļ���

        connect(ui.treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*, int)),
                this, SLOT(processItem(QTreeWidgetItem*, int))); // ����

        ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(ui.treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this,
                SLOT(on_treeWidget_customContextMenuRequested(QPoint)));

        connect(m_ftp, SIGNAL(stateChanged(int)), this,
                SLOT(ftpStateChanged(int)));

        ui.lineEdit_Host->setText(Default.m_HostStr);
        ui.lineEdit_Port->setText(QString("%1").arg(Default.m_port));
        ui.lineEdit_User->setText(Default.UserStr);
        ui.lineEdit_pad->setText(Default.PasswordStr);
        ui.lineEdit_FilePath->setText(Default.m_SourcePath);
        ui.lineEdit_DirPath->setText(Default.m_SourcePath2);
        ui.lineEdit_DirPath_2->setText(Default.m_SourcePath3);
        ui.timeEdit_evening->setTime(
            QTime(Default.Hour_Evening, Default.Minute_Evening));
        ui.timeEdit->setTime(QTime(Default.Hour, Default.Minute));

        ui.checkBox_AutoLogin->setChecked(Default.isLoginChecked);
        ui.lineEdit_factory->setText(Default.factory);
        ui.lineEdit_manufacturer->setText(Default.manufacturer);
        ui.lineEdit_number->setText(Default.number);
        ui.lineEdit_procedure->setText(Default.procedure);
        ui.lineEdit_station->setText(Default.station);

        currentPath = "";

        connect(m_timer, SIGNAL(timeout()), this, SLOT(GetTime())); // ��ʱ��

        IsLogin = false;

        on_checkBox_AutoLogin_clicked(Default.isLoginChecked);
    }

    // fixme:
    {
        initComponent(false);

        ui.cancelBtn->setEnabled(false);
        ui.pushButton_CancelT->setEnabled(false);

        ui.pushButton_Quit->setVisible(false);
        ui.setButton->setVisible(false);

        ui.radioButtonActive->setChecked(Default.initiative);
        ui.radioButtonPassive->setChecked(Default.passive);
        ui.CB_EncodingFormat->addItem("GBK");
        ui.CB_EncodingFormat->addItem("UTF-8");
        ui.CB_EncodingFormat->setCurrentIndex(0);
        ui.downloadButton->setText(QString::fromLocal8Bit("�ļ����ϴ�"));
        ui.CB_EncodingFormat->setCurrentIndex(Default.encoding);

        ui.label_currentpath->setAlignment(Qt::AlignLeft);
        ui.label_currentpath->setAlignment(Qt::AlignVCenter);

//        if(Default.autoUpload)
//        {
//            initComponent(false);
//            try {
//                m_timer->stop();
//                m_ftp->close();

//                ui.pushButton_Login->setEnabled(true);
//                on_pushButton_Login_clicked();

//                on_pushButton_ComfirmT_clicked();
//            } catch (...) {
//                CancelT();
//            }
//        }
    }
}

// ����ر�����
void FtpUpload::closeEvent(QCloseEvent* e)
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

    WriteDefaultPath();
    e->accept();

    m_ftp->close();
    m_ftp->destroyed();
}

// ��¼
void FtpUpload::on_pushButton_Login_clicked()
{
    QString str = ui.pushButton_Login->text();
    if (ui.pushButton_Login->text() == QString::fromLocal8Bit("ע��")) {
        m_ftp->close();
        ui.pushButton_Login->setText(QString::fromLocal8Bit("��¼"));
        ui.treeWidget->clear();
        isDirectory.clear();
        WriteDefaultPath();
        initComponent(false);
    }
    else {
        auto ip       = ui.lineEdit_Host->text();
        auto port     = ui.lineEdit_Port->text();
        auto userName = ui.lineEdit_User->text();
        auto psw      = ui.lineEdit_pad->text();

        myMessageOutput(QString::fromLocal8Bit("��¼ ") + ip +
                        QString::fromLocal8Bit(" ") + port +
                        QString::fromLocal8Bit(" ") + userName +
                        QString::fromLocal8Bit(" ") + psw);

        ui.treeWidget->clear();
        if (!ip.isEmpty() && !port.isEmpty() && !userName.isEmpty() &&
            !psw.isEmpty()) {
            m_ftp->connectToHost(ip, port.toInt());
            m_ftp->login(userName, psw); // ��½������
        }
        else {
            ui.statusLabel->setText(QString::fromLocal8Bit("��������Ϊ��"));
        }
        initComponent(true);
    }
}

// �Զ���¼
void FtpUpload::on_checkBox_AutoLogin_clicked(bool checked)
{
    if (checked == true) {
        on_pushButton_Login_clicked();
    }
}

// �������
void FtpUpload::S_commandFinish(int tmp, bool en)
{
    Q_UNUSED(tmp);

    if (m_ftp->currentCommand() == QFtp::ConnectToHost) {
        if (en) {
            myMessageOutput(QString::fromLocal8Bit("���ӷ��������ִ���"));
            ui.textEdit->append(QString::fromLocal8Bit("���ӷ��������ִ���%1")
                                    .arg(m_ftp->errorString()));
        }
        else {
            myMessageOutput(QString::fromLocal8Bit("���ӵ��������ɹ�"));
            ui.textEdit->append(QString::fromLocal8Bit("���ӵ��������ɹ�"));
        }
    }

    if (m_ftp->currentCommand() == QFtp::Login) {
        if (en) {
            myMessageOutput(QString::fromLocal8Bit("��¼���ִ���"));
            ui.textEdit->append(QString::fromLocal8Bit("��¼���ִ���%1")
                                    .arg(m_ftp->errorString()));
        }
        else {
            myMessageOutput(QString::fromLocal8Bit("��¼�ɹ�"));
            ui.textEdit->append(QString::fromLocal8Bit("��¼�������ɹ�"));
            ui.pushButton_Login->setText(QString::fromLocal8Bit("ע��"));

//            currentPath = Default.m_TargetPath;
            currentPath = "/";
            m_ftp->cd(toSpecialEncoding("/"));

            ui.treeWidget->clear();
            m_ftp->list();
        }
    }

    if (m_ftp->currentCommand() == QFtp::Cd ||
        m_ftp->currentCommand() == QFtp::List) {
        ui.label_currentpath->setText(QString::fromLocal8Bit("  ��ǰ·��: ") +
                                      (currentPath.isEmpty() ?
                                           QString::fromLocal8Bit("��Ŀ¼") :
                                           currentPath));
    }

    if (m_ftp->currentCommand() == QFtp::Get) {
        if (en) {
            ui.textEdit->append(QString::fromLocal8Bit("���س��ִ���%1")
                                    .arg(m_ftp->errorString()));
        }
        else {
            ui.textEdit->append(QString::fromLocal8Bit("�Ѿ��������"));
        }
        refreshed();
    }
    else if (m_ftp->currentCommand() == QFtp::Put) {
        if (en) {
            myMessageOutput(QString::fromLocal8Bit("�ϴ����ִ���%1")
                                .arg(m_ftp->errorString()));
            ui.textEdit->append(QString::fromLocal8Bit("�ϴ����ִ���%1")
                                    .arg(m_ftp->errorString()));
            m_ftp->abort();
        }
        else {
            if (m_loop.isRunning())
                m_loop.exit();
        }
    }
    else if (m_ftp->currentCommand() == QFtp::Close) {
        //        myMessageOutput(QString::fromLocal8Bit("�Ѿ��ر�����"));
        ui.textEdit->append(QString::fromLocal8Bit("�Ѿ��ر�����"));
    }
    else if (m_ftp->currentCommand() == QFtp::Unconnected) {
        //        myMessageOutput(QString::fromLocal8Bit("�Ͽ�����"));
        ui.textEdit->append(QString::fromLocal8Bit("���ӶϿ�"));

    }
    else if (m_ftp->currentCommand() == QFtp::Rename) {
        //        myMessageOutput(QString::fromLocal8Bit("�ļ��������ɹ�"));
        ui.textEdit->append(QString::fromLocal8Bit("�ļ��������ɹ�"));
        refreshed();
    }
    else if (m_ftp->currentCommand() == QFtp::Mkdir) {
        //        myMessageOutput(QString::fromLocal8Bit("�½��ļ��гɹ�"));
        ui.textEdit->append(QString::fromLocal8Bit("�½��ļ��гɹ�"));

        refreshed();
    }
    else if (m_ftp->currentCommand() == QFtp::Remove) {
        //        myMessageOutput(QString::fromLocal8Bit("�ļ�ɾ���ɹ�"));
        ui.textEdit->append(QString::fromLocal8Bit("�ļ�ɾ���ɹ�"));
    }
    else if (m_ftp->currentCommand() == QFtp::Rmdir) {
        //        myMessageOutput(QString::fromLocal8Bit("�ļ���ɾ���ɹ�"));
        ui.textEdit->append(QString::fromLocal8Bit("�ļ���ɾ���ɹ�"));
    }
}

// ��������
void FtpUpload::ftpCommandStarted(int tem)
{
    if (m_ftp->currentCommand() == QFtp::ConnectToHost) {
        //        myMessageOutput(QString::fromLocal8Bit("�������ӵ�������..."));
        ui.textEdit->append(QString::fromLocal8Bit("�������ӵ�������..."));
    }
    if (m_ftp->currentCommand() == QFtp::Login) {
        //        myMessageOutput(QString::fromLocal8Bit("���ڵ�¼..."));
        ui.textEdit->append(QString::fromLocal8Bit("���ڵ�¼..."));
    }
    if (m_ftp->currentCommand() == QFtp::Get) {
        //        myMessageOutput(QString::fromLocal8Bit("��������..."));
//        ui.textEdit->append(QString::fromLocal8Bit("��������..."));
    }
    if (m_ftp->currentCommand() == QFtp::Put) {
        //        myMessageOutput(QString::fromLocal8Bit("�����ϴ�..."));
//        ui.textEdit->append(QString::fromLocal8Bit("�����ϴ�..."));

    }
    else if (m_ftp->currentCommand() == QFtp::Close) {
        //        myMessageOutput(QString::fromLocal8Bit("���ڹر�����..."));
        ui.textEdit->append(QString::fromLocal8Bit("���ڹر�����..."));
    }
}

// ftp ����״̬����
void FtpUpload::ftpStateChanged(int state)
{
    if (state == QFtp::Unconnected) {
        IsLogin = false;
        myMessageOutput(QString::fromLocal8Bit("δ���ӵ�����"));
        ui.textEdit->append(QString::fromLocal8Bit("δ���ӵ�����"));
        ui.pushButton_Login->setText(QString::fromLocal8Bit("��¼"));
        ui.treeWidget->clear();
        initComponent(false);
    }
    if (state == QFtp::Connected) {
        ui.textEdit->append(QString::fromLocal8Bit("�Ѿ����ӵ�����"));
    }
    if (state == QFtp::HostLookup) {
        ui.textEdit->append(QString::fromLocal8Bit("���ڲ�������"));
    }
    if (state == QFtp::LoggedIn) {
        ui.textEdit->append(QString::fromLocal8Bit("�Ѿ���¼"));
        IsLogin = true;
    }
    if (state == QFtp::Closing) {
        ui.textEdit->append(QString::fromLocal8Bit("�������ڹر�"));
        initComponent(false);
    }
}

// ˢ�²ۺ���
void FtpUpload::addToList(const QUrlInfo& urlInfo)
{
    QString
        fileSize; // ���ڴ洢�ļ���С�������ļ���С�ֽڣ������ļ������б�ĵ�λ
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

// ˫������
void FtpUpload::processItem(QTreeWidgetItem* item, int column)
{
    Q_UNUSED(column) // ���δʹ�õı������־��������
    QString name = item->text(0);
    QString str  = toSpecialEncoding(name);

    if (isDirectory.value(str)) {
        ui.treeWidget->clear();
        isDirectory.clear();
        currentPath += QString::fromLocal8Bit("/") + name;
        m_ftp->cd(str);
        m_ftp->list();
        return;
    }
}

// ˢ��
void FtpUpload::on_pushButton_Refush_clicked()
{
    ui.treeWidget->clear();
    m_ftp->list();
}

// ����
void FtpUpload::on_pushButton_Back_clicked()
{
    ui.treeWidget->clear();
    isDirectory.clear();
    QString strLeft = currentPath.left(currentPath.lastIndexOf('/'));
    currentPath     = strLeft;
    if (currentPath.isEmpty()) {
        m_ftp->cd(toSpecialEncoding(QString::fromLocal8Bit("/")));
    }
    else {
        m_ftp->cd(toSpecialEncoding(currentPath));
    }
    m_ftp->list();
}

// �ϴ��ļ�
void FtpUpload::on_uploadButton_clicked()
{
    if (IsLogin == false)
        on_pushButton_Login_clicked();

    auto fileName = ui.lineEdit_FilePath->text();

    QFile file(fileName);
    if (file.exists()) {
        QFile* m_File = new QFile(fileName);
        if (!m_File->isOpen()) {
            QFileInfo fi(fileName);
            QString   filename = fi.fileName();

            uploadStatusEvent(true, true, "�ļ� : ", filename);

            m_ftp->put(m_File, toSpecialEncoding(filename)); // �ϴ�
            refreshed();

            uploadStatusEvent(true, false, "�ļ� : ", filename);
        }
        else {
            ui.textEdit->append(QString::fromLocal8Bit("�ļ���ռ��"));
            QMessageBox::warning(NULL, QString::fromLocal8Bit("�ļ����쳣"),
                                 QString::fromLocal8Bit("�ļ���ռ��"));
            uploadStatusEvent(false, false, "�쳣���ļ���ռ�� : ", fileName);
            m_File->close();
            return;
        }

        m_File->close();
    }
    else {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("�ļ��쳣"),
                             fileName + QString::fromLocal8Bit("�ļ�������"));
        uploadStatusEvent(false, false, "�쳣���ļ������� : ", fileName);
    }
}

// �����ϴ�
void FtpUpload::on_uploadButton_All_clicked()
{
    if (strDirPath != "") {
        ui.lineEdit_DirPath->setText(strDirPath);
    }
    if (strDirPath2 != "") {
        ui.lineEdit_DirPath_2->setText(strDirPath2);
    }

    auto path  = ui.lineEdit_DirPath->text();
    auto path2 = ui.lineEdit_DirPath_2->text();

    Batch_upload(path);
}

// ѡ���ļ�·��
void FtpUpload::on_toolButton_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, QString::fromLocal8Bit("���ļ�..."), ".", "*");
    if (fileName.isNull())
        return;

    if (!QFile::exists(fileName)) {
        return;
    }

    ui.lineEdit_FilePath->setText(fileName);
}

// ѡ���ļ���·��
void FtpUpload::on_toolButton_dir_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this);
    ui.lineEdit_DirPath->setText(path);
}

// ѡ���ļ���2·��
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

// ȷ����ʱ�ϴ�
void FtpUpload::on_pushButton_ComfirmT_clicked()
{
    QString factory = ui.lineEdit_factory->text();
    if (!qstrIsEffective(factory)) {
        QMessageBox::warning(
            this, QString::fromLocal8Bit("����"),
            QString::fromLocal8Bit("<����> ���Ʋ��Ϸ���������ȷ��!"));
        ui.lineEdit_factory->setText(NULL);
        return;
    }

    QString procedure = ui.lineEdit_procedure->text();
    if (!qstrIsEffective(procedure)) {
        QMessageBox::warning(
            this, QString::fromLocal8Bit("����"),
            QString::fromLocal8Bit("<����> ���Ʋ��Ϸ���������ȷ��!"));
        ui.lineEdit_procedure->setText(NULL);
        return;
    }

    QString manufacturer = ui.lineEdit_manufacturer->text();
    if (!qstrIsEffective(manufacturer)) {
        QMessageBox::warning(
            this, QString::fromLocal8Bit("�豸����"),
            QString::fromLocal8Bit("<�豸����> ���Ʋ��Ϸ���������ȷ��!"));
        ui.lineEdit_manufacturer->setText(NULL);
        return;
    }

    QString number = ui.lineEdit_number->text();
    if (!qstrIsEffective(number)) {
        QMessageBox::warning(
            this, QString::fromLocal8Bit("�豸���"),
            QString::fromLocal8Bit("<�豸���> ���Ʋ��Ϸ���������ȷ��!"));
        ui.lineEdit_number->setText(NULL);
        return;
    }

    QString station = ui.lineEdit_station->text();
    if (!qstrIsEffective(station)) {
        QMessageBox::warning(
            this, QString::fromLocal8Bit("��Ӧ��λ"),
            QString::fromLocal8Bit("<��Ӧ��λ> ���Ʋ��Ϸ���������ȷ��!"));
        ui.lineEdit_station->setText(NULL);
        return;
    }

    ConfirmT();

#ifdef bintest
    ScheduledUP(true, 8, 30);
    ScheduledUP(false, 20, 30);
#endif
}

// ȡ����ʱ�ϴ�
void FtpUpload::on_pushButton_CancelT_clicked()
{
    //    myMessageOutput(QString::fromLocal8Bit("ȡ����ʱ�ϴ�"));
    CancelT();
}

// ȡ������
void FtpUpload::on_cancelBtn_clicked()
{
    try {
        m_ftp->abort();
    }
    catch (...) {
        on_pushButton_Login_clicked();
    }

    ui.progressBar->setValue(0);
    ui.progressBar->setVisible(false);
}

// �˳�
void FtpUpload::on_pushButton_Quit_clicked() {}

// ��ʱ������
void FtpUpload::GetTime()
{
    QTime current_time   = QTime::currentTime();
    int   current_hour   = current_time.hour();
    int   current_minute = current_time.minute();
    //    int   current_second = current_time.second();

    int hour_m   = ui.timeEdit->time().hour(); // �ϴ�ҹ��ʱ��
    int minute_m = ui.timeEdit->time().minute();

    int hour_e   = ui.timeEdit_evening->time().hour(); // �ϴ��װ�ʱ��
    int minute_e = ui.timeEdit_evening->time().minute();

    int  hour    = hour_m; // �ϴ�ҹ��
    int  minute  = minute_m;
    bool evening = true;  // �ϴ�ҹ��
    bool upload  = false; // Ĭ�ϲ����ϴ�

    if ((hour_m == (current_hour + 1) && current_minute == 58 + minute_m) ||
        ((current_hour == hour_m) && (minute_m - current_minute) == 5)) {
        initComponent(false);
    }

    if ((hour_e == (current_hour + 1) && current_minute == 58 + minute_e) ||
        ((current_hour == hour_e) && (minute_e - current_minute) == 5)) {
        initComponent(false);
    }


    if ((hour_m == (current_hour + 1) && current_minute == 58 + minute_m) ||
        ((current_hour == hour_m) && (minute_m - current_minute) == 2)) {
        upload = true;
    }

    if ((hour_e == (current_hour + 1) && current_minute == 58 + minute_e) ||
        ((current_hour == hour_e) && (minute_e - current_minute) == 2)) {
        hour    = hour_e;
        minute  = minute_e;
        evening = false;
        upload  = true;
    }

    ui.label_auto->setText(QString::fromLocal8Bit("(���: ") +
                           QString::number(m_upload_num) +
                           QString::fromLocal8Bit(")�Զ���ʱ�ϴ���..."));

    if (upload) {
        if (IsLogin == false) {

            m_timer->stop();
            on_pushButton_Login_clicked();
        }

        ScheduledUP(evening, hour, minute);

        m_upload_num++;
        ui.label_auto->setText(QString::fromLocal8Bit("(���: ") +
                               QString::number(m_upload_num) +
                               QString::fromLocal8Bit(")�Զ���ʱ�ϴ���..."));
        m_timer->start(37000);
        initComponent(false);
    }
}

void FtpUpload::on_radioButtonActive_clicked()
{
    m_ftp->setTransferMode(QFtp::Active);
}

void FtpUpload::on_radioButtonPassive_clicked()
{
    m_ftp->setTransferMode(QFtp::Passive);
}

// ��Ӳ˵�
void FtpUpload::on_treeWidget_customContextMenuRequested(const QPoint)
{
    static int status = 1;
    if (status == 1) {
        popMenu = new QMenu(this); // ����һ���Ҽ������˵�
        cdToParent = popMenu->addAction(QString::fromLocal8Bit("������һ��"));
        upload   = popMenu->addAction(QString::fromLocal8Bit("�ϴ�"));
        download = popMenu->addAction(QString::fromLocal8Bit("����"));
        popMenu->addSeparator(); // ����һ���ָ���
        reName = popMenu->addAction(QString::fromLocal8Bit("������"));
        createFolder = popMenu->addAction(QString::fromLocal8Bit("�½��ļ���"));
        popMenu->addSeparator();
        removeFile = popMenu->addAction(QString::fromLocal8Bit("ɾ���ļ�"));
        removeFolder = popMenu->addAction(QString::fromLocal8Bit("ɾ���ļ���"));
        popMenu->addSeparator();
        refresh = popMenu->addAction(QString::fromLocal8Bit("ˢ��"));
        if (ui.treeWidget->topLevelItemCount() == 0) // ���ڵ�Ϊ��
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

        // ���ò˵����
        popMenu->setStyleSheet(
            "QMenu{background-color: white;}"
            "QMenu::item {background-color: transparent;"
            "padding:6px 30px;}"
            "QMenu::item:selected {background-color: #2dabf9;}");
        popMenu->exec(QCursor::pos()); // �����Ҽ��˵����˵�λ��Ϊ���λ��
        popMenu->clear();
        delete popMenu;
        popMenu = nullptr;
    }
    else {
    }
    status *= -1;
}

// �ļ�������
void FtpUpload::fileRename()
{
    QString oldName = ui.treeWidget->currentItem()->text(0);
    QString str     = toSpecialEncoding(oldName);
    if (isDirectory.value(str)) // ѡ�е����ļ��У��򷵻�
    {
        QMessageBox::information(
            this, QString::fromLocal8Bit("����"),
            QString::fromLocal8Bit(
                "<font size='6' color='#008ed5'>�ļ��в�����������</font>"),
            QMessageBox::Ok);
        return;
    }
    bool    ok;
    QString newName = QInputDialog::getText(
        this, QString::fromLocal8Bit("������"),
        QString::fromLocal8Bit("���ļ�����"), QLineEdit::Normal,
        QString::fromLocal8Bit(""), &ok, Qt::WindowCloseButtonHint);
    if (newName.isEmpty())
        return;
    m_ftp->rename(toSpecialEncoding(oldName), toSpecialEncoding(newName));
}

// �½��ļ���
void FtpUpload::createNewFolder()
{
    bool    ok;
    QString folderName = QInputDialog::getText(
        this, QString::fromLocal8Bit("�½��ļ���"),
        QString::fromLocal8Bit("���ļ�������"), QLineEdit::Normal,
        QString::fromLocal8Bit(""), &ok, Qt::WindowCloseButtonHint);
    if (folderName.isEmpty())
        return;
    m_ftp->mkdir(toSpecialEncoding(folderName));
}

// ɾ���ļ�
void FtpUpload::deleteFile()
{
    QString deleteFile = ui.treeWidget->currentItem()->text(0);
    QString str        = toSpecialEncoding(deleteFile);
    if (isDirectory.value(str)) // ѡ�е����ļ��У��򷵻�
    {
        return;
    }
    QTreeWidgetItem* item = ui.treeWidget->currentItem();
    if (item->childCount() > 0) // ������ӽڵ㣬��ɾ��
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

// ˢ��
void FtpUpload::refreshed()
{
    m_ftp->cd(toSpecialEncoding(currentPath));
    ui.treeWidget->clear();
    m_ftp->list();
}

// ɾ������Ŀ�ڵ�
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

// ɾ���ļ���
void FtpUpload::deleteFolder()
{
    QString folder = ui.treeWidget->currentItem()->text(0);
    QString str    = toSpecialEncoding(folder);
    if (isDirectory.value(str)) {
        m_ftp->rmdir(toSpecialEncoding(folder));

        QTreeWidgetItem* item = ui.treeWidget->currentItem();
        if (item->childCount() > 0) // ������ӽڵ㣬��ɾ��
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
    m_timer->start(37000); // ������ʱ��, 40 ��
    ui.label_auto->setText(QString::fromLocal8Bit("(���: ") +
                           QString::number(m_upload_num) +
                           QString::fromLocal8Bit(")�Զ���ʱ�ϴ���..."));
    initComponent(false);
}

void FtpUpload::CancelT()
{
    m_timer->stop();

    initComponent(true);

    ui.label_auto->setText(QString::fromLocal8Bit(""));
}

// ��ȡ�����ļ�
void FtpUpload::ReadDefaultPath()
{
    QString    path   = GetIniPath();
    QSettings* config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));

    QString retStr1   = config->value(QString("Login/Host")).toString();
    Default.m_HostStr = retStr1;

    Default.m_port = config->value(QString("Login/port")).toInt();

    QString retStr2 = config->value(QString("Login/UserName")).toString();
    Default.UserStr = retStr2;

    QString retStr3     = config->value(QString("Login/PassWord")).toString();
    Default.PasswordStr = retStr3;

    Default.Hour         = config->value(QString("Time/Hour")).toInt();
    Default.Minute       = config->value(QString("Time/Minute")).toInt();
    Default.Hour_Evening = config->value(QString("Time/Hour_Evening")).toInt();
    Default.Minute_Evening =
        config->value(QString("Time/Minute_Evening")).toInt();
    Default.autoUpload   = config->value(QString("Time/autoUpload")).toBool();


    QString retStr4      = config->value(QString("Path/SourcePath")).toString();
    Default.m_SourcePath = retStr4;
    QString retStr5 = config->value(QString("Path/SourcePath2")).toString();
    Default.m_SourcePath2 = retStr5;
    QString retStr6 = config->value(QString("Path/SourcePath3")).toString();
    Default.m_SourcePath3 = retStr6;
    QString retStr7      = config->value(QString("Path/TargetPath")).toString();
    Default.m_TargetPath = retStr7;

    Default.factory = config->value(QString("Login/factory")).toString();
    Default.manufacturer =
        config->value(QString("Login/manufacturer")).toString();
    Default.number    = config->value(QString("Login/number")).toString();
    Default.procedure = config->value(QString("Login/procedure")).toString();
    Default.station   = config->value(QString("Login/station")).toString();

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

// д�������ļ�
void FtpUpload::WriteDefaultPath()
{
    Default.Hour           = ui.timeEdit->time().hour();
    Default.Minute         = ui.timeEdit->time().minute();
    Default.Hour_Evening   = ui.timeEdit_evening->time().hour();
    Default.Minute_Evening = ui.timeEdit_evening->time().minute();

//    QString    path   = "device.ini";
    QString    path   = GetIniPath();
    QSettings* config = new QSettings(path, QSettings::IniFormat);
    config->setIniCodec(QTextCodec::codecForName("UTF-8"));

    config->clear();
    QString retStr1        = ui.lineEdit_Host->text();
    Default.m_HostStr      = retStr1;
    Default.m_port         = ui.lineEdit_Port->text().toInt();
    QString retStr2        = ui.lineEdit_User->text();
    Default.UserStr        = retStr2;
    QString retStr3        = ui.lineEdit_pad->text();
    Default.PasswordStr    = retStr3;
    QString retStr4        = ui.lineEdit_FilePath->text();
    Default.m_SourcePath   = retStr4;
    QString retStr5        = ui.lineEdit_DirPath->text();
    Default.m_SourcePath2  = retStr5;
    QString retStr6        = ui.lineEdit_DirPath_2->text();
    Default.m_SourcePath3  = retStr6;
    QString retStr7        = currentPath;
    Default.m_TargetPath   = retStr7;
    Default.isLoginChecked = ui.checkBox_AutoLogin->isChecked();
    Default.factory        = ui.lineEdit_factory->text();
    Default.manufacturer   = ui.lineEdit_manufacturer->text();
    Default.number         = ui.lineEdit_number->text();
    Default.procedure      = ui.lineEdit_procedure->text();
    Default.station        = ui.lineEdit_station->text();
    Default.initiative     = ui.radioButtonActive->isChecked();
    Default.passive        = ui.radioButtonPassive->isChecked();
    Default.encoding       = ui.CB_EncodingFormat->currentIndex();
    Default.autoUpload     = ui.pushButton_ComfirmT->isEnabled();


    config->beginGroup(QString("Login"));
    config->setValue("Host", Default.m_HostStr);
    config->setValue("port", Default.m_port);
    config->setValue("UserName", Default.UserStr);
    config->setValue("PassWord", Default.PasswordStr);

    config->setValue("factory", Default.factory);
    config->setValue("procedure", Default.procedure);
    config->setValue("manufacturer", Default.manufacturer);
    config->setValue("number", Default.number);
    config->setValue("station", Default.station);
    config->endGroup();

    config->beginGroup(QString("Time"));
    config->setValue("Hour", Default.Hour);
    config->setValue("Minute", Default.Minute);
    config->setValue("Hour_Evening", Default.Hour_Evening);
    config->setValue("Minute_Evening", Default.Minute_Evening);
    config->setValue("autoUpload", Default.autoUpload);
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

// �����ϴ�
void FtpUpload::Batch_upload(QString DirPath)
{
    mutex.lock();

    try {
        if (DirPath == "") {
            mutex.unlock();
            return;
        }

        QDir dir(DirPath);
        if (dir.exists()) {
            ui.progressBar->setVisible(true);
            auto fileLst = dir.entryInfoList(QDir::Files);
            auto end_it  = fileLst.end();
            for (auto it = fileLst.begin(); it != end_it; it++) {
                QFile* file = new QFile(it->filePath(), this);
                if (!file->open(QIODevice::ReadOnly)) {
                    if (m_loop.isRunning())
                        m_loop.exit();
                    continue;
                }
                ui.textEdit->append(QString::fromLocal8Bit("��ǰ�����ϴ�:") +
                                    it->fileName());

                uploadStatusEvent(true, true, "�����ļ� : ", it->fileName());

                m_ftp->put(file, toSpecialEncoding(it->fileName()));

                m_loop.exec();
            }

            ui.progressBar->setValue(0);
            ui.progressBar->setVisible(false);
            ui.textEdit->append(QString::fromLocal8Bit("����������ļ��ϴ�"));
        }
        refreshed();
    }
    catch (...) {
        uploadStatusEvent(false, false, "�쳣�������ļ� : ", m_ftp->errorString());
    }

    uploadStatusEvent(true, false, "�����ļ� : ", DirPath);

    mutex.unlock();
}

void FtpUpload::Batch_upload2(QString DirPath)
{
    mutex.lock();

    if (DirPath == "") {
        mutex.unlock();
        return;
    }

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
                create.toString("yyyy-MM-dd"); // ��ȡ�ļ�����ʱ��
            QDateTime currentTime = QDateTime::currentDateTime();
            QString   currentTimeStr =
                currentTime.toString("yyyy-MM-dd"); // ��ȡ��ǰʱ��
            QString beforeDayTimeStr = currentTime.addDays(-1).toString(
                "yyyy-MM-dd"); // ��ȡǰһ��ʱ��

            if (_createTime == currentTimeStr ||
                _createTime == beforeDayTimeStr) {
                if (!file->open(QIODevice::ReadOnly)) {
                    if (m_loop.isRunning())
                        m_loop.exit();
                    continue;
                }

                ui.textEdit->append(QString::fromLocal8Bit("��ǰ�����ϴ�:") +
                                    it->fileName());
                m_ftp->put(file, toSpecialEncoding(it->fileName()));

                m_loop.exec();
            }
        }
        ui.progressBar->setValue(0);

        ui.textEdit->append(QString::fromLocal8Bit("����������ļ��ϴ�"));
    }
    mutex.unlock();
}

// ��־��¼
void FtpUpload::myMessageOutput(const QString& msg)
{
    // ƴ�������Ϣ
    QString strDateTime =
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString strMessage =
        QString::fromLocal8Bit("%2	%1").arg(msg).arg(strDateTime);

    // д����־���ļ��У���д��׷����ʽ��
    QFile file(GetLogPath());
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

    for (int i = 0; i < fileList.length(); i++) {
        QString strName = fileList[i];
    }
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

// �ϴ��װ� ҹ��
void FtpUpload::ScheduledUP(bool evening, int hour, int minute)
{
    mutex.lock();

    int   i              = 0;
    std::string dirname = "%1��%2�հװ�";
    std::string upload_dirname = "�װ�";
    if (evening) {
        i = -1;

        dirname = "%1��%2��ҹ��";
        upload_dirname =  "ҹ��";
    }

    const QString temp  = ui.lineEdit_DirPath->text();
    QDate         today = QDate::currentDate().addDays(i);
    int           year  = today.year();
    int           month = today.month();
    int           day   = today.day();

    QString name = QString::fromLocal8Bit(dirname.c_str())
                       .arg(QString::number(month))
                       .arg(QString::number(day));
    QString path = QString::fromLocal8Bit("%1/%2").arg(temp).arg(name);

    QDir dir(path);
    if (dir.exists()) {
        uploadStatusEvent(true, true, "��ʱ�ϴ��ļ��� : ", name);

        sleep(1000);

        QString a1 = ui.lineEdit_factory->text();
        QString a2 = ui.lineEdit_procedure->text();
        QString a3 = ui.lineEdit_manufacturer->text();
        QString a4 = ui.lineEdit_number->text();
        QString a5 = QString::number(year);
        QString a6 = QString::number(month);
        QString a7 = QString::number(day);
        QString a8 = QString::fromLocal8Bit(upload_dirname.data());
        QString a9 = ui.lineEdit_station->text();
        try {
            mkdir_cd_update(a1); // ����

            mkdir_cd_update(ui.lineEdit_procedure->text()); // ����

            mkdir_cd_update(ui.lineEdit_manufacturer->text()); // �豸����

            mkdir_cd_update(ui.lineEdit_number->text()); // �豸���

            mkdir_cd_update(QString::fromLocal8Bit("Image")); // Image

            mkdir_cd_update(QString::number(year) + QString::fromLocal8Bit("��")); // ��

            mkdir_cd_update(QString::number(month) +
                            QString::fromLocal8Bit("��")); // ��

            mkdir_cd_update(QString::number(day) + QString::fromLocal8Bit("��")); // ��

            mkdir_cd_update(QString::fromLocal8Bit(upload_dirname.data())); // �װ� ҹ��

            mkdir_cd_update(ui.lineEdit_station->text()); // ��λ

        } catch (...) {
            uploadStatusEvent(false, false,
                              "�쳣���ļ��д���ʧ�� : ", m_ftp->errorString());
        }

        QFile file(GetSciUploadLog());
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::critical(this, "����",
                                  "��ʱ��־��ʧ�ܣ���Ϣû�б��棡", "ȷ��");
            return;
        }

        QTextStream out(&file); // д��
        QString     outstr = NULL;

        QDate   today2 = QDate::currentDate();
        QString date  = QString::fromLocal8Bit("%1-%2:%3")
                .arg(today2.toString("yyyy/MM/dd"))
                .arg(QString::number(hour))
                .arg(QString::number(minute));

        bool    success = false;
        QString content = NULL;

        try {            
            success = true;

            if(!UpFileList(path)) // �����ļ����ڲ�
            {
                uploadStatusEvent(false, false,
                                  "�쳣���ϴ�ʧ��: ", path);
                success = false;
            }

            content = QString::fromLocal8Bit("%1/%2/%3/%4/Image/%5/%6/%7/%8/%9")
                    .arg(a1)
                    .arg(a2)
                    .arg(a3)
                    .arg(a4)
                    .arg(a5)
                    .arg(a6)
                    .arg(a7)
                    .arg(a8)
                    .arg(a9);
        }
        catch (...) {
            content = QString::fromLocal8Bit("NG");
            uploadStatusEvent(false, false, "�쳣����ʱ�ϴ��ļ��� : ", name);
            return;
        }

        outstr = QString::fromLocal8Bit("%1��%2;%3\r\n")
                .arg(success ? QString::fromLocal8Bit("�ɹ�") :
                               QString::fromLocal8Bit("ʧ��"))
                .arg(date)
                .arg(content);
        out << outstr;

#    ifdef bintest
        // �ɹ���2023/03/17-8:30;һ����/��Mylar/1#/2023/3/16/���/�����⹤λ
        // ʧ�ܣ�2023/03/17-8:30;NG
        success = false;
        content = QString::fromLocal8Bit("NG");
        outstr  = QString::fromLocal8Bit("%1��%2;%3\r\n")
                .arg(success ? QString::fromLocal8Bit("�ɹ�") :
                               QString::fromLocal8Bit("ʧ��"))
                .arg(date)
                .arg(content);
        out << outstr;
#    endif

        backUp();
        backUp();
        backUp();
        backUp();
        backUp();
        backUp();
        backUp();
        backUp();
        backUp();
        backUp();

        try {
            if (file.exists()) {
                QFile* m_File = new QFile(GetSciUploadLog());
                if (!m_File->isOpen()) {
                    QFileInfo fi(GetSciUploadLog());
                    QString   filename = fi.fileName();
                    m_ftp->put(m_File, toSpecialEncoding(filename)); // �ϴ�

                    refreshed();

                    uploadStatusEvent(success, false, "��ʱ�ϴ��ļ��� : ", name);

                    m_File->close();
                }
                else
                {
                    uploadStatusEvent(false, false,
                                      "�쳣���ϴ�����ļ���ռ�� : ", file.fileName());
                }
            }
            else
            {
                uploadStatusEvent(false, false,
                                  "�쳣���ϴ�����ļ������� : ", file.fileName());
            }
        }
        catch (...) {
            uploadStatusEvent(false, false,
                              "�쳣���ϴ�����ļ� : ", file.fileName());
            return;
        }
    }
    else
    {
        uploadStatusEvent(false, false,
                          "�쳣���ļ��в�����: ", path);
        ui.textEdit_fail->append(QString::fromLocal8Bit("������: ") + path + QString::fromLocal8Bit("\r\n"));
    }

    ui.label_auto->setText(QString::fromLocal8Bit("(���: ") +
                           QString::number(m_upload_num) +
                           QString::fromLocal8Bit(")��ʱ�ϴ���..."));
    ui.pushButton_ComfirmT->setEnabled(false);
    ui.pushButton_CancelT->setEnabled(true);

    sleep(1000*60*2);

    mutex.unlock();
}

// �ϴ��ļ���
bool FtpUpload::UpFileList(const QString& path)
{
    QDir dir(path);
    if (dir.exists()) {
        auto fileLst = dir.entryInfoList(QDir::Files);
        auto end_it  = fileLst.end();

        QFile* file = nullptr;

        for (auto it = fileLst.begin(); it != end_it; it++) {
            file = new QFile(it->filePath(), this);

            if (!file->open(QIODevice::ReadOnly)) {
                ui.textEdit_fail->append(
                    QString::fromLocal8Bit("��ʧ��: ") + it->fileName() + QString::fromLocal8Bit("\r\n"));
                if (m_loop.isRunning())
                    m_loop.quit();

                continue;
            }

            try {
                int ret = m_ftp->put(file, toSpecialEncoding(it->fileName()));
                qDebug() << "put: " << ret << "\n";
                sleep(200);
            }
            catch (...) {
                myMessageOutput(QString::fromLocal8Bit("�ļ��ϴ�ʧ��: ") +
                                it->fileName() + m_ftp->error());

                ui.textEdit_fail->append(
                    QString::fromLocal8Bit("�ϴ�ʧ��: ") + it->fileName() + QString::fromLocal8Bit("\r\n"));

                uploadStatusEvent(false, false, "�쳣���ϴ��ļ� : ", it->fileName());

                return false;
            }
        }
        if (file != nullptr) {
            file->close();
            delete file;
            file = NULL;
        }

        QFileInfoList dirlist = dir.entryInfoList(QDir::Dirs);

        if (dirlist.count() > 2) {
            auto it_end = dirlist.end();
            for (auto it = dirlist.begin(); it != it_end; it++) {
                QString temp     = it->filePath();
                QString tempname = it->fileName();

                QString pattern("[.]"); // windos �ļ������ƽ�ֹ
                QRegExp rx(pattern);
                if (tempname.indexOf(rx) >= 0) {
                    continue;
                }

                if (it->isDir()) {
                    try {
                        QString s = toSpecialEncoding(tempname);
                        m_ftp->mkdir(toSpecialEncoding(tempname));
                        currentPath += QString::fromLocal8Bit("/") + tempname;
                        m_ftp->cd(toSpecialEncoding(currentPath));
                        sleep(100);
                    }
                    catch (...) {
                        myMessageOutput(
                            QString::fromLocal8Bit("Ŀ¼�쳣���޷�����: ") +
                            tempname + " >" + m_ftp->error());
                        ui.textEdit_fail->append(
                            QString::fromLocal8Bit("�޷�����: ") +
                            toSpecialEncoding(tempname) + QString::fromLocal8Bit("\r\n"));
                        uploadStatusEvent(false, false,
                                          "�쳣���ļ��н���ʧ�� : ", tempname);

                        return false;
                    }

                    if(!UpFileList(temp))
                    {
                        return false;
                    }

                    backUp();
                }
            }
        }

        refreshed();
        return true;
    }
    else
    {
        uploadStatusEvent(false, false, path.toLatin1().data(), "�ļ�������");

        return false;
    }

}

// ������һ��
bool FtpUpload::backUp()
{
    QString strLeft = currentPath.left(currentPath.lastIndexOf('/'));
    currentPath     = strLeft;
    bool isRoot     = false;
    if (currentPath.isEmpty()) {
        m_ftp->cd(toSpecialEncoding("/"));

        isRoot = true;
    }
    else {
        m_ftp->cd(toSpecialEncoding(currentPath));
    }

    m_ftp->list();

    sleep(100);

    return isRoot;
}

// �ϴ��Զ����ļ���
void FtpUpload::UploadCustomDir(const QString& path, const QString& pathname)
{
    if (QDir(path).exists()) {
        m_ftp->mkdir(toSpecialEncoding(pathname));

        if (isDirectory.value(toSpecialEncoding(pathname))) {
            if (true) {
                ui.treeWidget->clear();
                currentPath += QString::fromLocal8Bit("/") + pathname;
                m_ftp->cd(toSpecialEncoding(currentPath));

                ui.treeWidget->clear();
            }
        }

        UpFileList(path);
        backUp();
        ui.treeWidget->clear();
        m_ftp->list();
    }
}

// �ļ����ϴ�������
void FtpUpload::on_downloadButton_clicked()
{
    if (ui.downloadButton->text() == QString::fromLocal8Bit("�ļ����ϴ�")) {
        QString       temp = ui.lineEdit_DirPath_2->text();
        const QString pathname =
            temp.mid(temp.lastIndexOf('/') + 1, temp.length() - 1);

        uploadStatusEvent(true, true, "�ļ��� : ", pathname);

        mkdir_cd_update(pathname);

        try {
            UpFileList(ui.lineEdit_DirPath_2->text());
            backUp();

            refreshed();

            uploadStatusEvent(true, false, "�ļ��� : ", pathname);
        }
        catch (...) {
            uploadStatusEvent(false, false, "�쳣���ļ��� : ", pathname);
        }
    }
}

// �½��������ļ���
void FtpUpload::mkdir_cd_update(const QString& dirname)
{
    qDebug() << "B " << currentPath << " " << dirname << '\n';
    if (currentPath.isEmpty()) {
        m_ftp->cd(toSpecialEncoding(QString::fromLocal8Bit("/")));
    }
    currentPath = (currentPath==QString("/"))?QString(""):currentPath;
    currentPath += QString::fromLocal8Bit("/") + dirname;
    qDebug() << "E " << currentPath << '\n';

    m_ftp->mkdir(toSpecialEncoding(dirname));
    m_ftp->cd(toSpecialEncoding(currentPath));

    sleep(100);
}

// �ϴ�״̬��ʾ
void FtpUpload::uploadStatusEvent(bool           success,
                                  bool           ing,
                                  const char*    prefixnotice,
                                  const QString& content)
{
    initComponent(!ing);

    QString content2;

    content2 = QString::fromLocal8Bit(prefixnotice) + content;
    if (success) {
        if (ing) {
            content2 += QString::fromLocal8Bit(" �ϴ���......");
            ui.textEdit->append(content2);
            ui.progressBar->setVisible(true);
            myMessageOutput(content2);
        }
        else {
            content2 += QString::fromLocal8Bit(" �ϴ��ɹ�!!!");
            ui.textEdit->append(content2);
            ui.progressBar->setVisible(false);
            myMessageOutput(content2);
        }
    }
    else {
        content2 += QString::fromLocal8Bit(" �ϴ�ʧ��!!!");
        ui.textEdit->append(content2);
//        ui.textEdit_fail->append(content2 + QString::fromLocal8Bit("\r\n"));
        ui.progressBar->setVisible(false);
        myMessageOutput(content2);
    }

    ui.statusLabel->setText(content2);

    ui.treeWidget->setFocus();
}

// �ַ����Ϸ�
bool FtpUpload::qstrIsEffective(const QString& str)
{
    int     length = str.length();
    QString temp   = str;
    int length2    = temp.remove(QRegExp("\\s")).length(); // ȥ�����пո�

    if (length2 <= 0) { // Ϊ�� ����
        return false;
    }

    if (length2 == length) {
        QString pattern("[\\\\/:*?\"<>|]"); // windos �ļ������ƽ�ֹ
        QRegExp rx(pattern);
        int     match = str.indexOf(rx);
        if (match >= 0) {
            return false;
        } // �������ļ�ǰ׺
        else {
            return true;
        }
    }
    else { // ���ڿո�
        return false;
    }
}

// ��������ѹ�ƶ�
void FtpUpload::mousePressEvent(QMouseEvent* event)
{
    if ((event->button() == Qt::LeftButton)) {
        mouse_press = true;
        mousePoint  = event->globalPos() - this->pos();
    }
}

// ��������ѹ�ƶ�
void FtpUpload::mouseMoveEvent(QMouseEvent* event)
{
    if (mouse_press) {
        move(event->globalPos() - mousePoint);
    }
}

// �ͷ�ֹͣ�ƶ�
void FtpUpload::mouseReleaseEvent(QMouseEvent* event)
{
    mouse_press = false;
}

#    define AUTO_RUN_KEY                                                       \
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
void FtpUpload::setMyAppAutoRun(bool isStart)
{
    QString application_name = QApplication::applicationName(); // ��ȡӦ������
    QSettings* settings = new QSettings(
        AUTO_RUN_KEY,
        QSettings::NativeFormat); // ����QSetting, ��Ҫ���QSettingͷ�ļ�
    if (isStart) {
        QString application_path =
            QApplication::applicationFilePath(); // �ҵ�Ӧ�õ�Ŀ¼
        settings->setValue(application_name,
                           application_path.replace("/", "\\")); // д��ע���
    }
    else {
        settings->remove(application_name); // ��ע�����ɾ��
    }
}

// �����ʼ��
void FtpUpload::initComponent(bool enable)
{
    ui.CB_EncodingFormat->setEnabled(enable);
    ui.radioButtonActive->setEnabled(enable);
    ui.radioButtonPassive->setEnabled(enable);

    ui.pushButton_Refush->setEnabled(enable);
    ui.pushButton_Back->setEnabled(enable);

    ui.treeWidget->setEnabled(enable);

    ui.toolButton_dir->setEnabled(enable);
    ui.toolButton_dir_2->setEnabled(enable);
    ui.toolButton_file->setEnabled(enable);
    ui.lineEdit_DirPath->setEnabled(enable);
    ui.lineEdit_DirPath_2->setEnabled(enable);
    ui.lineEdit_FilePath->setEnabled(enable);

    ui.uploadButton->setEnabled(enable);
    ui.uploadButton_All->setEnabled(enable);
    ui.downloadButton->setEnabled(enable);

    ui.lineEdit_factory->setEnabled(enable);
    ui.lineEdit_manufacturer->setEnabled(enable);
    ui.lineEdit_number->setEnabled(enable);
    ui.lineEdit_procedure->setEnabled(enable);
    ui.lineEdit_station->setEnabled(enable);

    ui.cancelBtn->setEnabled(!enable);

    ui.timeEdit->setEnabled(enable);
    ui.timeEdit_evening->setEnabled(enable);

    ui.pushButton_ComfirmT->setEnabled(enable);
    ui.pushButton_CancelT->setEnabled(!enable);
}

// ���߳���ͣ
void FtpUpload::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < reachTime) {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void FtpUpload::on_timeEdit_timeChanged(const QTime& time)
{
    timeChanged(QString::fromLocal8Bit("ʱ��ӦС�ڵڶ���ʱ�䣡"), 1);
}

void FtpUpload::on_timeEdit_evening_timeChanged(const QTime& time)
{
    timeChanged(QString::fromLocal8Bit("ʱ��Ӧ���ڵ�һ��ʱ�䣡"), 2);
}

void FtpUpload::timeChanged(const QString& content, int id)
{
    int hour    = ui.timeEdit->time().hour();
    int minute  = ui.timeEdit->time().minute();
    int hour2   = ui.timeEdit_evening->time().hour();
    int minute2 = ui.timeEdit_evening->time().minute();

    bool change = false;

    if ((minute + hour * 60 + 5) > (minute2 + hour2 * 60)) {
        QMessageBox::warning(this, QString::fromLocal8Bit("��ʱ�쳣"), content);
        change = true;
    }

    if (change) {
        if (id == 1) {
            ui.timeEdit->setTime(ui.timeEdit->minimumTime());
        }
        else {
            ui.timeEdit_evening->setTime(ui.timeEdit_evening->maximumTime());
        }
    }
}

/**********************************************  end
 * @author        bin
 * @date          2023-03-02
 ***********************************************/
#endif
