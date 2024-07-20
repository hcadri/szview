
#include "SampleHttpServer.h"

SimpleHttpServer::SimpleHttpServer(QObject *parent): QObject(parent), tcpServer(new QTcpServer(this)) {
    connect(tcpServer, &QTcpServer::newConnection, this, &SimpleHttpServer::handleNewConnection);
    if (!tcpServer->listen(QHostAddress::Any, 8080)) {
        qCritical() << "Unable to start the server: " << tcpServer->errorString();
    } else {
        qDebug() << "Server started on port" << tcpServer->serverPort();
    }
}

void SimpleHttpServer::handleNewConnection() {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
        QString request(clientSocket->readAll());
        // Simple parsing logic to extract URL from GET request
        if (request.startsWith("GET /setUrl?")) {
            int start = request.indexOf("url=") + 4;
            int end = request.indexOf(" ", start);
            QString url = request.mid(start, end - start);
            emit urlRequested(url);
        }
        clientSocket->write("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nURL set successfully.");
        clientSocket->disconnectFromHost();
    });
}
