#include "mainwindow.h"
#include <QWebEngineView>
#include <QApplication>
#include <ui_mainwindow.h>
#include "helpers/configloader.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("SZViewer");
    QCoreApplication::setApplicationVersion("1.0");
    QString defaultUrl;

    auto config = ConfigLoader::loadConfig(QApplication::applicationDirPath() + "/config.json");


    // Check if a URL was provided as a command-line argument
    if (argc > 1) {
        defaultUrl = argv[1]; // Use the first argument as the URL
    }
    // Check if a URL was provided in the config file
    else if (!config.isEmpty()) {
        defaultUrl = config["defaultUrl"].toString();
    }
    else {
        defaultUrl = "file://" + QApplication::applicationDirPath() + "/index.html"; // Or set a hardcoded default URL
    }
    MainWindow w(nullptr, defaultUrl);
    // w.show();
    return QApplication::exec();
}


