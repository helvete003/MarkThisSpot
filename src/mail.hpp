/*
 * mail.hpp
 *
 *  Created on: 16.12.2014
 *      Author: helvete
 */

#ifndef MAIL_HPP_
#define MAIL_HPP_

#include <QObject>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <QByteArray>
#include "abstractAI.hpp"


using namespace bb::system;

class Mail : public Ai
{
    Q_OBJECT
public:
    //Mail(QObject *parent=0);
    Mail();
    virtual ~Mail();
    /*void sendGmap(const QVariantMap&);
    void sendBing(const QVariantMap&);
    void sendOpenMap(const QVariantMap&);
    void sendHereMap(const QVariantMap&);*/
    void openGmap(const QVariantMap&);
    void openBing(const QVariantMap&);
    void openOpenMap(const QVariantMap&);
    void openHereMap(const QVariantMap&);
private:
    InvokeRequest invReq;

};


#endif /* MAIL_HPP_ */
