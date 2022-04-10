#pragma once

#include <QObject>

#include "httprequestworker.h"

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

    Q_INVOKABLE void showMsg();

signals:
    void showTrayMessage(QString title, QString msg);

private slots:
    void handleResult(HttpRequestWorker *worker);

private:
    void parseCurrencyResponse(QByteArray apiResponse);

    HttpRequestWorker *_worker;
};
