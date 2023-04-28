#ifndef CHATREQUEST_H
#define CHATREQUEST_H

#include <QObject>

class Message : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString role READ getRole)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString content READ getContent)


public:
    inline Message(QObject *parent = nullptr):QObject(parent) {

    }
    inline Message(const Message & other) {
        *this = other;
    }

    inline Message & operator=(const Message & other){
        role = other.role;
        name = other.name;
        content = other.content;
        return *this;
    }

    inline QString getRole() const { return role; }
    inline QString getName() const { return name; }
    inline QString getContent() const { return content; }


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

    ChatRequest(QObject *parent = nullptr);
    ChatRequest(const QByteArray & json);
    ChatRequest(const ChatRequest & other);

    inline Message message() const { return m_message; }
    inline QString model() const { return m_model; }
    inline int n() const { return m_n; }
    inline float temperature() const { return m_temperature; }

    ChatRequest & operator=(const ChatRequest & other);

public slots:
    QByteArray toJson();

signals:

private:

    Message m_message;              // the message to resquest
    QString m_model;                // the id of the language model to user. ex : gpt-3.5-turbo
    int m_n = 1;                    // the number of response choices to Generate : default 1
    float m_temperature = 0;        // randomize output level


};

///
///
///

class ChatResponse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Message * message READ message_ptr)
    Q_PROPERTY(QString model READ model)
    Q_PROPERTY(QString object READ object)
    Q_PROPERTY(QString id READ id)
    Q_PROPERTY(QByteArray json READ toJson)

public:

    ChatResponse(QObject *parent = nullptr);
    ChatResponse(const QByteArray & json);
    ChatResponse(const ChatResponse & other);

    inline Message message() const { return m_message; }
    inline QString model() const { return m_model; }
    inline QString id() const { return m_id; }
    inline QString object() const { return m_object; }
    inline Message * message_ptr() { return &m_message; }

    ChatResponse & operator=(const ChatResponse & other);

public slots:
    QByteArray toJson();

signals:

private:

    Message m_message;              // the list of messages to resquest
    QString m_model;                // the id of the language model to user. ex : gpt-3.5-turbo
    QString m_id;                   // id of response
    QString m_object;               // the type of a response

};


#endif // CHATREQUEST_H
