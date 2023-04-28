#include "openai.h"
#include <exception>
#include <logger.h>

OpenAI::OpenAI(ILogger * logger, QObject *parent)
    : QObject{parent}, m_logger{logger}
{

}

OpenAI::~OpenAI() {

}

void OpenAI::init() {
    try{
        // init openai module
        openai::start(TOKEN, ORGANISATION);
    } catch (const std::runtime_error & e){
        // log the error message
        logger()->e(e.what());
    }
}

void OpenAI::send(const QString &text)
{
    try {

        // create a basic request model
        auto json = R"({
            "model": "gpt-3.5-turbo",
            "messages": [{"role":"user", "content":""}],
            "temperature": 0
        })"_json;
        // update text
        json["messages"][0]["content"] = text.toStdString();

        // emit send request signal
        emit requestSend();
        // send the request
        auto _response = openai::chat().create(json);
        auto response_toStr = nlohmann::to_string(_response);

        // update value of local vars
        m_response = ChatResponse(QByteArray::fromStdString(response_toStr));

        // emit response received
        emit responseReceived(m_response.toJson());


    } catch (const std::exception & e) {
        logger()->e(e.what());
    }
}
