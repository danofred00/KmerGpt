#ifndef CHATREQUEST_H
#define CHATREQUEST_H

#include <QObject>

struct Message {
    QString role;       // the role of the author : system | assistant | user
    QString content;    // the message content
    QString name;       // the name of the author of message
};

class ChatRequest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Message> messages READ messages)
    Q_PROPERTY(int n READ n)
    Q_PROPERTY(QString model READ model)
    Q_PROPERTY(float temperature READ temperature)

public:

    explicit ChatRequest(QObject *parent = nullptr);

    inline QList<Message> messages() const { return m_messages; }
    inline QString model() const { return m_model; }
    inline int n() const { return m_n; }
    inline float temperature() const { return m_temperature; }

public slots:
    static ChatRequest * fromJson(const QByteArray & json);
    QByteArray toJson();

signals:

private:

    QList<Message> m_messages;      // the list of messages to resquest
    QString m_model;            // the id of the language model to user. ex : gpt-3.5-turbo
    int m_n = 1;                    // the number of response choices to Generate : default 1
    float m_temperature = 0;        // randomize output level


};

#endif // CHATREQUEST_H
