#ifndef NETHANDLEREQUESTPERCENT_H
#define NETHANDLEREQUESTPERCENT_H
#include "clientsubscription.h"
#include "nethandlebase.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "videoplayer.h"
#include <QTimer>

class NetHandleRequestPercent : public NetHandleBase
{
public:
    NetHandleRequestPercent();
    void  nethandlefunc(QString);
    void SetSendEngine(ClientSubscription* );
    void SetVideoPlayer(VideoPlayer*);
    void StartMyTimeSync(int );
private:
    QByteArray CreateCurrentPercentJsonMap( int , int );
    ClientSubscription * client;
    VideoPlayer *player;
    QTimer time;
};

#endif // NETHANDLEREQUESTPERCENT_H
