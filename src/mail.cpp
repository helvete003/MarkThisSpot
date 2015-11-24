/*
 * mail.cpp
 *
 *  Created on: 16.12.2014
 *      Author: helvete
 */

#include "mail.hpp"

Mail::Mail()
{
    invReq.setTarget("sys.pim.uib.email.hybridcomposer");
    invReq.setAction("bb.action.SHARE");
    invReq.setMimeType("text/plain");
}
Mail::~Mail()
{

}

void Mail::openGmap(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "http://maps.google.com?q="+data["latitude"].value<QString>()+","+data["longitude"].value<QString>();
        QString noteText = data["note"].value<QString>() + "\n\n" + gMapString;
        QByteArray sendData;
        sendData.append(noteText);
        qDebug() << sendData;
        invReq.setData(sendData);
        invManager.invoke(invReq);
    }
}
void Mail::openBing(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "http://www.bing.com/maps/?cp="+data["latitude"].value<QString>()+"~"+data["longitude"].value<QString>()+"&lvl=16&sty=r";
        QString noteText = data["note"].value<QString>() + "\n\n" + gMapString;
        QByteArray sendData;
        sendData.append(noteText);
        qDebug() << sendData;
        invReq.setData(sendData);
        invManager.invoke(invReq);
    }
}
void Mail::openOpenMap(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "http://www.openstreetmap.org/#map=16/"+data["latitude"].value<QString>()+"/"+data["longitude"].value<QString>()+"&layers=standard";
        QString noteText = data["note"].value<QString>() + "\n\n" + gMapString;
        QByteArray sendData;
        sendData.append(noteText);
        qDebug() << sendData;
        invReq.setData(sendData);
        invManager.invoke(invReq);
    }
}
void Mail::openHereMap(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "https://www.here.com/?map="+data["latitude"].value<QString>()+","+data["longitude"].value<QString>()+",17";
        QString noteText = data["note"].value<QString>() + "\n\n" + gMapString;
        QByteArray sendData;
        sendData.append(noteText);
        qDebug() << sendData;
        invReq.setData(sendData);
        invManager.invoke(invReq);
    }
}
