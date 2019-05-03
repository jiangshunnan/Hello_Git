#ifndef NETHANDLEBASE_H
#define NETHANDLEBASE_H

#include <QObject>
#define  SEVERPUBLIC  "/W"
class NetHandleBase : public QObject
{
    Q_OBJECT
public:
    explicit NetHandleBase(QObject *parent = 0);
    virtual void nethandlefunc(QString)=0;
    void SetNetCommandType(int);
	int  GetNetCommandType();
protected:    
private:
     int type;

    
};

#endif // NETHANDLEBASE_H
