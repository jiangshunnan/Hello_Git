#include "nethandlerequestpercent.h"

NetHandleRequestPercent::NetHandleRequestPercent()
{

}

void NetHandleRequestPercent::nethandlefunc(QString)
{

}

void NetHandleRequestPercent::SetSendEngine(ClientSubscription *c)
{
    this->client=c;
}

void NetHandleRequestPercent::SetVideoPlayer(VideoPlayer *p)
{
    this->player=p;
}

void NetHandleRequestPercent::StartMyTimeSync(int x)
{

    connect(&this->time,&QTimer::timeout,[this]()
    {

        int curpercent=this->player->getpercent();
        int vol=this->player->getvol();
        QByteArray by=CreateCurrentPercentJsonMap(curpercent,vol);
        if(by.length())
         {
            qDebug()<<"timeout"<<by;
            this->client->public_topic(SEVERPUBLIC,by);
        }
    }

            );
    time.start(x);
}

QByteArray NetHandleRequestPercent::CreateCurrentPercentJsonMap( int c,int vol)
{
    // 构建 JSON 对象
    QJsonObject json;
    json.insert("currentpercent",c);
    json.insert("currentvol",vol);
    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    return document.toJson(QJsonDocument::Compact);
}
