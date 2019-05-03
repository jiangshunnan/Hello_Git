#ifndef NETWORKHANDLEMODULES_H
#define NETWORKHANDLEMODULES_H

#include "nethandlebase.h"
#include "nethandleplay.h"
#include <QDebug>
#include <QObject>
#include "clientsubscription.h"
#include <QJsonParseError>
class NetWorkHandleModules : public QObject
{
    Q_OBJECT
public:
    explicit NetWorkHandleModules(QObject *parent = 0);
    void AddFortor(NetHandleBase*);
    void  start_modules();
    ClientSubscription * GetClient();
signals:   
public slots:
private slots:
     void NetWorkHandle(QByteArray s);
     QMap<int,QString> JsonParser(QByteArray);

 private:
     QList<NetHandleBase*>  alllist;
     ClientSubscription *clientsub;
};

#endif // NETWORKHANDLEMODULES_H
