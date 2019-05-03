#include "nethandlerequestvideolist.h"

NetHandleRequestVideoList::NetHandleRequestVideoList()
{

}

void NetHandleRequestVideoList::nethandlefunc(QString s)
{
    if(s!="videolist")
        return;
    QDir dir(VIDEOPATH);
    QStringList nameFilters;
   nameFilters << "*.mp4";
   QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    QByteArray byar=CreateJsonArray(files);
    qDebug()<<"byar"<<"QQQQQQQQQQQQQQ"<<byar<<"dfdg"<<files;
    if(byar.length())
        this->client->public_topic(SEVERPUBLIC,byar);
}

void NetHandleRequestVideoList::SetSendEngine(ClientSubscription *c)
{
    this->client=c;
}

QByteArray NetHandleRequestVideoList::CreateJsonArray(QStringList list)
{
     QJsonArray json;
     QByteArray by;
     int len=list.length();
     if(len>0)
      {
          for(int i=0;i<len;i++)
              json.append(list.at(i));
           QJsonDocument document;
           document.setArray(json);
           by=document.toJson(QJsonDocument::Compact);
    }
     return by;
}
