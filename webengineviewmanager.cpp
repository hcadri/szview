#include "webengineviewmanager.h"

WebEngineViewManager::WebEngineViewManager(QObject *parent) : QObject(parent)
{
    connect(&view, &QWebEngineView::loadFinished, this, &WebEngineViewManager::onLoadFinished);
}

void WebEngineViewManager::loadUrl(const QString &urlString)
{
    currentUrl = urlString;
    QUrl url(urlString);
    if (!url.isValid()) {
        qInfo() << "Invalid URL: " << urlString;
    }
    view.load(url);
    view.resize(1920, 1080); // Example size, adjust as needed
}

void WebEngineViewManager::showView()
{
    view.show();
}

void WebEngineViewManager::onLoadFinished(bool success)
{
    if (!success) {
        qInfo() << "Failed to load URL: " << currentUrl;
        return;
    }
    qInfo() << "Loaded URL: " << currentUrl;
}