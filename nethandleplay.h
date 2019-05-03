#ifndef NETHANDLEPLAY_H
#define NETHANDLEPLAY_H
#include "nethandlebase.h"
#include "videoplayer.h"
class NetHandlePlay : public NetHandleBase
{
public:
    NetHandlePlay();
    void  nethandlefunc(QString);
    void SetVideoPlayer(VideoPlayer*);
private:
    VideoPlayer *player;
};

#endif // NETHANDLEPLAY_H
