#include "networkhandlemodules.h"
#include <QTextCodec>

#if 0  //C���Ժ���ָ������
#define  COMMAND(NAME)  {NAME,NAME##_command}
typedef void (*PFUNC)(QString);
typedef struct _nethandle
{
    int type;
    PFUNC   handle_func;
}nethandle_func_t;
enum func_type
{
    play_func,
    stop_func,
};
void play_func_command(QString s)
{
    //dosomething
    qDebug()<<"functypeplay"<<s;
}
void stop_func_command(QString s)
{
     //dosomething
    qDebug()<<"functypestop"<<s;
}

nethandle_func_t NetHandleFuncTable[]=
{
    COMMAND(play_func),
    COMMAND(stop_func),
};
int NetHandleManager(int k)
{
    for(int i=0;i<sizeof(NetHandleFuncTable);i++)
    {
        if(k==NetHandleFuncTable[i].type)
        {
            NetHandleFuncTable[i].handle_func(QString::number(k));
            break;
        }
    }
}

#endif

NetWorkHandleModules::NetWorkHandleModules(QObject *parent) :
    QObject(parent)
{

    clientsub=new ClientSubscription();
    clientsub->set_url("ws://106.12.130.179:8083/mqtt");
    connect(clientsub,&ClientSubscription::messageReceived,this,&NetWorkHandleModules::NetWorkHandle);

}

void NetWorkHandleModules::AddFortor(NetHandleBase *b)
{
    this->alllist<<b;
}
void NetWorkHandleModules::start_modules()
{
    //NetHandleManager(1);
    //��ʼ��mqttģ��  ���Ļص����Ӹ���Ĳ� NetWorKHandke "ws://106.12.130.179:8083/mqtt"
    qDebug()<<"start";
    clientsub->connect_net();
}

ClientSubscription * NetWorkHandleModules::GetClient()
{
    return this->clientsub;
}

void NetWorkHandleModules::NetWorkHandle(QByteArray byy)
{
    //Jsons���ݽ��
    QMap<int,QString> m_map;
    QTextCodec *tc=QTextCodec::codecForName("UTF-8");
    QString src=tc->toUnicode(byy);
    m_map=JsonParser(byy);
    if(m_map.isEmpty())
        return;
    QMap<int, QString>::iterator iter = m_map.begin();
    qDebug()<<"plist lenrgth"<<alllist.length();
    while (iter != m_map.end())
    {
      qDebug() << "Iterator " << iter.key() << ":" << iter.value(); // ������
      for(int i=0;i<alllist.length();i++)
      {
         qDebug()<<"plistat"<<alllist.at(i)->GetNetCommandType();
          if(alllist.at(i)->GetNetCommandType()==iter.key())
          {
              qDebug()<<"NETMODULES    "<<i;
              alllist.at(i)->nethandlefunc(iter.value());
              break;
           }
      }
      iter++;
    }



    //�����������Ӽ��� �ҵ�����ķ���  ���������ɲ��ſ���ģ���������ӵ���������   �������Ӳ����������������ģ��ķ���


}

QMap<int, QString> NetWorkHandleModules::JsonParser(QByteArray data)
{
    QMap<int,QString>  map;
    int key;
    QString dest;

    QJsonParseError jsonError;//Qt5����
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);//Qt5����
    qDebug()<<"ERRROR "<<jsonError.error ;
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject rootObj = json.object();
            if (rootObj.contains("key"))
            {
                QJsonValue value = rootObj.value("key");
                if (value.isDouble())
                {
                    qDebug()<<"Json parser key "<<value;
                    key=value.toInt();
                }
            }
            if (rootObj.contains("value"))
            {
                QJsonValue value = rootObj.value("value");
                if (value.isString())
                {

                    qDebug()<<"json parm valuse"<<value;
                    dest=value.toString();
                }
            }
        }

    }
    map.insert(key,dest);
    return map;
}
