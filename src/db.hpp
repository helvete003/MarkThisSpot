/*
 * db.hpp
 *
 *  Created on: 15.12.2014
 *      Author: helvete
 */

#ifndef DB_HPP_
#define DB_HPP_

#include <QObject>
#include <QVariant>
#include <bb/data/DataSource>
#include <bb/data/SqlDataAccess>
#include <bb/system/SystemToast>
#include <bb/system/SystemUiPosition>


using namespace bb::data;
using namespace bb::system;

class Db : public QObject
{
    Q_OBJECT
private:
    QString dbPath;
    QString dbFile;
public:
    Db(QString, QString, QObject *parent = 0);
    virtual ~Db();
    bool getAllData(QVariant&);
    bool saveData(const QString&);
    bool saveData(const QString&,const QVariantMap&);
    bool deleteDataById(const QString&);
    void copyDatabaseToData();
};

#endif /* DB_HPP_ */
