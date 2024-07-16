//
// Created by cash on 7/16/24.
//

#ifndef HASSIOLOADER_H
#define HASSIOLOADER_H



#include <QObject>
#include <QWebEngineView>

class HassioLoader : public QObject {
    Q_OBJECT
public:
    explicit HassioLoader(QObject *parent = nullptr);
    void loadHassio();

    signals:
        void loadFinished(bool success);

private:
    QWebEngineView view;
};



#endif //HASSIOLOADER_H
