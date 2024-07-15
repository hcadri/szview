#include "mainwindow.h"

#include <QWebEngineView>

#include "./ui_mainwindow.h"
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

