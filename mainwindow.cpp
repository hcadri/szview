#include "mainwindow.h"

#include <QWebEngineView>
#include "./ui_mainwindow.h"
#include "helpers/SampleHttpServer.h"

MainWindow::MainWindow(QWidget *parent, const QString& defaultUrl)
: QMainWindow(parent), ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    if (!defaultUrl.isEmpty()) {
        ui->urlEdit->setPlainText(defaultUrl);
        viewManager.loadUrl(defaultUrl);
        viewManager.showView();
    }

    auto *server = new SimpleHttpServer(this);
    connect(server, &SimpleHttpServer::urlRequested, &viewManager, &WebEngineViewManager::loadUrl);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetworkReply);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_goBtn_clicked()
{
    urlBox = ui->urlEdit->toPlainText();
    qInfo() << "URL: " << urlBox;
    if(ui->pageType->isChecked()) {
        viewManager.loadUrl(urlBox);
        viewManager.showView();
    } else {
        loadImageFromUrl(urlBox);
    }

}

void MainWindow::on_closeBtn_clicked() {
    viewManager.close();
}

void MainWindow::loadImageFromUrl(const QString& url) const {
    const QNetworkRequest request(url);
    networkManager->get(request);
}

void MainWindow::handleNetworkReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        auto *imageDialog = new QDialog(this);
        imageDialog->setWindowTitle("Image Viewer");
        auto *imageLabel = new QLabel(imageDialog);
        imageLabel->setPixmap(pixmap);
        auto *layout = new QVBoxLayout(imageDialog);
        layout->addWidget(imageLabel);
        imageDialog->setLayout(layout);
        imageDialog->resize(600, 400);
        imageDialog->show();
    }
    reply->deleteLater();
}