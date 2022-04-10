#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>

#include "httprequestworker.h"
#include "currencymodel.h"

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

    Q_INVOKABLE
    void showMsg();

    void initializeQmlContext(QGuiApplication *app, QQmlApplicationEngine *engine);

signals:
    void showTrayMessage(QString title, QString msg);

private slots:
    void handleResult(HttpRequestWorker *worker);

private:
    void parseCurrencyResponse(QByteArray apiResponse);

    HttpRequestWorker *_worker;
    QQmlApplicationEngine *_engine;
    QGuiApplication *_app;
    CurrencyModel _currencyModel;
};
