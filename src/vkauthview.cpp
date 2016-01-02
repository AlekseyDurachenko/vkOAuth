// Copyright 2013-2016, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "vkauthview.h"


const char VkAuthUri[] = "https://oauth.vk.com/authorize";
const char VkAuthRedirectUri[] = "https://oauth.vk.com/blank.html";

// the supported version of the vk api
const char *VkApiVersions[] = {
    "5.42",
    "5.41",
    "5.40",
    "5.39",
    "5.38",
    "5.37",
    "5.36",
    "5.35",
    "5.34",
    "5.33",
    "5.32",
    "5.31",
    "5.30",
    "5.29",
    "5.28",
    "5.27",
    "5.26",
    "5.25",
    "5.24",
    "5.23",
    "5.22",
    "5.21",
    "5.20",
    "5.19",
    "5.18",
    "5.17",
    "5.16",
    "5.15",
    "5.14",
    "5.13",
    "5.12",
    "5.11",
    "5.10",
    "5.9",
    "5.8",
    "5.7",
    "5.6",
    "5.5",
    "5.4",
    "5.3",
    "5.2",
    "5.1",
    "5.0",
    "4.104",
    "4.103",
    "4.102",
    "4.101",
    "4.100",
    "4.99",
    "4.98",
    "4.97",
    "4.96",
    "4.95",
    "4.94",
    "4.93",
    "4.92",
    "4.91",
    "4.9",
    "4.8",
    "4.7",
    "4.6",
    "4.5",
    "4.4",
    "4.3",
    "4.2",
    "4.1",
    "4.0",
    ""
};

const char *VkPermissionNames[] = {
    "notify"        ,
    "friends"       ,
    "photos"        ,
    "audio"         ,
    "video"         ,
    "offers"        ,
    "questions"     ,
    "pages"         ,
    "+256"          ,
    "status"        ,
    "notes"         ,
    "messages"      ,
    "wall"          ,
    "ads"           ,
    "offline"       ,
    "docs"          ,
    "groups"        ,
    "notifications" ,
    "stats"         ,
    "email"         ,
    "market"        ,
    "nohttps"
};

const int VkPermissionCodes[] = {
    VkPermissionNotify         ,
    VkPermissionFriends        ,
    VkPermissionPhotos         ,
    VkPermissionAudio          ,
    VkPermissionVideo          ,
    VkPermissionOffers         ,
    VkPermissionQuestions      ,
    VkPermissionPages          ,
    VkPermissionAttacheToMenu  ,
    VkPermissionStatus         ,
    VkPermissionNotes          ,
    VkPermissionMessages       ,
    VkPermissionWall           ,
    VkPermissionAds            ,
    VkPermissionOffline        ,
    VkPermissionDocs           ,
    VkPermissionGroups         ,
    VkPermissionNotifications  ,
    VkPermissionStats          ,
    VkPermissionEmail          ,
    VkPermissionMarket         ,
    VkPermissionNoHttps
};

const int VkPermissionCount = sizeof(VkPermissionCodes) / sizeof(int);


QString permissionDescription(int permission)
{
    if (permission == VkPermissionNotify) {
        return QObject::tr("User allowed to send notifications to him/her");
    }
    if (permission == VkPermissionFriends) {
        return QObject::tr("Access to friends");
    }
    if (permission == VkPermissionPhotos) {
        return QObject::tr("Access to photos");
    }
    if (permission == VkPermissionAudio) {
        return QObject::tr("Access to audios");
    }
    if (permission == VkPermissionVideo) {
        return QObject::tr("Access to videos");
    }
    if (permission == VkPermissionOffers) {
        return QObject::tr("Access to offers (obsolete methods)");
    }
    if (permission == VkPermissionQuestions) {
        return QObject::tr("Access to questions (obsolete methods)");
    }
    if (permission == VkPermissionPages) {
        return QObject::tr("Access to wiki pages");
    }
    if (permission == VkPermissionAttacheToMenu) {
        return QObject::tr("Addition of link to the application in the left menu");
    }
    if (permission == VkPermissionStatus) {
        return QObject::tr("Access to user status");
    }
    if (permission == VkPermissionNotes) {
        return QObject::tr("Access to user notes");
    }
    if (permission == VkPermissionMessages) {
        return QObject::tr("(for Standalone applications) Access to advanced methods for messaging");
    }
    if (permission == VkPermissionWall) {
        return QObject::tr("Access to standard and advanced methods for the wall. Note that this access permission is unavailable for sites (it is ignored at attempt of authorization)");
    }
    if (permission == VkPermissionAds) {
        return QObject::tr("Access to advanced methods for Ads API");
    }
    if (permission == VkPermissionOffline) {
        return QObject::tr("Access to API at any time");
    }
    if (permission == VkPermissionDocs) {
        return QObject::tr("Access to documents");
    }
    if (permission == VkPermissionGroups) {
        return QObject::tr("Access to user groups");
    }
    if (permission == VkPermissionNotifications) {
        return QObject::tr("Access to notifications about answers to the user");
    }
    if (permission == VkPermissionStats) {
        return QObject::tr("Access to statistics of user groups and applications where he/she is an administrator");
    }
    if (permission == VkPermissionEmail) {
        return QObject::tr("User e-mail access. Available only for sites");
    }
    if (permission == VkPermissionMarket) {
        return QObject::tr("Market");
    }
    if (permission == VkPermissionNoHttps) {
        return QObject::tr("Possibility to make API requests without HTTPS. Note that this functionality is under testing and can be changed");
    }

    return QString();
}


VkAuthView::VkAuthView(QWidget *parent)
    : QWebView(parent)
{
    m_appId = 1;
    m_apiVersion = VkApiVersions[0];
    m_requiredPermissions = 0;
    connect(this, SIGNAL(urlChanged(QUrl)), SLOT(on_urlChanged(QUrl)));
}

void VkAuthView::setAppId(int appId)
{
    m_appId = appId;
}

void VkAuthView::setRequiredPermissions(int requirePermissions)
{
    m_requiredPermissions = requirePermissions;
}

void VkAuthView::setApiVersion(const QString &apiVersion)
{
    m_apiVersion = apiVersion;
}

void VkAuthView::openAuthPage()
{
    QUrl url(VkAuthUri);
    url.addQueryItem("client_id", QString::number(m_appId));
    url.addQueryItem("scope", QString::number(m_requiredPermissions));
    url.addQueryItem("display", "mobile");
    url.addQueryItem("v", m_apiVersion);
    url.addQueryItem("redirect_uri", VkAuthRedirectUri);
    url.addQueryItem("response_type", "token");
    load(url);
}

void VkAuthView::on_urlChanged(const QUrl &newUrl)
{
    const QUrl url = newUrl.toString().replace("#", "?");

    if (url.hasQueryItem("error")) {
        emit authFailed(url.queryItemValue("error"),
                        url.queryItemValue("error_description"));
        return;
    }

    if (url.hasQueryItem("access_token")) {
        emit authSucceed(url.queryItemValue("access_token"),
                         url.queryItemValue("expires_in").toInt(),
                         url.queryItemValue("user_id").toInt());
        return;
    }
}

QString VkAuthView::permissionToString(int permissions)
{
    QStringList scope;
    if (permissions & VkPermissionNotify) {
        scope << "notify";
    }
    if (permissions & VkPermissionFriends) {
        scope << "friends";
    }
    if (permissions & VkPermissionPhotos) {
        scope << "photos";
    }
    if (permissions & VkPermissionAudio) {
        scope << "audio";
    }
    if (permissions & VkPermissionVideo) {
        scope << "video";
    }
    if (permissions & VkPermissionDocs) {
        scope << "docs";
    }
    if (permissions & VkPermissionNotes) {
        scope << "notes";
    }
    if (permissions & VkPermissionPages) {
        scope << "pages";
    }
    if (permissions & VkPermissionAttacheToMenu) {
        scope << "+256";
    }
    if (permissions & VkPermissionStatus) {
        scope << "status";
    }
    if (permissions & VkPermissionOffers) {
        scope << "offers";
    }
    if (permissions & VkPermissionQuestions) {
        scope << "questions";
    }
    if (permissions & VkPermissionWall) {
        scope << "wall";
    }
    if (permissions & VkPermissionGroups) {
        scope << "groups";
    }
    if (permissions & VkPermissionMessages) {
        scope << "messages";
    }
    if (permissions & VkPermissionEmail) {
        scope << "email";
    }
    if (permissions & VkPermissionNotifications) {
        scope << "notifications";
    }
    if (permissions & VkPermissionStats) {
        scope << "stats";
    }
    if (permissions & VkPermissionAds) {
        scope << "ads";
    }
    if (permissions & VkPermissionMarket) {
        scope << "market";
    }
    if (permissions & VkPermissionOffline) {
        scope << "offline";
    }
    if (permissions & VkPermissionNoHttps) {
        scope << "nohttps";
    }

    return scope.join(",");
}
