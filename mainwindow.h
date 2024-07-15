#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

#include "webengineviewmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const QString& defaultUrl = "");
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QString urlBox;
    WebEngineViewManager viewManager;
    QString defaultUrl;



private slots:
    void on_goBtn_clicked();

};
#endif // MAINWINDOW_H
