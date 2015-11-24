/*
 * map.cpp
 *
 *  Created on: 16.01.2015
 *      Author: helvete
 */

#include "browser.hpp"

Browser::Browser()
{
    invReq.setTarget("sys.browser");
    invReq.setAction("bb.action.OPEN");
    invReq.setMimeType("text/html");
}
Browser::~Browser()
{

}
void Browser::openGmap(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "http://maps.google.com?q="+data["latitude"].value<QString>()+","+data["longitude"].value<QString>();
        qDebug() << gMapString;
        invReq.setUri(gMapString);
        invManager.invoke(invReq);
    }
}
void Browser::openBing(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "http://www.bing.com/maps/?cp="+data["latitude"].value<QString>()+"~"+data["longitude"].value<QString>()+"&lvl=16&sty=r";
        qDebug() << gMapString;
        invReq.setUri(gMapString);
        invManager.invoke(invReq);
    }
}
void Browser::openOpenMap(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "http://www.openstreetmap.org/#map=16/"+data["latitude"].value<QString>()+"/"+data["longitude"].value<QString>()+"&layers=standard";
        qDebug() << gMapString;
        invReq.setUri(gMapString);
        invManager.invoke(invReq);
    }
}
void Browser::openHereMap(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        InvokeManager invManager;
        QString gMapString = "https://www.here.com/?map="+data["latitude"].value<QString>()+","+data["longitude"].value<QString>()+",17";
        qDebug() << gMapString;
        invReq.setUri(gMapString);
        invManager.invoke(invReq);
    }
}
