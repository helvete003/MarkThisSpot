/*
 * abstractAI.hpp
 *
 *  Created on: 16.01.2015
 *      Author: helvete
 */

#ifndef ABSTRACTAI_HPP_
#define ABSTRACTAI_HPP_

#include <QObject>

using namespace bb::system;

//Auch wenn es eine abstrakte klasse ist, muss es von QObjects erben
class Ai : public QObject {
public:
    virtual ~Ai() {}
    virtual void openGmap(const QVariantMap&)=0;
    virtual void openBing(const QVariantMap&)=0;
    virtual void openOpenMap(const QVariantMap&)=0;
    virtual void openHereMap(const QVariantMap&)=0;
};



#endif /* ABSTRACTAI_HPP_ */
