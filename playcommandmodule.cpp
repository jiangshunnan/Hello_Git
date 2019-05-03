#include "playcommandmodule.h"
#include "nethandleplay.h"
PlayCommandModule::PlayCommandModule(QObject *parent) :
    QObject(parent)
{
    player.show();
}

VideoPlayer *PlayCommandModule::GetVideoPlayer()
{
    return &this->player;
}
