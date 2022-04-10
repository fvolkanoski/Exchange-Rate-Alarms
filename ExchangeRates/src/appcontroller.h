#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>

#include "httprequestworker.h"
#include "currencymodel.h"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainCurrency READ mainCurrency WRITE setMainCurrency NOTIFY mainCurrencyChanged)

public:
    explicit AppController(QObject *parent = nullptr);

    Q_INVOKABLE
    void showMsg();

    void initializeQmlContext(QGuiApplication *app, QQmlApplicationEngine *engine);

    const QString &mainCurrency() const;
    void setMainCurrency(const QString &newMainCurrency);

signals:
    void showTrayMessage(QString title, QString msg);

    void mainCurrencyChanged();

private slots:
    void handleResult(HttpRequestWorker *worker);

private:
    void parseCurrencyResponse(QByteArray apiResponse);

    HttpRequestWorker *_worker;
    QQmlApplicationEngine *_engine;
    QGuiApplication *_app;
    CurrencyModel _currencyModel;
    CurrencyModel _cbModel;
    QString m_mainCurrency = "AED";
};
