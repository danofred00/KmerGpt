#include "openai.h"
#include <exception>
#include <logger.h>
#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>
#include <QtConcurrent>

OpenAI::OpenAI(ILogger * logger, QObject *parent)
    : QObject{parent}, m_logger{logger}
{

}

OpenAI::~OpenAI() {

}

void OpenAI::init() {
    try{
        // init openai module
        auto config = readConfigFile("config.json");

        logger()->d("Services OpenAI Loading ...");

        openai::start(
            config.value("token").toString().toStdString(),
            config.value("organisation").toString().toStdString()
        );

        logger()->d("Services OpenAI Loading completed");

    } catch (const std::runtime_error & e){
        // log the error message
        logger()->e(e.what());
    }
}

QJsonObject OpenAI::readConfigFile(const QString & path)
{
    // create QFile with the path gived in arguments
    QFile file {path};
    QJsonObject jsonConfig;
    QJsonDocument jsonDoc;
    QJsonParseError error;

    if (file.exists()) {
        // open the file
        file.open(QIODevice::OpenModeFlag::ReadOnly);

        // read contents
        auto content = file.readAll();

        jsonDoc = QJsonDocument::fromJson(content, &error);

        if(error.error != QJsonParseError::NoError)
        {
            // if there's some error, we raised an exception
            throw std::runtime_error(QString("Could'nt Parse Document : %1").arg(error.errorString()).toStdString());
        }

        jsonConfig.insert("token", jsonDoc["token"]);
        jsonConfig.insert("organisation", jsonDoc["organisation"]);

        // close the config file
        file.close();
    } else {
        // if file not exists
        throw std::runtime_error(QString("Could'nt read config : Config file %1 not exists").arg(file.fileName()).toStdString());
    }

    return jsonConfig;
}

nlohmann::json OpenAI::openai_send(nlohmann::json text)
{
    return openai::chat().create(text);
}

void OpenAI::send(const QString & role, const QString & username, const QString & text)
{
    try {

        // create a basic request model
        auto json = R"({
            "model": "gpt-3.5-turbo",
            "messages": [{"role":"user", "content":"", "name":""}],
            "temperature": 0
        })"_json;
        // update text
        json["messages"][0]["content"] = text.toStdString();
        json["messages"][0]["name"] = username.toStdString();
        json["messages"][0]["role"] = role.toStdString();

        // update m_request
        m_request = ChatRequest(QString::fromStdString(nlohmann::to_string(json)).toLatin1());
        // emit send request signal
        emit requestSend(ChatRequest(m_request));
        // send the request
        QFuture<nlohmann::json> _response = QtConcurrent::run(&OpenAI::openai_send, json);
        _response.waitForFinished();
        // stringify the result
        auto response_toStr = nlohmann::to_string(_response.result());

        // update value of local vars
        m_response = ChatResponse(QByteArray::fromStdString(response_toStr));

        // emit response received
        emit responseReceived(m_response.toJson());

    } catch (const std::exception & e) {
        logger()->e(e.what());
    }
}
