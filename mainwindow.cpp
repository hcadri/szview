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

void MainWindow::loadImageFromUrl(const QString& url)
{
    QNetworkRequest request(url);
    networkManager->get(request);
}

void MainWindow::handleNetworkReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        QDialog *imageDialog = new QDialog(this); // Create a new dialog as a child of the main window
        imageDialog->setWindowTitle("Image Viewer");
        QLabel *imageLabel = new QLabel(imageDialog); // Create a label inside the dialog
        imageLabel->setPixmap(pixmap); // Set the pixmap to the label
        QVBoxLayout *layout = new QVBoxLayout(imageDialog); // Create a layout for the dialog
        layout->addWidget(imageLabel); // Add the label to the layout
        imageDialog->setLayout(layout); // Set the dialog's layout
        imageDialog->resize(600, 400); // Resize the dialog to a reasonable size
        imageDialog->show(); // Show the dialog
    }
    reply->deleteLater();
}