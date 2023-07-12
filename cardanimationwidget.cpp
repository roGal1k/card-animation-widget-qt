#include "cardanimationwidget.h"
#include "ui_cardanimationwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QEventLoop>

QString processJsonData(const QByteArray& jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON data";
        return NULL;
    }

    QJsonArray jsonArray = doc.array();
    for (const QJsonValue& jsonValue : jsonArray) {
        if (jsonValue.isObject()) {
            QJsonObject jsonObject = jsonValue.toObject();
            int category = jsonObject["category"].toInt();
            QString name = jsonObject["name"].toString();
            QString description = jsonObject["description"].toString();
            QString photoUrl = jsonObject["photo"].toString();

            // Do something with the retrieved data
            qDebug() << "Category: " << category;
            qDebug() << "Name: " << name;
            qDebug() << "Description: " << description;
            qDebug() << "Photo URL: " << photoUrl;
            return photoUrl;
        }
    }
    return NULL;
}

// Make the GET request and handle the response
QString makeRequest()
{
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://64a3a005c3b509573b565443.mockapi.io/api/product-card"));  // Replace with your API endpoint URL

    QNetworkReply* reply = manager.get(request);
    qDebug() << "test0";

    QEventLoop eventLoop;
    QString photoUrl="";
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        qDebug() << "test1";
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "test2";
            QByteArray data = reply->readAll();
            QString photoUrl = processJsonData(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        eventLoop.quit();
    });

    eventLoop.exec();
    return photoUrl;
    qDebug() << "After makeRequest()";
}

CardAnimationWidget::CardAnimationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardAnimationWidget)
{
    ui->setupUi(this);

    qDebug() << "Before makeRequest()"; // Debug output
    QString photoUrl = "https://cdn.pixabay.com/photo/2023/02/06/00/21/scooter-7770871_1280.png";
    QUrl imageUrl(photoUrl);  // Replace with your image URL
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    // Send a GET request to download the image
    QNetworkReply* reply = manager->get(QNetworkRequest(imageUrl));

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Read the image data
            QByteArray imageData = reply->readAll();

            // Create a pixmap from the image data
            QPixmap pixmap;
            pixmap.loadFromData(imageData);

            // Set the pixmap as the QLabel's pixmap
            ui->label->setPixmap(pixmap);
            ui->label->setScaledContents(true);  // Scale the pixmap to fit the QLabel

            // Update the QLabel's size to match the pixmap size
            ui->label->setFixedSize(pixmap.size());
        } else {
            qDebug() << "Error loading image:" << reply->errorString();
        }

        // Clean up the network manager and reply objects
        reply->deleteLater();
        manager->deleteLater();
    });
    qDebug() << "After makeRequest()"; // Debug output
}

CardAnimationWidget::~CardAnimationWidget()
{
    delete ui;
}
