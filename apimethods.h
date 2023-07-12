#ifndef APIMETHODS_H
#define APIMETHODS_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QEventLoop>
#include <QPixmap>

class ApiCardConnector : public QObject
{
    Q_OBJECT
public:
    ApiCardConnector(int category = 0, const QString& name = "", const QString& description = "", const QPixmap& image = QPixmap())
        : category(category), name(name), description(description), image(image)
    {
        makeRequest();
    }

    const QString &getDescription() const;
    void setDescription(const QString &newDescription);
    void resetDescription();

    const QString &getName() const;
    void setName(const QString &newName);
    void resetName();

    const QPixmap &getImage() const;
    void setImage(const QPixmap &newImage);

signals:
    void descriptionChanged();

    void nameChanged();

    void imageChanged();

private:
    int category;
    QString name;
    QString description;
    QPixmap image;
    bool processingComplete = false;

    void processJsonData(const QByteArray& jsonData)
    {
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (!doc.isArray()) {
            qDebug() << "Invalid JSON data";
        }

        QJsonArray jsonArray = doc.array();
        for (const QJsonValue& jsonValue : jsonArray) {
            if (jsonValue.isObject()) {
                QJsonObject jsonObject = jsonValue.toObject();
                category = jsonObject["category"].toInt();
                name = jsonObject["name"].toString();
                description = jsonObject["description"].toString();
                QString photoUrl = jsonObject["photo"].toString();

                QUrl imageUrl(photoUrl);  // Replace with your image URL
                QNetworkAccessManager* manager = new QNetworkAccessManager(this);  // Pass a valid QObject pointer

                // Send a GET request to download the image
                QNetworkReply* reply = manager->get(QNetworkRequest(imageUrl));

                QObject::connect(reply, &QNetworkReply::finished, [=]() {
                    if (processingComplete) {
                        return;
                    }
                    processingComplete = true;
                    if (reply->error() == QNetworkReply::NoError) {
                        // Read the image data
                        QByteArray imageData = reply->readAll();

                        // Create a pixmap from the image data
                        image.loadFromData(imageData);
                        qDebug() <<"img1test:"<< image.size();
                        qDebug() << "Connected Info:" <<Qt::endl
                                 << "Category:" << category<<Qt::endl
                                 << "Name:" << name<<Qt::endl
                                 << "Description:" << description<<Qt::endl
                                 << "Photo URL:" << photoUrl<<Qt::endl
                                 << "Image:" << (image.isNull() ? "null" : "valid");
                    } else {
                        qDebug() << "Error loading image:" << reply->errorString();
                    }
                    reply->deleteLater();
                    manager->deleteLater();
                });
            }
        }
    }

    // Make the GET request and handle the response
    void makeRequest()
    {
        QNetworkAccessManager manager;
        QNetworkRequest request(QUrl("https://64a3a005c3b509573b565443.mockapi.io/api/product-card"));

        QNetworkReply* reply = manager.get(request);

        QEventLoop eventLoop;
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray data = reply->readAll();
                processJsonData(data);
            } else {
                qFatal("Error: %s", qPrintable(reply->errorString()));
            }
            reply->deleteLater();
            eventLoop.quit();
        });

        eventLoop.exec();
        qDebug() << "After makeRequest()";
    }
    Q_PROPERTY(QString description READ getDescription WRITE setDescription RESET resetDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString name READ getName WRITE setName RESET resetName NOTIFY nameChanged)
    Q_PROPERTY(QPixmap image READ getImage WRITE setImage NOTIFY imageChanged)
};

inline const QString &ApiCardConnector::getDescription() const
{
    return description;
}

inline void ApiCardConnector::setDescription(const QString &newDescription)
{
    if (description == newDescription)
        return;
    description = newDescription;
    emit descriptionChanged();
}

inline void ApiCardConnector::resetDescription()
{
    setDescription({}); // TODO: Adapt to use your actual default value
}

inline const QString &ApiCardConnector::getName() const
{
    return name;
}

inline void ApiCardConnector::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

inline void ApiCardConnector::resetName()
{
    setName({}); // TODO: Adapt to use your actual default value
}

inline const QPixmap &ApiCardConnector::getImage() const
{
    return image;
}

inline void ApiCardConnector::setImage(const QPixmap &newImage)
{
    image = newImage;
    emit imageChanged();
}

#endif // APIMETHODS_H
