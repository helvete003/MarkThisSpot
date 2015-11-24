/*
 * db.cpp
 *
 *  Created on: 15.12.2014
 *      Author: helvete
 */

#include "db.hpp"

Db::Db(QString path, QString name, QObject *parent)
    : QObject(parent)
    , dbPath(path)
    , dbFile(name)
{
    qDebug() << "Eintrag";
    copyDatabaseToData();
}

Db::~Db() {

}

void Db::copyDatabaseToData() {
    //We have to copy the database to another place or it wont be writeable
    QString dataFolder = QDir::homePath();
    QString newFileName = dataFolder + "/" + dbFile;
    QFile newFile(newFileName);
    if(!newFile.exists()) {
        QString appFolder(QDir::homePath());
        appFolder.chop(4);
        QString origFileName = appFolder + dbPath + dbFile;
        QFile originalFile(origFileName);

        if(originalFile.exists()) {
            QFileInfo fileInfo(newFileName);
            QDir().mkpath(fileInfo.dir().path());
            if(!originalFile.copy(newFileName)) {

                qDebug() << "Datenbank kopier fehler " << newFileName;
            } else {
                qDebug() << "Datenbank kopiert";
            }
        } else {
            qDebug() << "Copy error";
        }

    }
    dbPath = dataFolder;

}

bool Db::getAllData(QVariant& data) {
    //SqlDataAccess sda(QDir::currentPath() + dbPath + dbFile);
    SqlDataAccess sda(dbPath + "/" + dbFile);
    data = sda.execute("SELECT * FROM data ORDER BY id DESC");

    if(sda.hasError()) {
          DataAccessError err = sda.error();

          if (err.errorType() == DataAccessErrorType::SourceNotFound)
          {
              qDebug() << "Source not found: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::ConnectionFailure)
          {
              qDebug() << "Connection failure: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::OperationFailure)
          {
              qDebug() << "Operation failure: " << err.errorMessage();
          }
          SystemToast *toast = new SystemToast();

          toast->setBody("Database Error");
          toast->setPosition(SystemUiPosition::MiddleCenter);
          toast->show();
          sda.disconnect();
          return false;
    }

    sda.disconnect();
    return true;
}
bool Db::saveData(const QString& query, const QVariantMap& data)
{
    qDebug() << "prepared";
    SqlDataAccess sda(dbPath + "/" + dbFile);
    sda.execute(query,data);


    if(sda.hasError()) {
          DataAccessError err = sda.error();

          if (err.errorType() == DataAccessErrorType::SourceNotFound)
          {
              qDebug() << "Source not found: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::ConnectionFailure)
          {
              qDebug() << "Connection failure: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::OperationFailure)
          {
              qDebug() << "Operation failure: " << err.errorMessage();
          }
          SystemToast *toast = new SystemToast();

          toast->setBody("Failed to save");
          toast->setPosition(SystemUiPosition::MiddleCenter);
          toast->show();
          sda.disconnect();
          return false;
    }

    sda.disconnect();
    return true;
}
bool Db::saveData(const QString& query)
{
    SqlDataAccess sda(dbPath + "/" + dbFile);
    sda.execute(query);


    if(sda.hasError()) {
          DataAccessError err = sda.error();

          if (err.errorType() == DataAccessErrorType::SourceNotFound)
          {
              qDebug() << "Source not found: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::ConnectionFailure)
          {
              qDebug() << "Connection failure: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::OperationFailure)
          {
              qDebug() << "Operation failure: " << err.errorMessage();
          }
          SystemToast *toast = new SystemToast();

          toast->setBody("Failed to save");
          toast->setPosition(SystemUiPosition::MiddleCenter);
          toast->show();
          sda.disconnect();
          return false;
    }

    sda.disconnect();
    return true;
}
bool Db::deleteDataById(const QString& delId)
{
    SqlDataAccess sda(dbPath + "/" + dbFile);
    QString sqlString = "DELETE FROM data WHERE id="+delId+";";
    qDebug() << sqlString;
    sda.execute(sqlString);

    if(sda.hasError()) {
          DataAccessError err = sda.error();

          if (err.errorType() == DataAccessErrorType::SourceNotFound)
          {
              qDebug() << "Source not found: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::ConnectionFailure)
          {
              qDebug() << "Connection failure: " << err.errorMessage();
          }
          else if (err.errorType() == DataAccessErrorType::OperationFailure)
          {
              qDebug() << "Operation failure: " << err.errorMessage();
          }
          SystemToast *toast = new SystemToast();

          toast->setBody("Failed to save");
          toast->setPosition(SystemUiPosition::MiddleCenter);
          toast->show();
          sda.disconnect();
          return false;
    }

    sda.disconnect();
    return true;
}
