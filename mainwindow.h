#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webengineviewmanager.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QNetworkReply>
#include <QTableWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void loadFilesAndDisplay(const QString& chars, QTableWidget* table_widget);
    explicit MainWindow(QWidget *parent = nullptr,
                        const QString& defaultUrl = "",
                        const QString& mediaPath = "");


    ~MainWindow() override;

public slots:
    void openFile(const QString& filePath);

private:
    Ui::MainWindow *ui;
    QString urlBox;
    WebEngineViewManager viewManager;
    QString defaultUrl;
    QNetworkAccessManager* networkManager;
    QTableWidget* fileListWidget;

private slots:
    void on_goBtn_clicked();
    void on_closeBtn_clicked();
    void loadImageFromUrl(const QString& url) const;
    void handleNetworkReply(QNetworkReply* reply);
};
#endif // MAINWINDOW_H
