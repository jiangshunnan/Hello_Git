#ifndef PLAYCOMMANDMODULE_H
#define PLAYCOMMANDMODULE_H
#include "nethandlebase.h"
#include <QObject>
#include "videoplayer.h"
class PlayCommandModule : public QObject
{
    Q_OBJECT
public:
    explicit PlayCommandModule(QObject *parent = 0);
    VideoPlayer*  GetVideoPlayer();
signals:
    
public slots:
private:
      VideoPlayer player;
};

#endif // PLAYCOMMANDMODULE_H
