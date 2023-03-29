#include "helpers.h"
#include "DelimitedMessagesStreamParser.h"

Messages::WrapperMessage* create_fast_response(std::string date);
Messages::WrapperMessage* create_slow_response(unsigned count);
Messages::WrapperMessage* create_request_for_fast_response();
Messages::WrapperMessage* create_request_for_slow_response(unsigned long time);

int main(int argc, char* argv[]) {

    std::cout << "Program start" << std::endl;

    std::vector<char> messages;
    
    Messages::WrapperMessage* test_messages[4] {
        create_fast_response("19851019T050107.333"),
        create_slow_response(100),
        create_request_for_fast_response(),
        create_request_for_slow_response(1000)
    };

    for (int i = 0; i < 4; i++) {
        PointerToConstData res = serializeDelimited<Messages::WrapperMessage>(*test_messages[i]);
        for (auto& c : *res) {
            messages.push_back(c);
        }
    }
    // тут код заполнения messages с помощью  serializeDelimited

    typedef DelimitedMessagesStreamParser<Messages::WrapperMessage> Parser;
    Parser parser;

    // идем по одному байту по входному потоку сообщений
    for(const char byte : messages) {
        const std::list<std::shared_ptr<const Messages::WrapperMessage>>& parsedMessages = parser.parse(std::string(1, byte));
        for(const std::shared_ptr<const Messages::WrapperMessage>& value : parsedMessages) {
            std::cout << value->DebugString() << std::endl;
            // добавляем куда-то все сообщения
        }
    }
    // тут код проверки, что все сообщения расшифровались верно

    google::protobuf::ShutdownProtobufLibrary();
    std::cout << "Shutdown Protobuf Library" << std::endl;

    return 0;
}

Messages::WrapperMessage* create_fast_response(std::string date) {
    Messages::WrapperMessage* message;

    try {
        message = new Messages::WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    std::cout << "Create WrapperMessage with fast_response field." << std::endl;

    message->mutable_fast_response()
           ->set_current_date_time(date);
    return message;
}

Messages::WrapperMessage* create_slow_response(unsigned count) {
    Messages::WrapperMessage* message;

    try {
        message = new Messages::WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    std::cout << "Create WrapperMessage with slow_response field." << std::endl;

    message->mutable_slow_response()
           ->set_connected_client_count(count);
    return message;
}

Messages::WrapperMessage* create_request_for_fast_response() {
    Messages::WrapperMessage* message;
    try {
        message = new Messages::WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    std::cout << "Create WrapperMessage with request_for_fast_response field." << std::endl;

    *message->mutable_request_for_fast_response() = Messages::RequestForFastResponse();
    return message;
}

Messages::WrapperMessage* create_request_for_slow_response(unsigned long time) {
    Messages::WrapperMessage* message;
    try {
        message = new Messages::WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    std::cout << "Create WrapperMessage with request_for_slow_response field." << std::endl;

    message->mutable_request_for_slow_response()
           ->set_time_in_seconds_to_sleep(time);
    return message;
}
