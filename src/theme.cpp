// Copyright 2016, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "theme.h"


static QHash<theme::Icon, QIcon> m_icons;
static QImage m_appImage;


static QString themeFileName(const QString &baseFileName)
{
    return QString(":/icons/%1.png").arg(baseFileName);
}

static QIcon themeIcon(const QString &baseFileName)
{
    return QIcon(themeFileName(baseFileName));
}

static QImage themeImage(const QString &baseFileName)
{
    return QImage(themeFileName(baseFileName));
}


void theme::initialize()
{
    m_appImage = themeImage("vkoauth");

    m_icons.insert(IconApp, themeIcon("vkoauth"));

    m_icons.insert(IconActionCopyToClipboard,   themeIcon("action-copy-to-clipboard"));
    m_icons.insert(IconActionQuit,      themeIcon("action-quit"));
    m_icons.insert(IconActionAbout,     themeIcon("action-about"));
    m_icons.insert(IconActionAboutQt,   themeIcon("action-about-qt"));
}

const QIcon theme::icon(Icon name, const QIcon &defaultIcon)
{
    return m_icons.value(name, defaultIcon);
}

const QImage &theme::appImage()
{
    return m_appImage;
}
