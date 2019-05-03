#include "nethandlesetvol.h"

NetHandleSetvol::NetHandleSetvol()
{

}

void NetHandleSetvol::nethandlefunc(QString s)
{
    int k=s.toInt();
    this->player->setvol(k);
}

void NetHandleSetvol::SetVideoPlater(VideoPlayer *p)
{
    this->player=p;
}
