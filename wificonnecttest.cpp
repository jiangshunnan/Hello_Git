#include "wificonnecttest.h"
#include <QRegExp>

#include <QInputDialog>
#include <QMessageBox>
const QString wifiStrList = QString("/home/pi/newplay/Qt5.3player/scan_result.txt");

WifiConnectTest::WifiConnectTest()
    : QDialog()
{

    FileRead();
    LoadSucceedWIFI();
    current_page=1;
    vLayout = new QVBoxLayout(this);
    QDesktopWidget desktop;
    max_heith=desktop.height();
    max_widht=desktop.width();
    this->setFixedSize(desktop.width(),desktop.height());
    InitWidget();
    current_page=1;
    LoadStringList(1);

}

WifiConnectTest::~WifiConnectTest()
{

}

bool WifiConnectTest::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(mouseEvent->type() == QEvent::MouseButtonPress)
    {
        if(mouseEvent->button()==Qt::LeftButton)
        {
            if(obj->objectName().contains("wifiName"))
            {

                QString wifiName = obj->objectName().section('*',-1);
                static int curLine = 0;
                connectButton[curLine]->setVisible(false);                  //隐藏所有wifi连接button
                curLine = obj->objectName().section('*',1,1).toInt();
                slectWificurline=curLine;
                slectWifiname=wifiName;
                connectButton[curLine]->setVisible(true);                   //选中当前wifi属性框后，显示wifi连接按钮
                if(mapiscontainvalue(wifiName)!="")
                {
                     connectButton[curLine]->setText("disconnect");
                }




            return true;
           }
        }
    }
    return QWidget::eventFilter(obj, event);
}

QStringList WifiConnectTest::ParserWifiini(QString s)
{
    QStringList list;
    if(s.length()<1)
        return list;
    QRegExp rx("([^\\s]+)\\s+([^\\s]+)\\s+([^\\s]+)\\s+([^\\s]+)\\s+([^\\s]+)\\s*");
    if (rx.indexIn(s) != -1) {
        list<<rx.cap(1);
        list<<rx.cap(2);
        list<<rx.cap(3);
        list<<rx.cap(4);
        list<<rx.cap(5);
    }
    return list;
}

void WifiConnectTest::FileRead()
{
    QFile file(wifiStrList);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"No such file!";
        return;
    }
    QString line;
    if(file.size()==0)
        return;

    QTextStream in(&file);
    line =  in.readLine();// remove titile
    while((!line.isEmpty()))
    {

       line =  in.readLine();
       if(line=="")
           return;
       readlinelist<<line;
    }
}
void WifiConnectTest::InitWidget()
{
#if 1
    int curLine=0;
    for( curLine=0;curLine<WIFINUM;curLine++)
    {
        wifiWidget[curLine] = new QWidget(this);
        QGridLayout *gridLayout = new QGridLayout();//wifi对应的属性栏
        wifiWidget[curLine]->installEventFilter(this);                          //安装事件过滤器，选中wifi后弹出连接wifi的接口按钮
        wifiWidget[curLine]->setStyleSheet(QString("QWidget::hover{background-color:darkgray}").append(QString("QWidget{background-color:transparent;}")));
        wifiWidget[curLine]->setMaximumSize(max_widht,max_heith/(WIFINUM+13));
        wifiNameLabel[curLine] = new QLabel(wifiWidget[curLine]);
        iconLabel[curLine] = new QLabel(wifiWidget[curLine]);
        connectLabel[curLine] = new QLabel(wifiWidget[curLine]);
        connectButton[curLine] = new QPushButton(wifiWidget[curLine]);
        connectButton[curLine]->setStyleSheet(QString("QPushButton{background-color:lightgray;}").append(QString("QPushButton::pressed{background-color:darkgray;}")));
        connect(connectButton[curLine],&QPushButton::clicked,[this]()
        {
            QString val=mapiscontainvalue(slectWifiname);
            if(val!="")
            {
                disconnectWIFI(val);
                connectLabel[slectWificurline]->setText("");
                connectButton[slectWificurline]->setText("connect");
            }
            else
            {
                 bool isOK;
                QString text = QInputDialog::getText(NULL, "Input Dialog","Please input your comment",QLineEdit::Password,"your comment",&isOK);
                if(isOK)
                {
                    if(ConnectWIFI(slectWifiname,text.trimmed()))
                    {
                        connectButton[slectWificurline]->setText("disconnect");
                        connectLabel[slectWificurline]->setText("connecting");
                        check_network();
                    }
                    else
                        QMessageBox::information(NULL,"TiTle","ERROR",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                }
            }

        });

        gridLayout->addWidget(wifiNameLabel[curLine],0,0,1,3);      //在wifi属性框中添加wifi对应的属性信息
        gridLayout->addWidget(connectLabel[curLine],0,3,1,1);
        gridLayout->addWidget(iconLabel[curLine],0,4,1,1);
        gridLayout->addWidget(connectButton[curLine],1,3,1,1);
        gridLayout->setMargin(0);
        gridLayout->setSpacing(0);
        wifiWidget[curLine]->setLayout(gridLayout);
        vLayout->addWidget(wifiWidget[curLine]);
        vLayout->setMargin(2);
        vLayout->setSpacing(0);
        wifiWidget[curLine]->hide();

    }
    QHBoxLayout* end=new QHBoxLayout();

    ping.setText("null");
    prev.setText("prev");
    next.setText("next");

    connect(&prev,&QPushButton::clicked,[this](){qDebug()<<"prev";LoadStringList(current_page-1);});
    connect(&next,&QPushButton::clicked,[this](){qDebug()<<"next";LoadStringList(current_page+1);});
    end->addWidget(&ping);
    end->addWidget(&prev);
    end->addWidget(&next);
    end->setSpacing(max_widht/5);
    end->setStretch(0,1);
    end->setStretch(1,1);
    end->setStretch(2,1);
    end->setContentsMargins(10,10,10,10);

    vLayout->addLayout(end);
    this->setLayout(vLayout);
#endif
}

void WifiConnectTest::LoadStringList(int page)
{

    int k;
    int curLine;
    int len=readlinelist.length();
    QString wifiName;
    int signalValue;
    QString curConnection="*";
    int max_page=len/WIFINUM+1;
    if(!((page<=max_page)&&(page>0)))//   1 2
        return;
    current_page=page;
    k=(page-1)*WIFINUM;
    for(int i=0;i<WIFINUM;i++)
    {
        wifiWidget[i]->hide();
    }
    for(int i=0;((k+i)<len)&&(i<WIFINUM);i++)
    {
        curLine=i;
        QStringList list=ParserWifiini(readlinelist.at(i+k));
        if(list.length()<1)
            break;
        wifiName=list.at(4);
        signalValue=120+list.at(2).toInt();
         wifiWidget[curLine]->setObjectName(QString("wifiName*%1*%2").arg(QString::number(curLine)).arg(wifiName));
         wifiNameLabel[curLine]->setText(wifiName);
         QPixmap pix = QPixmap(60,40);       //根据wifi信号强度绘制wifi信号
         pix.fill(Qt::transparent);
         QPainter paint(&pix);
         QPen pen = QPen();
         pen.setColor(Qt::darkGreen);
         pen.setWidth(4);
         paint.setPen(pen);
         for(int k=2;k<7;k++){
             if(k == (signalValue/20+3)){
                 QPen penGray = QPen();
                 penGray.setColor(Qt::gray);
                 penGray.setWidth(4);
                 paint.setPen(penGray);
             }
             paint.drawLine(8*k,48-7*k,8*k,35);
         }
         paint.end();
         iconLabel[curLine]->setPixmap(pix); //添加wifi信号强度图标
                 //wifi连接状态，wifi名前如果有"*",表示当前wifi处于连接状态
       connectLabel[curLine]->setText(mapiscontainvalue(wifiName)!=""?"connected":"");


          connectButton[curLine]->setText(tr("Connect"));
          connectButton[curLine]->setVisible(false);
          wifiWidget[curLine]->show();
    }
}

void WifiConnectTest::LoadSucceedWIFI()
{
   // system("wpa_cli -i wlan0 list_network");

        QProcess process;

       process.start("sudo wpa_cli -i wlan0 list_network");
       process.waitForFinished();
       while (process.canReadLine()) {
           QString s= process.readLine().trimmed();
           QRegExp rx("([^\\s]+)\\s+([^\\s]+)\\s+([^\\s]+)\\s+([^\\s]+)\\s*");
           if (rx.indexIn(s) != -1) {
                //qDebug()<<rx.cap(0);
                   if(!rx.cap(4).contains("DISABLED"))
                        succeewifilist.insert(rx.cap(1),rx.cap(2));
                   else if(rx.cap(4).contains("TEMP"))
                        {
                           QString s=QString("sudo wpa_cli -i wlan0 remove_network  %1").arg(rx.cap(1));
                           system_qstring(s);

                       }


             }
       }
     system("sudo wpa_cli -i wlan0 save_config");
    qDebug()<<succeewifilist;

}

bool WifiConnectTest::ConnectWIFI(QString name,QString pass)
{
    qDebug()<<name<<pass;
    QString id;
    QProcess process;
    process.start("sudo wpa_cli -i wlan0 add_network");
    process.waitForFinished();
    while (process.canReadLine()) {
        id=process.readLine().trimmed();
    }
    QString s11=QString("sudo wpa_cli -i wlan0 set_network %1  Key_mgmt=WPA_PSK").arg(id);
    QString s=QString("sudo wpa_cli -i wlan0 set_network %1 ssid \'\"%2\"\'").arg(id).arg(name);
    QString s2=QString("sudo wpa_cli -i wlan0 set_network %1 psk \'\"%2\"\'").arg(id).arg(pass);
    QString s3=QString("sudo wpa_cli -i wlan0 select_network %1").arg(id);
    QString s4=QString("sudo wpa_cli -i wlan0 enable_network %1").arg(id);
     system_qstring(s);

    system_qstring(s11);
    qDebug()<<"PSK#################################3";
    QString  tt="";
    tt=ExcuteCMD(s2);
    qDebug()<<"PSK"<<tt;;
    if(!tt.contains("OK"))
        return false;
    if(!system_qstring(s3))
        return false;
    if(!system_qstring(s4))
        return false;
       system("sudo wpa_cli -i wlan0 save_config");
#if 1
       QProcess process2;
      qDebug()<<s2;
      process2.start("sudo dhclient wlan0");

      while (process2.canReadLine()) {
           qDebug()<< process2.readLine().trimmed();

      }
#else
      system("sudo dhclient wlan0");

#endif
        qDebug()<<"#########################";
        succeewifilist.insert(id,name);
        qDebug()<<succeewifilist<<"CONNECT";


    return true;

}

int WifiConnectTest::system_qstring(QString s)
{

    QByteArray sr = s.toUtf8();
      qDebug()<<s<<"system_qstring";
    char* buf=sr.data();
    qDebug()<<"cchar"<<buf;
    int ret=system(buf);
    int w=WIFEXITED(ret);
    int ec=WEXITSTATUS(ret);
    if((ret!=-1)&&(w!=0)&&(ec==0))
        return true;
    else
        return false;
}

QString WifiConnectTest::ExcuteCMD(QString s)
{

    QByteArray sr = s.toUtf8();
    char* ps=sr.data();
    char  buf[1024]={0,};
   FILE* ptr=popen(ps,"r");
   if(ptr)
   {
       fread(buf,1024,1,ptr);
   }
    pclose(ptr);
    return QString::fromUtf8(buf);


}

QString WifiConnectTest::mapiscontainvalue(QString s)
{

    QMap<QString,QString>::iterator it; //遍历map
        for ( it = succeewifilist.begin(); it != succeewifilist.end(); ++it ) {
                if(s==it.value())
                       return it.key();
            }

        return "";
}

void WifiConnectTest::disconnectWIFI(QString id)
{
    qDebug()<<"DISCONNECT"<<id;
    QString s=QString("sudo wpa_cli -i wlan0 remove_network  %1").arg(id);
    system_qstring(s);
     system("sudo wpa_cli -i wlan0 save_config");
    succeewifilist.remove(id);
    qDebug()<<succeewifilist<<"DIS";
}

void WifiConnectTest::check_network()
{
    QProcess process3;
   process3.start("ping www.baidu.com");

   while (process3.waitForFinished(20)==false) {
       QString s=process3.readAllStandardOutput();
       if(s.contains("TTL"))
       {
           this->close();
       }

   }
}
