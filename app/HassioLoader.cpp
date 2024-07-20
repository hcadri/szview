//
// Created by cash on 7/16/24.
//

#include "HassioLoader.h"
HassioLoader::HassioLoader(QObject *parent) : QObject(parent) {
    connect(&view, &QWebEngineView::loadFinished, this, &HassioLoader::loadFinished);
}

void HassioLoader::loadHassio() {
    view.load(QUrl("http://hassio.local:8123"));
        QString username = "username";
        QString password = "password";

        QString script = QStringLiteral(
            R"DELIM(
            setTimeout(
                function() {
                    document.querySelector('input[name="username"]').value = "%1";
                    document.querySelector('input[name="password"]').value = "%2";
                    document.querySelector('form').submit();
                },
                1000
            );

        )DELIM"
        ).arg(username).arg(password);

        view.page()->runJavaScript(script, 42);

    view.show();
}