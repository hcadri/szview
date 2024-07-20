#include "mainwindow.h"

#include <QWebEngineView>
#include "./ui_mainwindow.h"
#include "helpers/SampleHttpServer.h"
#include <QDir>
#include <QFileInfoList>
#include <QDesktopServices>
#include <QMessageBox>
#include <QRegularExpression>

#include "ImageViewer.h"


void MainWindow::loadFilesAndDisplay(const QString& chars, QTableWidget* table_widget) {
    QDir dir(chars);
    QFileInfoList files = dir.entryInfoList(QDir::Files);

    table_widget->setRowCount(files.size());
    table_widget->setColumnCount(3); // Add one for the "Open" button
    table_widget->setHorizontalHeaderLabels(QStringList() << "File Name" << "File Size" << "Action");

    for (int i = 0; i < files.size(); ++i) {
        QFileInfo fileInfo = files.at(i);

        // File name
        auto* nameItem = new QTableWidgetItem(fileInfo.fileName());
        table_widget->setItem(i, 0, nameItem);

        // File size
        auto* sizeItem = new QTableWidgetItem(QString::number(fileInfo.size()));
        table_widget->setItem(i, 1, sizeItem);

        // Open button
        auto* openBtn = new QPushButton("Open");
        table_widget->setCellWidget(i, 2, openBtn);
        // connect(openBtn, &QPushButton::clicked, [this, fileInfo]() { openFile(fileInfo.absoluteFilePath()); });
        connect(openBtn, &QPushButton::clicked, this, [this, fileInfo]() { openFile(fileInfo.absoluteFilePath()); });
    }
}

MainWindow::MainWindow(QWidget *parent, const QString& defaultUrl, const QString& mediaPath)
: QMainWindow(parent), ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    // Open the default URL if one was provided
    // if (!defaultUrl.isEmpty()) {
    //     ui->urlEdit->setPlainText(defaultUrl);
    //     viewManager.loadUrl(defaultUrl);
    //     viewManager.showView();
    // }

    auto *server = new SimpleHttpServer(this);
    connect(server, &SimpleHttpServer::urlRequested, &viewManager, &WebEngineViewManager::loadUrl);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetworkReply);

    ui->fileListWidget->setRowCount(2);
    ui->fileListWidget->setColumnCount(2);
    ui->fileListWidget->setHorizontalHeaderLabels(QStringList() << "File Name" << "File Size");

    loadFilesAndDisplay(mediaPath, ui->fileListWidget);
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

        ImageViewer viewer;
        viewer.setImage(pixmap);
        viewer.showDialog();
    }
    reply->deleteLater();
}

void MainWindow::openFile(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    // // Inside openFile method
    // if (QRegularExpression("png|jpg|jpeg|bmp|gif").match(fileInfo.suffix().toLower()).hasMatch()) {
    //     QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    // } else {
    //     QMessageBox::information(this, "Not an Image", "The selected file is not an image.");
    // }

    QPixmap pixmap(filePath);
    ImageViewer viewer;
    viewer.setImage(pixmap);
    viewer.showDialog();

}