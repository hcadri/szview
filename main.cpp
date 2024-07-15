#include "mainwindow.h"
#include <QWebEngineView>
#include <QApplication>
#include <ui_mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("SZViewer");
    QCoreApplication::setApplicationVersion("1.0");
    QString defaultUrl;
    // Check if a URL was provided as a command-line argument
    if (argc > 1) {
        defaultUrl = argv[1]; // Use the first argument as the URL
    } else {
        defaultUrl = "file://" + QApplication::applicationDirPath() + "/index.html"; // Or set a hardcoded default URL
    }
    MainWindow w(nullptr, defaultUrl);
    w.show();
    return QApplication::exec();
}


