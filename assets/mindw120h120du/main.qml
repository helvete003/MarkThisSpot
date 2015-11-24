/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
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

import bb.cascades 1.4

Page {
    Container {
        layout: DockLayout {

        }
        Container {
            id:header
            preferredHeight: ui.du(5.0)
            background: Color.Black
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Top
            leftPadding: 10
            rightPadding: 10
            Label {
                id: headerText
                text: "Mark This Spot"
                textStyle.color: Color.White
            }
        }
        Container {
            id:body
            objectName: "body"
            background: Color.create("#f5f5f5")
            verticalAlignment: VerticalAlignment.Bottom
            horizontalAlignment: HorizontalAlignment.Fill
            preferredHeight: ui.du(103.0)
            layout: DockLayout {

            }
            ListView {
                id: listV
                objectName: "listView"
                accessibility.name: "dataList"
                accessibilityMode: A11yMode.Default
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Bottom
                visible: true
                dataModel: ArrayDataModel {
                
                }
                contextActions: [
                    ActionSet {
                        actions: [
                            ActionItem {
                                title: "Delete"
                                imageSource: "asset:///images/ic_delete.png"
                                objectName: "delAction"
                            },
                            ActionItem {
                                title: "Open in Browser"
                                imageSource: "asset:///images/ic_browser.png"
                                objectName: "browserAction"
                            },
                            ActionItem {
                                title: "Send Link"
                                imageSource: "asset:///images/ic_email_dk.png"
                                objectName: "linkAction"
                            },
                            ActionItem {
                                title: "BB Maps"
                                imageSource: "asset:///images/ic_map.png"
                                objectName: "mapsAction"
                            }
                        ]
                    }
                ]
                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            objectName: ListItemData.id
                            title: ListItemData.title
                            description: ListItemData.note
                            status: ListItemData.date
                        
                        }
                    
                    }
                ]
                scrollRole: ScrollRole.Main
            }
            Container {
                id: loadingCont
                objectName: "loadCont"
                preferredHeight: 100
                preferredWidth: 100
                background: Color.Black
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                opacity: 0.1
                
                layout: DockLayout {
                
                }
                minWidth: 100.0
                minHeight: 100.0
                maxWidth: 100.0
                maxHeight: 100.0
                rotationZ: 0.0
                visible: false
                ActivityIndicator {
                    id: activIn
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    preferredHeight: 100
                    preferredWidth: 100
                    accessibility.name: "activIn"
                    running: true
                
                }
            }

        }

    }
    actions: [
        ActionItem {
            id: markAction
            objectName: "aItem"
            ActionBar.placement: ActionBarPlacement.Signature
            imageSource: "asset:///images/ic_location.png"
            title: qsTr("Mark")

        }
    ]
}
