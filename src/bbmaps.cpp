/*
 * bbmaps.cpp
 *
 *  Created on: 17.01.2015
 *      Author: helvete
 */

#include "bbmaps.hpp"
BbMaps::BbMaps(QObject *parent)
    : QObject(parent)
{

}
BbMaps::BbMaps()
{
}
BbMaps::~BbMaps()
{

}
void BbMaps::open(const QVariantMap& data)
{
    if(data["latitude"].value<QString>() != "" && data["longitude"].value<QString>() != "") {
        lmi.setCenterLatitude(data["latitude"].value<double>());
        lmi.setCenterLongitude(data["longitude"].value<double>());
        lmi.setGeocodeLocationEnabled(false);
        lmi.setCurrentLocationEnabled(false);
        lmi.go();
    }
}
