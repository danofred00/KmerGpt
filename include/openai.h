#ifndef OPENAI_H
#define OPENAI_H

#include <QObject>
#include <chatrequest.h>
#include <openai/openai.hpp>
#include <logger.h>

class OpenAI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ILogger * logger READ logger WRITE setLogger NOTIFY loggerChanged)
    Q_PROPERTY(ChatResponse * response READ response)
    Q_PROPERTY(ChatRequest * request READ request)

public:
    OpenAI(ILogger * logger, QObject *parent = nullptr);
    ~OpenAI();

    inline ILogger * logger() const { return m_logger; }
    inline void setLogger(ILogger * logger) {
        if (logger == m_logger)
            return;

        m_logger = logger;
        emit loggerChanged();
    }

    static nlohmann::json openai_send(nlohmann::json text);

public slots:
    void init();
    void send(const QString & role, const QString & username, const QString & text);
    inline ChatResponse * response() { return &m_response; }
    inline ChatRequest * request() { return &m_request; }

signals:
    void loggerChanged();
    void requestSend(const ChatRequest & request);
    void responseReceived(const QByteArray & jsonResponse);

private:

    QJsonObject readConfigFile(const QString & path = QString("config.json"));

    ILogger * m_logger;
    ChatResponse m_response;
    ChatRequest m_request;
};

#endif // OPENAI_H
