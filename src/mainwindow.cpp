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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "version.h"
#include "theme.h"
#include "aboutdialog.h"
#include <QClipboard>
#include <QMessageBox>
#include <QNetworkCookieJar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);    
    ui->authView->load(QUrl("about::blank"));    

    setWindowTitle(appName());
    setWindowIcon(theme::icon(theme::IconApp));

    ui->copyUserId_toolButton->setIcon(theme::icon(theme::IconActionCopyToClipboard));
    ui->copyExpiresIn_toolButton->setIcon(theme::icon(theme::IconActionCopyToClipboard));
    ui->copyAccessToken_toolButton->setIcon(theme::icon(theme::IconActionCopyToClipboard));
    ui->quit_action->setIcon(theme::icon(theme::IconActionQuit));
    ui->about_action->setIcon(theme::icon(theme::IconActionAbout));
    ui->aboutQt_action->setIcon(theme::icon(theme::IconActionAboutQt));

    initializeApiVersion();
    initializePermissions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_auth_pushButton_clicked()
{
    int requiredPermissions = 0;
    for (int i = 0; i < ui->permissions_listWidget->count(); ++i) {
        if (ui->permissions_listWidget->item(i)->checkState() == Qt::Checked) {
            requiredPermissions |=
                ui->permissions_listWidget->item(i)->data(Qt::UserRole).toInt();
        }
    }

    ui->authView->setRequiredPermissions(requiredPermissions);
    ui->authView->setAppId(ui->appId_spinBox->value());
    ui->authView->page()->networkAccessManager()->setCookieJar(new QNetworkCookieJar()); // reset all cookie
    ui->authView->openAuthPage();

    ui->accessToken_lineEdit->clear();
    ui->expiresIn_lineEdit->clear();
    ui->userId_lineEdit->clear();
}

void MainWindow::on_authView_authSucceed(const QString &accessToken,
                                         int expiresInSecs,
                                         int userId)
{
    ui->accessToken_lineEdit->setText(accessToken);
    ui->expiresIn_lineEdit->setText(QString::number(expiresInSecs));
    ui->userId_lineEdit->setText(QString::number(userId));
    ui->authView->load(QUrl("about::blank"));
    ui->authView->setHtml("<HTML><HEAD></HEAD><BODY><CENTER><H1>AUTH SUCCEED</H1></CENTER></BODY></HTML>");

    QMessageBox::information(this, tr("Auth"), tr("Success"));
}

void MainWindow::on_authView_authFailed(const QString &code,
                                        const QString &desc)
{
    ui->authView->load(QUrl("about::blank"));
    ui->authView->setHtml("<HTML><HEAD></HEAD><BODY><CENTER><H1>AUTH FAILED</H1></CENTER></BODY></HTML>");

    QMessageBox::warning(this, tr("Auth"), QString("%1 (%2)").arg(desc, code));
}

void MainWindow::initializeApiVersion()
{
    int index = 0;
    while (strlen(VkApiVersions[index])) {
        const QString apiVersion = VkApiVersions[index];
        ui->apiVersion_comboBox->addItem(apiVersion, apiVersion);

        index += 1;
    }

    ui->apiVersion_comboBox->setCurrentIndex(0);
}

void MainWindow::initializePermissions()
{
    for (int i = 0; i < VkPermissionCount; ++i) {
        QListWidgetItem *item = new QListWidgetItem(VkPermissionNames[i]);
        item->setData(Qt::UserRole, VkPermissionCodes[i]);
        item->setStatusTip(permissionDescription(VkPermissionCodes[i]));
        item->setToolTip(permissionDescription(VkPermissionCodes[i]));
        item->setCheckState(Qt::Unchecked);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        ui->permissions_listWidget->addItem(item);
    }
}

void MainWindow::on_copyUserId_toolButton_clicked()
{
    QApplication::clipboard()->setText(ui->userId_lineEdit->text());
}

void MainWindow::on_copyAccessToken_toolButton_clicked()
{
    QApplication::clipboard()->setText(ui->accessToken_lineEdit->text());
}

void MainWindow::on_copyExpiresIn_toolButton_clicked()
{
    QApplication::clipboard()->setText(ui->expiresIn_lineEdit->text());
}

void MainWindow::on_quit_action_triggered()
{
    qApp->quit();
}

void MainWindow::on_about_action_triggered()
{
    AboutDialog dialog(this);
    dialog.setPixmap(QPixmap::fromImage(theme::appImage()));
    dialog.exec();
}

void MainWindow::on_aboutQt_action_triggered()
{
    qApp->aboutQt();
}
