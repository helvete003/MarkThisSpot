/*
 * map.hpp
 *
 *  Created on: 16.01.2015
 *      Author: helvete
 */

#ifndef BROWSER_HPP_
#define BROWSER_HPP_

#include <QObject>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <QByteArray>
#include "abstractAI.hpp"


using namespace bb::system;

class Browser : public Ai
{
    Q_OBJECT
public:
    /*Browser(QObject *parent=0);*/
    Browser();
    virtual ~Browser();
    void openGmap(const QVariantMap&);
    void openBing(const QVariantMap&);
    void openOpenMap(const QVariantMap&);
    void openHereMap(const QVariantMap&);
private:
    InvokeRequest invReq;

};




#endif /* MAP_HPP_ */
