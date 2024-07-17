#ifndef WEBENGINEVIEWMANAGER_H
#define WEBENGINEVIEWMANAGER_H

#include <QObject>
#include <QWebEngineView>
#include <QUrl>
#include <QDebug>

class WebEngineViewManager : public QObject
{
    Q_OBJECT
public:
    explicit WebEngineViewManager(QObject *parent = nullptr);
    void loadUrl(const QString &urlString);
    void showView();
    void close();

private:
    QWebEngineView view;
    QString currentUrl;


    private slots:
        void onLoadFinished(bool success) const;
};

#endif // WEBENGINEVIEWMANAGER_H
