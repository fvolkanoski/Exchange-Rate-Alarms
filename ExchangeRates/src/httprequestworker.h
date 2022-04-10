#ifndef HTTPREQUESTWORKER_H
#define HTTPREQUESTWORKER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>


/* \brief Holds the enumeration for the variable layout.
 *
*/
enum HttpRequestVarLayout {
    NOT_SET,
    ADDRESS,
    URL_ENCODED,
    MULTIPART
};


/* \brief
 *
*/
class HttpRequestInputFileElement {

public:
    QString variable_name;
    QString local_filename;
    QString request_filename;
    QString mime_type;

};

/* \brief The request input class, holds the input parameters for the request.
 *
*/
class HttpRequestInput {

public:

    QString url_str;
    QString http_method;
    HttpRequestVarLayout var_layout;
    QMap<QString, QString> vars;
    QList<HttpRequestInputFileElement> files;

    /* \brief Default constructor for HttpRequestInput.
     *
    */
    HttpRequestInput();

    /* \brief URL and HTTP method constructor for HttpRequestInput
     *
     * @param v_url_str The url of the rest api.
     * @param v_http_method The http method.
    */
    HttpRequestInput(QString v_url_str, QString v_http_method);

    /* \brief Initialize the request.
     *
    */
    void initialize();

    /* \brief Add variable for the api request.
     *
     * @param key The key for the request.
     * @param value The value for the request.
    */
    void add_var(QString key, QString value);

    /* \brief Add file for the api request.
     *
     * @param variable_name The variable name.
     * @param local_filename The local file name.
     * @param request_filename The request file name.
     * @param mime_type Mime type.
    */
    void add_file(QString variable_name, QString local_filename, QString request_filename, QString mime_type);
};


class HttpRequestWorker : public QObject {
    Q_OBJECT

public:
    QByteArray response;
    QNetworkReply::NetworkError error_type;
    QString error_str;

    explicit HttpRequestWorker(QObject *parent = 0);

    /* \brief Encodes attribute to RFC 5987 or UTF-8.
     *
     * @param attribute_name The attribute name.
     * @param input Input.
    */
    QString http_attribute_encode(QString attribute_name, QString input);

    /* \brief Execute the api request.
     *
     * @param input The input class that was already formed before calling the execute process.
    */
    void execute(HttpRequestInput *input, bool auth = false);

signals:
    /* \brief This signal can be connected to a slot whenever needed,
     *        this signal is activated when the api request is finished.
     *
     * @param worker The HttpRequestWorker.
    */
    void on_execution_finished(HttpRequestWorker *worker);

private:
    QNetworkAccessManager *manager;

private slots:
    /* \brief This slot is called when finished signal of the QNetworkAccessManager is activated.
     *
     * @param reply The reply from the QNetworkAccessManager.
    */
    void on_manager_finished(QNetworkReply *reply);
};

#endif // HTTPREQUESTWORKER_H
