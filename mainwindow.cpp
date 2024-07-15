#include "mainwindow.h"

#include <QWebEngineView>

#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(goBtn, SIGNAL(click()), this, SLOT(on_goBtn_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_goBtn_clicked()
{
    urlBox = ui->urlEdit->toPlainText();
    qInfo() << "URL: " << urlBox;
    view.load(QUrl(urlBox));
    view.resize(1920, 1080);
    view.show();
}

