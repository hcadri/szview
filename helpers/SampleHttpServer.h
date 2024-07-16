#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>


#ifndef SAMPLEHTTPSERVER_H
#define SAMPLEHTTPSERVER_H


class SimpleHttpServer : public QObject {
    Q_OBJECT
public:
    explicit SimpleHttpServer(QObject *parent = nullptr);

    signals:
        void urlRequested(const QString &url);

    private slots:
        void handleNewConnection();

private:
    QTcpServer *tcpServer;
};
#endif //SAMPLEHTTPSERVER_H
