/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

//Test

#include <bb/cascades/StandardListItem>
#include <bb/cascades/ActionSet>
//TIME
#include <QDateTime>

using namespace bb::cascades;

ApplicationUI::ApplicationUI() :
        QObject()
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    /*Create SystemPrompt*/
    prompt = new SystemPrompt();
    prompt->setTitle("Save Mark");
    prompt->setDismissAutomatically(true);
    prompt->inputField()->setEmptyText("Write a note");
    if(!connect(prompt,SIGNAL(finished(bb::system::SystemUiResult::Type)),this,SLOT(onPromptFinished(bb::system::SystemUiResult::Type)))) {
        qDebug() << "Konnte prompt nicht connecten";
        prompt->deleteLater();
    }
    /* Create SystemPrompt End */
    /* DELETE PROMPT */
    delDialog = new SystemDialog("Yes", "No");
    delDialog->setTitle("Delete");
    delDialog->setBody("Do you really want to delete this entry?");
    if(!connect(delDialog
            ,SIGNAL(finished(bb::system::SystemUiResult::Type))
            ,this
            ,SLOT(onDelPromptFinished(bb::system::SystemUiResult::Type)))) {
        qDebug() << "Konnte del Dialog nicht connecten";
        delDialog->deleteLater();
    }
    /* DELETE PROMPT END */
    //List Dialog
    initListDialog(0);
    initListDialog(1);

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    ai = root->findChild<ActionItem*>("aItem");
    lv = root->findChild<ListView*>("listView");
    loader = root->findChild<Container*>("loadCont");
    /*
     * Leider muss das Context Menue per c++ hinzugefuegt werden
     * ich konnte leider nicht herausfinden wieso aber immerhin funktioniert es auf diese weise:
     * */
    deleteItem = root->findChild<ActionItem*>("delAction");
    openBrowser = root->findChild<ActionItem*>("browserAction");
    sendLink = root->findChild<ActionItem*>("linkAction");
    bbMaps = root->findChild<ActionItem*>("mapsAction");
    /*deleteItem = ActionItem::create().title("Delete").imageSource(QString("assets/ic_delete.png"));
    openBrowser = ActionItem::create().title("Open in Browser").imageSource(QString("assets/ic_browser.png"));
    sendLink = ActionItem::create().title("Send Link").imageSource(QString("assets/ic_email_dk.png"));
    bbMaps = ActionItem::create().title("BB Maps").imageSource(QString("assets/ic_map.png"));
    ActionSet *as = ActionSet::create();
    as->add(bbMaps);
    as->add(openBrowser);
    as->add(sendLink);
    as->add(deleteItem);
    lv->addActionSet(as);*/

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    /*SIGNALE verbinden */
    if(!connect(ai, SIGNAL(triggered()),this,SLOT(onTriggered()))) {
        qDebug() << "Konnte ActionItem nicht connecten!";
    }
    if(bbMaps) {
        if(!connect(bbMaps
               , SIGNAL(triggered())
               ,this
               ,SLOT(onBbMapsTriggered()))) {
           qDebug() << "Konnte ActionItem bbMaps nicht Connecten!";
       }
    }
    if(openBrowser) {
        if(!connect(openBrowser
               , SIGNAL(triggered())
               ,this
               ,SLOT(onOpenBrowserTriggered()))) {
           qDebug() << "Konnte ActionItem openBrowser nicht Connecten!";
       }
    }
    if(sendLink) {
        if(!connect(sendLink
               , SIGNAL(triggered())
               ,this
               ,SLOT(onSendLinkTriggered()))) {
           qDebug() << "Konnte ActionItem sendLink nicht Connecten!";
       }
    }
    if(deleteItem) {
       if(!connect(deleteItem
               , SIGNAL(triggered())
               ,this
               ,SLOT(onDeleteTriggered()))) {
           qDebug() << "Konnte ActionItem delete nicht Connecten!";
       }
    }

    navi = new Gps(this, prompt, ai, loader);
    dataBase = new Db("app/native/assets/","database.db", this);
    fillListView();
    //deleteItem = root->findChild<ActionItem*>("deleteAction");

}
ApplicationUI::~ApplicationUI()
{

}

void ApplicationUI::onTriggered()
{
    navi->getPosition();
    ai->setEnabled(false);
    loader->setVisible(true);
}
void ApplicationUI::onPromptFinished(bb::system::SystemUiResult::Type value)
{
    ai->setEnabled(true);
    loader->setVisible(false);

    qDebug() << "Test";
    if(value == SystemUiResult::ConfirmButtonSelection) {
        qDebug() << "Promt angenommen";

        QString sqlQuery = "INSERT INTO data (latitude,longitude,note,date) VALUES(:latitude,:longitude,:note,:date);";
        QVariantMap queryData;
        queryData.insert("latitude",QString::number(navi->getLatitude()));
        queryData.insert("longitude",QString::number(navi->getLongitude()));
        queryData.insert("note",prompt->inputFieldTextEntry());
        queryData.insert("date",QDate::currentDate().toString("dd.MM.yy"));

        if(dataBase->saveData(sqlQuery,queryData)) {
        //if(dataBase->saveData(sqlString)) {
            fillListView();
        } else {
            ai->setEnabled(false);
        }
    }
}
void ApplicationUI::onDelPromptFinished(bb::system::SystemUiResult::Type type)
{
    if(type == SystemUiResult::ConfirmButtonSelection)
    {
        QString delId = model->data(lv->selected()).value<QVariantMap>()["id"].value<QString>();
        qDebug() << delId;
        if(dataBase->deleteDataById(delId)) {
           fillListView();
       } else {
           qDebug() << "Error: eintrag löschen";
       }
    }
}
void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("MarkThisSpot_v0_2_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::fillListView()
{
    qDebug() << "fillListView";
    if(dataBase->getAllData(dataDb)) {
        QVariantList listData = dataDb.value<QVariantList>();
        if(listData.length() >= 0) {
            qDebug() << "Data count: " << listData.length();
            //Short version of if
            int mapSize = (listData.length() == 0) ? 1 : listData.length();
            QVariantMap *listMap = new QVariantMap[mapSize];
            QVariantList newData;
            for(int i = 0; i < listData.length(); ++i) {
                QString buildTitle = listData[i].value<QVariantMap>()["latitude"].toString() + " - " + listData[i].value<QVariantMap>()["longitude"].toString();
                qDebug() << buildTitle;
                listMap[i] = listData[i].value<QVariantMap>();
                listMap[i].insert("title", buildTitle);
                newData.append(listMap[i]);
            }
            if(listData.length() == 0) {
                qDebug() << "Empty string";
                listMap[0].insert("title", "Empty");
                listMap[0].insert("note", "Press the \"Mark\" button on the bottom.");
                newData.append(listMap[0]);
            }
            qDebug() << "ArrayDataModel";
            model = new ArrayDataModel();
            model->append(newData);
            qDebug() << "setDataModel";
            lv->setDataModel(model);
        }
    } else {
        ai->setEnabled(false);
    }

}
void ApplicationUI::onDeleteTriggered()
{
    //exec wird aufgerufen damit die oberfläche blockiert wird, somit ist der select vom ListView danach noch vorhanden
    QVariantMap data = model->data(lv->selected()).value<QVariantMap>();
    if(!data.empty() && data["title"].value<QString>() != "Empty") {
        delDialog->exec();
    }
}
void ApplicationUI::onOpenBrowserTriggered()
{
    //exec wird aufgerufen damit die oberfläche blockiert wird, somit ist der select vom ListView danach noch vorhanden
    QVariantMap data = model->data(lv->selected()).value<QVariantMap>();
    if(!data.empty() && data["title"].value<QString>() != "Empty") {
        openListDialog->exec();
    }
}
void ApplicationUI::onSendLinkTriggered()
{
    //exec wird aufgerufen damit die oberfläche blockiert wird, somit ist der select vom ListView danach noch vorhanden
    QVariantMap data = model->data(lv->selected()).value<QVariantMap>();
    if(!data.empty() && data["title"].value<QString>() != "Empty") {
        sendListDialog->exec();
    }
}
void ApplicationUI::onBbMapsTriggered()
{
    //exec wird aufgerufen damit die oberfläche blockiert wird, somit ist der select vom ListView danach noch vorhanden
    QVariantMap data = model->data(lv->selected()).value<QVariantMap>();
    if(!data.empty() && data["title"].value<QString>() != "Empty") {
        BbMaps bbMaps(this);
        bbMaps.open(data);

    }
}
void ApplicationUI::onOpenBrowserFinished(bb::system::SystemUiResult::Type value)
{
    if(value == SystemUiResult::ConfirmButtonSelection) {
        QVariantMap data = model->data(lv->selected()).value<QVariantMap>();
        callAi(new Browser(),data,openListDialog->selectedIndices().value(0));
    }
}
void ApplicationUI::onSendLinkFinished(bb::system::SystemUiResult::Type value)
{
    if(value == SystemUiResult::ConfirmButtonSelection) {
        QVariantMap data = model->data(lv->selected()).value<QVariantMap>();
        callAi(new Mail(),data,sendListDialog->selectedIndices().value(0));
    }
}
void ApplicationUI::initListDialog(int num)
{
    switch(num)
    {
        case 0:
            openListDialog = new SystemListDialog("Ok","Cancel");
            openListDialog->setTitle("Open in Browser");
            openListDialog->appendItem("Google Maps");
            openListDialog->appendItem("Bing Maps");
            openListDialog->appendItem("OpenStreetMap");
            openListDialog->appendItem("HERE Maps");
            if(!connect(openListDialog
                        ,SIGNAL(finished(bb::system::SystemUiResult::Type))
                        ,this
                        ,SLOT(onOpenBrowserFinished(bb::system::SystemUiResult::Type))))
            {
                qDebug() << "Konnte List Dialog nicht connecten";
                openListDialog->deleteLater();
            }
        break;
        case 1:
            qDebug() << "sendListDialog ***********************";
            sendListDialog = new SystemListDialog("Ok","Cancel");
            sendListDialog->setTitle("Send Link");
            sendListDialog->appendItem("Google Maps");
            sendListDialog->appendItem("Bing Maps");
            sendListDialog->appendItem("OpenStreetMap");
            sendListDialog->appendItem("HERE Maps");
            if(!connect(sendListDialog
                        ,SIGNAL(finished(bb::system::SystemUiResult::Type))
                        ,this
                        ,SLOT(onSendLinkFinished(bb::system::SystemUiResult::Type))))
            {
                qDebug() << "Konnte List Dialog nicht connecten";
                sendListDialog->deleteLater();
            }
        break;
    }
}
void ApplicationUI::callAi(Ai* model, const QVariantMap& data, int selected)
{
    qDebug() << "selected " << selected;
    switch(selected)
    {
        case 0:
           qDebug() << "Data: " << data;
           model->openGmap(data);
       break;
       case 1:
           qDebug() << "Data: " << data;
           model->openBing(data);
       break;
       case 2:
           qDebug() << "Data: " << data;
           model->openOpenMap(data);
       break;
       case 3:
           qDebug() << "Data: " << data;
           model->openHereMap(data);
       break;
       default:
           qDebug() << "default";
       break;
    }
}
