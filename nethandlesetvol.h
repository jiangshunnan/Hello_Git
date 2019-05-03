#ifndef NETHANDLESETVOL_H
#define NETHANDLESETVOL_H

#include "nethandlebase.h"
#include "videoplayer.h"
class NetHandleSetvol : public NetHandleBase
{
public:
    NetHandleSetvol();
    void  nethandlefunc(QString);
    void SetVideoPlater(VideoPlayer*);
private:
    VideoPlayer *player;
};

#endif // NETHANDLESETVOL_H
