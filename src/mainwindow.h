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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void on_auth_pushButton_clicked();
    void on_authView_authSucceed(const QString &accessToken, int expiresInSecs, int userId);
    void on_authView_authFailed(const QString &errorCode, const QString &errorDesc);
    void on_copyUserId_toolButton_clicked();
    void on_copyAccessToken_toolButton_clicked();
    void on_copyExpiresIn_toolButton_clicked();
    void on_quit_action_triggered();
    void on_about_action_triggered();
    void on_aboutQt_action_triggered();

private:
    void initializeApiVersion();
    void initializePermissions();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
