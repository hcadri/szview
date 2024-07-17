#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webengineviewmanager.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString& defaultUrl = "");
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QString urlBox;
    WebEngineViewManager viewManager;
    QString defaultUrl;
    QNetworkAccessManager* networkManager;


private slots:
    void on_goBtn_clicked();
    void on_closeBtn_clicked();
    void loadImageFromUrl(const QString& url);
    void handleNetworkReply(QNetworkReply* reply);
};
#endif // MAINWINDOW_H
