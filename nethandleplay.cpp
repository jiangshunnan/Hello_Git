#include "nethandleplay.h"
#include <QDebug>
NetHandlePlay::NetHandlePlay()
{


}

void NetHandlePlay::nethandlefunc(QString s)
{
    if(s=="play")
    {
        this->player->setbuttonstate(true);
        this->player->play();
    }
}
void NetHandlePlay::SetVideoPlayer(VideoPlayer *p)
{
    this->player=p;
}

