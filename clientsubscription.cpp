/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include "clientsubscription.h"

#include <QtCore/QCoreApplication>
//#include <QtCore/QLoggingCategory>
#ifdef BUG_CONSLE
    Q_LOGGING_CATEGORY(lcWebSocketMqtt, "qtdemo.websocket.mqtt")
#endif
ClientSubscription::ClientSubscription(QObject *parent) : QObject(parent)
{
    state_connect=0;
}

void ClientSubscription::set_url(QString s)
{
    m_url=QUrl(s);
    m_device.setUrl(m_url);
    m_version=3;
    m_device.setProtocol(m_version == 3 ? "mqttv3.1" : "mqtt");
    qDebug()<<m_url;

}

void ClientSubscription::connect_net()
{

    connect(&m_device, &WebSocketIODevice::socketConnected, this, [this]() {
            qDebug() << "WebSocket connected, initializing MQTT connection.";
            m_client.setProtocolVersion(m_version == 3 ? QMqttClient::MQTT_3_1 : QMqttClient::MQTT_3_1_1);
            m_client.setTransport(&m_device, QMqttClient::IODevice);

    connect(&m_client, &QMqttClient::connected, this, [this]()
    {
                qDebug() << "MQTT connection established";
        m_topic="/World";
        m_subscription = m_client.subscribe(m_topic);
        if (!m_subscription) {
            qDebug() << "Failed to subscribe to " << m_topic;
            emit errorOccured();
        }

        connect(m_subscription, &QMqttSubscription::stateChanged,
                [this](QMqttSubscription::SubscriptionState s) { state_connect=s; qDebug() << "Subscription state changed:" << s;});

            connect(m_subscription, &QMqttSubscription::messageReceived,
                [this](QMqttMessage msg) {
            handleMessage(msg.payload());
        });
    });

    m_client.connectToHost();
});
if (!m_device.open(QIODevice::ReadWrite))
    qDebug() << "Could not open socket device";
}

void ClientSubscription::public_topic(QString top,QByteArray barry)
{
    if(state_connect==2)
    {
        m_client.publish(top,barry);
    }
}

bool ClientSubscription::isconnect()
{
    return state_connect;
}
void ClientSubscription::handleMessage(const QByteArray &msgContent)
{
    qDebug()<<"recv"<<msgContent;
    emit messageReceived(msgContent);
}
