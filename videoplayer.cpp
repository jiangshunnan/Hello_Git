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

#include <QAudioDeviceInfo>
#include <QUrl>
#include <QtWidgets>
#include <qvideosurfaceformat.h>
#include <QMediaService>
#include <QAudioOutputSelectorControl>
VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
    , mediaPlayer(0, QMediaPlayer::VideoSurface)
    , playButton(0)
    , positionSlider(0)
{
    videoWidget = new VideoWidget;

       QAudioDeviceInfo infoout=(QAudioDeviceInfo::defaultInputDevice());
    QList<QAudioDeviceInfo> devices=QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach(QAudioDeviceInfo i,devices)
        qDebug()<<"videoplayer.h"<<i.deviceName();
    qDebug()<<"Default deviece is "<<infoout.deviceName();
    #if 0
    QMediaService* svc=mediaPlayer.service();
    if(svc!=nullptr)
    {
        QAudioOutputSelectorControl* out =qobject_cast<QAudioOutputSelectorControl*>(svc->requestControl(QAudioOutputSelectorControl_iid));
         if(out!=nullptr)
        {
                ;
             int jj=2;
             jj=jj<devices.length()?jj:devices.length()-1;
               out->setActiveOutput(devices[jj].deviceName());
                svc->releaseControl(out);
        }
    }

#endif



    QDesktopWidget desktop;
    videoWidget->setMaximumSize(QSize(desktop.width(),desktop.height()*8/10));
    QAbstractButton *openButton = new QPushButton(tr("Open..."));
    connect(openButton, SIGNAL(clicked()), this, SLOT(open_widget()));
    playButton = new QPushButton;
    playButton->setEnabled(false);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, SIGNAL(clicked()),this, SLOT(play()));

    positionSlider = new QSlider(Qt::Horizontal);
    positionSlider->setRange(0, 0);

    connect(positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setPosition(int)));

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addLayout(controlLayout);

    setLayout(layout);

    mediaPlayer.setVideoOutput(videoWidget->videoSurface());
    connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

    mediaPlayer.setVolume(50);
    current_percent=0;
    vol=100;
     this->move(10,30);


}

VideoPlayer::~VideoPlayer()
{
}


void VideoPlayer::setpercent(int percent)
{

    if(percent>0&&percent<100)
    {
        this->current_percent=percent;
        mediaPlayer.setPosition(percent*all_duration);
    }
}

void VideoPlayer::setvol(int t)
{
    this->vol=t;
    mediaPlayer.setVolume(t);
}

void VideoPlayer::seturl(QString s)
{

    if (!s.isEmpty())
    {
              qDebug()<<s;
              mediaPlayer.setMedia(QMediaContent(QUrl(s.trimmed())));
              playButton->setEnabled(true);
    }
}

void VideoPlayer::setlocalfile(QString fileName)
{
    qDebug()<<fileName<<"play";
    if (!fileName.isEmpty()) {
           mediaPlayer.setMedia(QMediaContent(QUrl::fromLocalFile(fileName)));

           playButton->setEnabled(true);
    }
}

unsigned int VideoPlayer::getpercent()
{
    return current_percent;
}

int VideoPlayer::getvol()
{
    return vol;
}

void VideoPlayer::setbuttonstate(bool b)
{
    this->playButton->setEnabled(b);
}




void VideoPlayer::play()
{
    switch(mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();
        break;
    default:
        mediaPlayer.play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    all_duration=duration/100;
    positionSlider->setRange(0, duration);
}

void VideoPlayer::volumeChange(int t)
{
    this->vol=t;
    mediaPlayer.setVolume(t);
}

void VideoPlayer::open_widget()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    qDebug()<<fileName;
     if (!fileName.isEmpty()) {
         mediaPlayer.setMedia(QMediaContent(QUrl::fromLocalFile(fileName)));

         playButton->setEnabled(true);
     }
}

void VideoPlayer::setPosition(int position)
{
    current_percent=position/all_duration;
    mediaPlayer.setPosition(position);
}


