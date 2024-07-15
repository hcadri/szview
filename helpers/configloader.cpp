#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDebug>

class ConfigLoader {
public:
    static QJsonObject loadConfig(const QString& filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open config file:" << filePath;
            return {};
        }

        QTextStream in(&file);
        QString configData = in.readAll();
        file.close();

        QJsonDocument document = QJsonDocument::fromJson(configData.toUtf8());
        if (document.isNull()) {
            qWarning() << "Failed to parse config file:" << filePath;
            return {};
        }

        return document.object();
    }
};