#ifndef NETHANDLESETPLAYURL_H
#define NETHANDLESETPLAYURL_H

#include "nethandlebase.h"
#include "videoplayer.h"
class NetHandleSetPlayUrl : public NetHandleBase
{
public:
    NetHandleSetPlayUrl();
    void  nethandlefunc(QString);
    void SetVideoPlater(VideoPlayer*);
private:
    VideoPlayer *player;
    QString ParserNetUrl(QString);
};

#endif // NETHANDLESETPLAYURL_H
