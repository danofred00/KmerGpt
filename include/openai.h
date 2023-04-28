#ifndef OPENAI_H
#define OPENAI_H

#include <QObject>
#include <chatrequest.h>
#include <openai/openai.hpp>
#include <logger.h>

#define TOKEN "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"
#define ORGANISATION "org-FUvuhvV04AZej9EerVzNud3O"

class OpenAI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ILogger * logger READ logger WRITE setLogger NOTIFY loggerChanged)
    Q_PROPERTY(ChatResponse response READ response)

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

public slots:
    void init();
    void send(const QString & text);
    inline ChatResponse response() const { return m_response; }

signals:
    void loggerChanged();
    void requestSend();
    void responseReceived(const QByteArray & jsonResponse);

private:
    ILogger * m_logger;
    ChatResponse m_response;
};

#endif // OPENAI_H
