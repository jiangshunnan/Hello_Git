#ifndef NETHANDLESETPERCENT_H
#define NETHANDLESETPERCENT_H
#include "nethandlebase.h"
#include "videoplayer.h"
class NetHandleSetPercent : public NetHandleBase
{
public:
    NetHandleSetPercent();
    void  nethandlefunc(QString);
    void SetVideoPlater(VideoPlayer*);
private:
    VideoPlayer *player;
};

#endif // NETHANDLESETPERCENT_H
