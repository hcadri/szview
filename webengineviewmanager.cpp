#include "webengineviewmanager.h"

#include <QApplication>

WebEngineViewManager::WebEngineViewManager(QObject *parent) : QObject(parent)
{
    connect(&view, &QWebEngineView::loadFinished, this, &WebEngineViewManager::onLoadFinished);
}

void WebEngineViewManager::loadUrl(const QString &urlString)
{
    currentUrl = urlString;
    QUrl url(urlString);
    if (!url.isValid() || url.isEmpty() || url == QUrl("about:blank")) {
        qInfo() << "Invalid URL: " << urlString;
        currentUrl = "file://" + QApplication::applicationDirPath() + "/index.html";
        url = QUrl(currentUrl);
    }
    view.load(url);
    view.resize(1920, 1080); // Example size, adjust as needed
}

void WebEngineViewManager::showView()
{
    view.show();
}

void WebEngineViewManager::close()
{
    view.close();
}

void WebEngineViewManager::onLoadFinished(bool success)
{
    if (!success) {
        qInfo() << "Failed to load URL: " << currentUrl;
        return;
    }
    qInfo() << "Loaded URL: " << currentUrl;
}
