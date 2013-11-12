// Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "cmainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

QListWidgetItem *createPermissionItem(const QString &text, QvkAuthView::Permission permission,
    Qt::CheckState checkState = Qt::Unchecked)
{
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setData(Qt::UserRole, permission);
    item->setCheckState(checkState);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    return item;
}

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->authView->load(QUrl("about::blank"));

    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Notify"), QvkAuthView::Notify));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Friends"), QvkAuthView::Friends, Qt::Checked));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Photos"), QvkAuthView::Photos, Qt::Checked));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Audio"), QvkAuthView::Audio));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Video"), QvkAuthView::Video));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Docs"), QvkAuthView::Docs));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Notes"), QvkAuthView::Notes));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Pages"), QvkAuthView::Pages));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("AttacheToMenu"), QvkAuthView::AttacheToMenu));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Status"), QvkAuthView::Status));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Offers"), QvkAuthView::Offers));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Questions"), QvkAuthView::Questions));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Wall"), QvkAuthView::Wall));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Groups"), QvkAuthView::Groups, Qt::Checked));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Messages"), QvkAuthView::Messages));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Notifications"), QvkAuthView::Notifications));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Stats"), QvkAuthView::Stats));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Ads"), QvkAuthView::Ads));
    ui->listWidget_Permissions->addItem(createPermissionItem(tr("Offline"), QvkAuthView::Offline));

    connect(ui->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_pushButton_OpenAuthPage_clicked()
{
    QvkAuthView::Permissions requiredPermissions;
    for (int i = 0; i < ui->listWidget_Permissions->count(); ++i)
    {
        if (ui->listWidget_Permissions->item(i)->checkState() == Qt::Checked)
        {
            requiredPermissions |= static_cast<QvkAuthView::Permission>(
                        ui->listWidget_Permissions->item(i)->data(Qt::UserRole).toInt());
        }
    }
    ui->authView->setRequiredPermissions(requiredPermissions);
    ui->authView->setAppId(ui->spinBox_AppId->value());
    ui->authView->page()->networkAccessManager()->setCookieJar(new QNetworkCookieJar()); // reset all cookie
    ui->authView->openAuthPage();

    ui->lineEdit_AccessToken->clear();
    ui->lineEdit_ExpiresIn->clear();
    ui->lineEdit_UserId->clear();
}

void CMainWindow::on_authView_authSuccess(const QString &accessToken, int expiresInSecs, int userId)
{
    ui->lineEdit_AccessToken->setText(accessToken);
    ui->lineEdit_ExpiresIn->setText(QString::number(expiresInSecs));
    ui->lineEdit_UserId->setText(QString::number(userId));
    ui->authView->load(QUrl("about::blank"));

    QMessageBox::information(this, tr("Auth"), tr("Success"));
}

void CMainWindow::on_authView_authFail(const QString &errorCode, const QString &errorDesc)
{
    ui->authView->load(QUrl("about::blank"));

    QMessageBox::warning(this, errorCode, errorDesc);
}
