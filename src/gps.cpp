/*
 * gps.cpp
 *
 *  Created on: 15.12.2014
 *      Author: helvete
 */

#include "gps.hpp"

Gps::Gps(QObject *parent, SystemPrompt *prompt, ActionItem *aItem, Container *lod)
    : QObject(parent), latitude(0), longitude(0), parentPrompt(prompt)
{
    geoInfo = QGeoPositionInfoSource::createDefaultSource(this);
    if(!connect(geoInfo,
            SIGNAL(positionUpdated(const QGeoPositionInfo &)),
            this,
            SLOT(positionUpdated(const QGeoPositionInfo &))))
    {
        qDebug() << "Error: Konnte position nicht connecten";
    }
    if(!connect(geoInfo,
            SIGNAL(updateTimeout()),
            this,
            SLOT(positionUpdateTimeout())))
    {
        qDebug() << "Error: Konnte timeout nicht connecten";
    }
    ai = aItem;
    loader = lod;

}
Gps::~Gps()
{
    //delete parentPrompt;
}
void Gps::getPosition()
{
    qDebug() << "In der Funktion";
    geoInfo->requestUpdate(30000);

}

qreal Gps::getLatitude()
{
    return latitude;
}
qreal Gps::getLongitude()
{
    return longitude;
}
void Gps::positionUpdated(const QGeoPositionInfo& posInfo)
{
    qDebug() << "Geht in positionUpdated";
    if(posInfo.isValid()) {
        QGeoCoordinate geoCoordinate = posInfo.coordinate();
        latitude = geoCoordinate.latitude();
        longitude = geoCoordinate.longitude();
        //qDebug() << "test1: "<< QString::number(latitude) << "test: " << QString::number(longitude) << QDate::currentDate();
        parentPrompt->setBody("Latitude: " + QString::number(latitude) + " Longitude: " + QString::number(longitude));
        parentPrompt->show();
    }
}
void Gps::positionUpdateTimeout()
{
    qDebug() << "Timeout";
    SystemToast *toast = new SystemToast();
    toast->setBody("GPS Error - Please check the app permissions");
    toast->setPosition(SystemUiPosition::MiddleCenter);
    toast->show();
    ai->setEnabled(true);
    loader->setVisible(false);
}
