/*
 * bbmaps.hpp
 *
 *  Created on: 17.01.2015
 *      Author: helvete
 */

#ifndef BBMAPS_HPP_
#define BBMAPS_HPP_

#include <QObject>
#include <QByteArray>
#include <bb/platform/LocationMapInvoker>

using namespace bb::platform;

class BbMaps : public QObject
{
    Q_OBJECT
public:
    BbMaps(QObject *parent=0);
    BbMaps();
    virtual ~BbMaps();
    void open(const QVariantMap&);
private:
    LocationMapInvoker lmi;

};



#endif /* BBMAPS_HPP_ */
