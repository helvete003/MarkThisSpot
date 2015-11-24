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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include "gps.hpp"
#include "db.hpp"
#include "mail.hpp"
#include "abstractAI.hpp"
#include "browser.hpp"
#include "bbmaps.hpp"

#include <QObject>
#include <bb/cascades/ListView>
#include <bb/cascades/ActionItem>
#include <bb/system/SystemPrompt>
#include <bb/system/SystemDialog>
#include <bb/system/SystemListDialog>
#include <bb/system/SystemUiResult>
#include <bb/cascades/Container>
#include <bb/cascades/ActionItem>
#include <bb/cascades/ArrayDataModel>

using namespace bb::cascades;
using namespace bb::system;

namespace bb
{
    namespace cascades
    {
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI();
    virtual ~ApplicationUI();
    void callAi(Ai*, const QVariantMap&,int);
private slots:
    void onSystemLanguageChanged();
    void onTriggered();
    void onPromptFinished(bb::system::SystemUiResult::Type);
    void onDelPromptFinished(bb::system::SystemUiResult::Type);
    void onOpenBrowserFinished(bb::system::SystemUiResult::Type);
    void onSendLinkFinished(bb::system::SystemUiResult::Type);
    void onDeleteTriggered();
    void onOpenBrowserTriggered();
    void onSendLinkTriggered();
    void onBbMapsTriggered();

private:
    void fillListView();
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    ListView *lv;
    ActionItem *ai;
    SystemPrompt *prompt;

    SystemListDialog *openListDialog;
    SystemListDialog *sendListDialog;

    SystemDialog *delDialog;
    Gps *navi;
    Container *loader;

    Db *dataBase;
    QVariant dataDb;
    ArrayDataModel *model;
    //ActionItems
    ActionItem *openBrowser;
    ActionItem *sendLink;
    ActionItem *deleteItem;
    ActionItem *bbMaps;

    void initListDialog(int);
};

#endif /* ApplicationUI_HPP_ */
