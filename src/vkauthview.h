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
#ifndef VKAUTHVIEW_H
#define VKAUTHVIEW_H


#include <QtWebKit>


extern const char *VkApiVersions[];
extern const char *VkPermissionNames[];
extern const int VkPermissionCodes[];
extern const int VkPermissionCount;

const int VkPermissionNotify          = 1;
const int VkPermissionFriends         = 2;
const int VkPermissionPhotos          = 4;
const int VkPermissionAudio           = 8;
const int VkPermissionVideo           = 16;
const int VkPermissionOffers          = 32;
const int VkPermissionQuestions       = 64;
const int VkPermissionPages           = 128;
const int VkPermissionAttacheToMenu   = 256;
const int VkPermissionStatus          = 1024;
const int VkPermissionNotes           = 2048;
const int VkPermissionMessages        = 4096;
const int VkPermissionWall            = 8192;
const int VkPermissionAds             = 32768;
const int VkPermissionOffline         = 65536;
const int VkPermissionDocs            = 131072;
const int VkPermissionGroups          = 262144;
const int VkPermissionNotifications   = 524288;
const int VkPermissionStats           = 1048576;
const int VkPermissionEmail           = 4194304;
const int VkPermissionMarket          = 134217728;
const int VkPermissionNoHttps         = 2147483648;  // this code is not exists in docs

QString permissionDescription(int permission);


class VkAuthView : public QWebView
{
    Q_OBJECT
public:
    explicit VkAuthView(QWidget *parent = 0);

    inline const int &appId() const;
    void setAppId(int appId);

    inline const int &requiredPermissions() const;
    void setRequiredPermissions(int requiredPermissions);

    inline const QString &apiVersion() const;
    void setApiVersion(const QString &apiVersion);

signals:
    void authSucceed(const QString &accessToken, int expiresInSecs, int userId);
    void authFailed(const QString &errorCode, const QString &errorDesc);

public slots:
    void openAuthPage();

private slots:
    void on_urlChanged(const QUrl &newUrl);

private:
    QString permissionToString(int permissions);

private:
    int m_appId;
    QString m_apiVersion;
    int m_requiredPermissions;
};


const int &VkAuthView::appId() const
{
    return m_appId;
}

const int &VkAuthView::requiredPermissions() const
{
    return m_requiredPermissions;
}

const QString &VkAuthView::apiVersion() const
{
    return m_apiVersion;
}


#endif // VKAUTHVIEW_H
