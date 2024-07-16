#include "mainwindow.h"

#include <QWebEngineView>
#include "./ui_mainwindow.h"
#include "helpers/SampleHttpServer.h"

MainWindow::MainWindow(QWidget *parent, const QString& defaultUrl)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!defaultUrl.isEmpty()) {
        ui->urlEdit->setPlainText(defaultUrl);
        viewManager.loadUrl(defaultUrl);
        viewManager.showView();
    }

    SimpleHttpServer *server = new SimpleHttpServer(this);
    connect(server, &SimpleHttpServer::urlRequested, &viewManager, &WebEngineViewManager::loadUrl);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_goBtn_clicked()
{
    urlBox = ui->urlEdit->toPlainText();
    qInfo() << "URL: " << urlBox;
    viewManager.loadUrl(urlBox);
    viewManager.showView();
}

void MainWindow::on_closeBtn_clicked() {
    viewManager.close();
}

