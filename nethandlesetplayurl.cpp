#include "nethandlesetplayurl.h"
#include <QTextCodec>
#define VIDEOPATH  QString("/home/pi/newplay/videofloder/")
NetHandleSetPlayUrl::NetHandleSetPlayUrl()
{

}

void NetHandleSetPlayUrl::nethandlefunc(QString s)
{
    if(s.length()<1)
        return;
        s=ParserNetUrl(s);
        if(s.contains("http"))
         {
             this->player->seturl(s);
         }
         else
        {
                s=VIDEOPATH+s;
                qDebug()<<s<<"WEB  LIST";
                this->player->setlocalfile(s);
        }


}

void NetHandleSetPlayUrl::SetVideoPlater(VideoPlayer *p)
{
    this->player=p;
}

QString NetHandleSetPlayUrl::ParserNetUrl(QString src)
{

    if(src.left(7).contains("thunder"))
    {
        src=src.right(src.length()-10);

      //  QByteArray text = src.toLocal8Bit();
        QByteArray text = src.toUtf8();
        QByteArray by = text.fromBase64(text);
        QString str = QString::fromLocal8Bit(by);
        str=str.right(str.length()-2);
        str=str.left(str.length()-2);
        return str;
    }
    return src;
}
