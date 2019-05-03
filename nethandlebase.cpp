#include "nethandlebase.h"

NetHandleBase::NetHandleBase(QObject *parent) :
    QObject(parent)
{
}

void NetHandleBase::SetNetCommandType(int t)
{
    this->type=t;
}

int NetHandleBase::GetNetCommandType()
{
    return this->type;
}
