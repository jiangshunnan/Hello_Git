#ifndef WIFICONNECTTEST_H
#define WIFICONNECTTEST_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QNetworkConfigurationManager>
#include <QDesktopWidget>
#include <QLabel>

#include <QtCore/QCommandLineParser>
#include <QtCore/QLoggingCategory>
#include  <QProcess>
#include <QListWidget>
#include <QListWidgetItem>
#include <QElapsedTimer>
#define WIFINUM 10                              //�����ʾ10��wifi

class WifiConnectTest : public QDialog
{
    Q_OBJECT

public:
    WifiConnectTest();
    ~WifiConnectTest();
private slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
	QLabel *iconLabel[WIFINUM];                 //��ʾwifi�ź�ǿ��
	QLabel *connectLabel[WIFINUM];              //��ʾwifi����״̬
	QLabel *wifiNameLabel[WIFINUM];             //wifi��
	QWidget *wifiWidget[WIFINUM];               //����wifi��Ա��widget
	QPushButton *connectButton[WIFINUM];        //wifi���Ӱ�ť
	QVBoxLayout *vLayout;
	QPushButton   ping;
	QPushButton   next;
	QPushButton   prev;
	int max_heith;
	int max_widht;
	// QListWidget*  listwidget;
	QStringList  readlinelist;
	QMap<QString,QString > succeewifilist;
	int current_page;
	QString slectWifiname;
	int slectWificurline;

	void LoadSucceedWIFI();
	bool ConnectWIFI(QString,QString);
	void disconnectWIFI(QString); 
	void check_network();
	int system_qstring(QString);
	void  FileRead();
	void InitWidget();
	void LoadStringList(int page);
	QString ExcuteCMD(QString);
	QString mapiscontainvalue(QString);
	QStringList ParserWifiini(QString);

};

#endif // WIFICONNECTTEST_H
