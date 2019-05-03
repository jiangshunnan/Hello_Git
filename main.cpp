/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "videoplayer.h"
#include "mainwidget.h"
#include "wificonnecttest.h"
#include "networkhandlemodules.h"
#include "playcommandmodule.h"
#include "nethandleplay.h"
#include "nethandlesetpercent.h"
#include "nethandlesetplayurl.h"
#include "nethandlesetvol.h"
#include "nethandlerequestvideolist.h"
#include "nethandlerequestpercent.h"
#include <QTextCodec>
#include <QElapsedTimer>
enum NetWorkCommandType
{
    set_play_state,
    reqest_video_list,
    set_play_vol,
    set_play_percent,
    set_play_url,
};
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationVersion("1.0");
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if  1
    system("sudo wpa_cli -i wlan0 scan");
     system("sudo wpa_cli -i wlan0 scan_results >/home/pi/newplay/Qt5.3player/scan_result.txt");
      //system("sudo wpa_cli -i wlan0 scan_results >/home/pi/newplay/Qt5.3player/scan_result.txt");
#endif
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<500);
#if 1
	WifiConnectTest wifidialog;
	wifidialog.exec();

    PlayCommandModule* playcommandmodule=new PlayCommandModule();
    NetWorkHandleModules* netmodules=new NetWorkHandleModules();

    NetHandlePlay*  nethandleplay=new NetHandlePlay();
    nethandleplay->SetVideoPlayer(playcommandmodule->GetVideoPlayer());
    nethandleplay->SetNetCommandType((int)set_play_state);

    NetHandleSetPlayUrl*  nethandleurl=new NetHandleSetPlayUrl();
    nethandleurl->SetVideoPlater(playcommandmodule->GetVideoPlayer());
    nethandleurl->SetNetCommandType((int)set_play_url);


    NetHandleSetPercent*  nethandlepercent=new NetHandleSetPercent();
    nethandlepercent->SetVideoPlater(playcommandmodule->GetVideoPlayer());
    nethandlepercent->SetNetCommandType((int)set_play_percent);

    NetHandleSetvol*  nethandlevol=new  NetHandleSetvol;
    nethandlevol->SetVideoPlater(playcommandmodule->GetVideoPlayer());
    nethandlevol->SetNetCommandType((int)set_play_vol);

    NetHandleRequestVideoList*   nethandlevediolist =new  NetHandleRequestVideoList();
    nethandlevediolist->SetNetCommandType((int)reqest_video_list);
    nethandlevediolist->SetSendEngine(netmodules->GetClient());


    NetHandleRequestPercent*   nethandlerequestpercent =new   NetHandleRequestPercent();
   nethandlerequestpercent->SetSendEngine(netmodules->GetClient());
   nethandlerequestpercent->SetVideoPlayer(playcommandmodule->GetVideoPlayer());

    netmodules->AddFortor(nethandleplay);
    netmodules->AddFortor(nethandlevol);
    netmodules->AddFortor(nethandlepercent);
    netmodules->AddFortor(nethandlevediolist);
    netmodules->AddFortor(nethandleurl);
    netmodules->start_modules();

    nethandlerequestpercent->StartMyTimeSync(2000);


#endif

    return app.exec();
}
