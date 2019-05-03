#ifndef NETHANDLEREQUESTVIDEOLIST_H
#define NETHANDLEREQUESTVIDEOLIST_H
#define VIDEOPATH  QString("/home/pi/newplay/videofloder/")
#include "nethandlebase.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>
#include "clientsubscription.h"
class NetHandleRequestVideoList : public NetHandleBase
{
public:
    NetHandleRequestVideoList();
    void  nethandlefunc(QString);
    void SetSendEngine(ClientSubscription* );
private:
    QByteArray CreateJsonArray(QStringList);
    ClientSubscription * client;
};

#endif // NETHANDLEREQUESTVIDEOLIST_H
