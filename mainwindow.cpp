#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"MeowHttpd/MeowHttpd_nossl_nolocal.h"
#include <QtCore>
#include <QImage>
#include<QDebug>
#include<QMap>
#include <QtGlobal>
#include<QFile>
#include <QCloseEvent>
#include<QUrl>
#include<QDir>
#include<QMessageBox>
#include<QNetworkInterface>

int docn=0;
QString UserAgent="MeowClient-1.1";
MeowHttpd::TcpServerManage meowserver(2);
QMap<QString,int> code;
QMap<int, QString> exam;
QMap<QString, QString> users;//用户列表
QMap<QString, QString> ips;//ip用户列表
QMap<QString, QString> files;//已经提交文件的用户列表及文件存储位置
QFile *file = new QFile();
QString rnd;//随机题目


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server();
    connect(ui->action_16,SIGNAL(triggered()),this,SLOT(clsoe()));
    code["/login"]=0;
    code["/stu"]=1;
    code["/put"]=2;
    exam[0] = "Unit17 L1 A+C (P20)";
    exam[1] = "Unit17 L1 B+c(P20)";
    exam[2] = "Unit17 L3 TextA 1-3段(P24)";
    exam[3] = "Unit17 L3 TextB 1-3段(P24)";
    exam[4] = "Unit17 L3 TextB 2-4段(P24)";
    exam[5] = "Unit18 L1 1-3段（P34）";
    exam[6] = "Unit18 L1 2-4段（P34）";
    exam[7] = "Unit18 L1 3-6段（P34）";
	QDir *a= new QDir;
	if (!a->exists("./received/")) {
		a->mkdir("./received/");
	}
	delete a;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::server(){
    meowserver.setHttpAcceptedCallback([this]( const QPointer< MeowHttpd::Session > &session ){
        qDebug()<<session->socket()->peerAddress();
        if(session->requestHeader()["User-Agent"]!=UserAgent){
            session->replyText("Forbidden",200);
            inrest(session->socket()->peerAddress().toString()+"以错误的用户标识符连接");
        }else if(!code.contains(session->requestUrlPath())){
            inrest(session->socket()->peerAddress().toString()+"访问不存在的页面");
            session->replyText("Page Not Found"+session->requestUrlPath(),200);
        }else{
            switch (code[session->requestUrlPath()]) {
            case 0:
                inrest(session->socket()->peerAddress().toString()+"登录喵网络");
                session->replyText("done\r\nss");
                break;
            case 1:
				if (files.contains(session->requestPost()["UID"])) {
					session->replyText("您已经提交文件，拒绝登录");
					return;
				}
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//随机码
                inrest(session->socket()->peerAddress().toString()+session->requestPost()["NAME"]+"登录");//输出帮助
				qDebug() << session->requestPost();//解析post
				ips[session->socket()->peerAddress().toString()] = session->requestPost()["UID"];
				rnd = exam[qrand() % exam.count()];
				users[session->requestPost()["UID"]] = session->requestPost()["NAME"] + "@" + rnd;//记录题目和姓名
                session->replyText(QString("done\r\n欢迎你:%1你有十分钟时间完成录制。你有3次机会。每次机会拥有15秒试音时间。<br>考试前请务必试音\r\n%2").arg(session->requestPost()["NAME"], rnd));//返回题目和姓名
				break;
            case 2:
                inrest(session->socket()->peerAddress().toString()+"提交了文件");
				if (!users.contains(ips[session->socket()->peerAddress().toString()])) {
					session->replyText("您没有在系统中注册，请联络管理员");
					inrest(session->socket()->peerAddress().toString() + "没有注册就提交文件");
					return;
				}
                file->setFileName("./received/"+ips[session->socket()->peerAddress().toString()]+"@"+users[ips[session->socket()->peerAddress().toString()]]+".wav");
				file->open(QFile::WriteOnly);
				file->write(session->requestPost()["DATA"]);
				file->close();
				files[ips[session->socket()->peerAddress().toString()]] = "./received/" + users[ips[session->socket()->peerAddress().toString()]]+"@"+ips[session->socket()->peerAddress().toString()]+".wav";//姓名+考题+UID号
                session->replyText("done");
                break;
            }
        }
        //session->replyText( QString( "url:%1\nbody:%2\n" ).arg( session->requestUrl(),  QString(session->requestBody()) )  );
    });
    if(meowserver.listen( QHostAddress("localhost"), 23412 )){
         inrest("喵网络服务已经正常启动，监听"+getHostIpAddress()+":23412");
    }else{
        inrest("喵网络服务启动失败！");
        QMessageBox::warning(this,"错误","喵网络服务启动失败！");
    }
}

void MainWindow::inrest(QString what){
    QListWidgetItem* lst = new QListWidgetItem(what, MainWindow::ui->listWidget);
    MainWindow::ui->listWidget->insertItem(docn,lst);
    docn+=1;
}
void MainWindow::closeEvent(QCloseEvent *event){
   clsoe();
}
void MainWindow::clsoe(){
    exit(0);
}

QString MainWindow::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
               break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}
