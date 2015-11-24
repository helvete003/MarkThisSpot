/*
 * gps.hpp
 *
 *  Created on: 15.12.2014
 *      Author: helvete
 */

#ifndef GPS_HPP_
#define GPS_HPP_

#include <QObject>
#include <QtLocationSubset/QGeoPositionInfo>
#include <QtLocationSubset/QGeoPositionInfoSource>
#include <QtLocationSubset/QGeoSatelliteInfo>
#include <QtLocationSubset/QGeoSatelliteInfoSource>
#include <bb/cascades/maps/MapView>
//Systemprompt
#include <bb/system/SystemPrompt>
#include <bb/system/SystemToast>
#include <bb/system/SystemUiPosition>
#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>


using namespace bb::cascades;
using namespace QtMobilitySubset;
using namespace bb::cascades::maps;
using namespace bb::platform::geo;
using namespace bb::system;

class Gps : public QObject {
    Q_OBJECT
public:
    Gps(QObject *parent=0, SystemPrompt *prompt=0, ActionItem *aItem=0,Container *lod=0);
    ~Gps();
    void getPosition();
    qreal getLatitude();
    qreal getLongitude();
public slots:
    void positionUpdated(const QGeoPositionInfo &);
    void positionUpdateTimeout();
private:
    qreal latitude;
    qreal longitude;
    SystemPrompt *parentPrompt;
    QGeoPositionInfoSource *geoInfo;
    ActionItem *ai;
    Container *loader;
};


#endif /* GPS_HPP_ */
