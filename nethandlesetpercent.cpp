#include "nethandlesetpercent.h"

NetHandleSetPercent::NetHandleSetPercent()
{

}

void NetHandleSetPercent::nethandlefunc(QString s)
{
    int k=s.toInt();
    this->player->setpercent(k);
}

void NetHandleSetPercent::SetVideoPlater(VideoPlayer *p)
{
     this->player=p;
}
