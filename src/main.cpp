#include "helpers.h"
#include "DelimitedMessagesStreamParser.h"

int main() {

    std::vector<char> messages;
    
    WrapperMessage* test_messages[4] {
        create_fast_response("19851019T050107.333"),
        create_slow_response(100),
        create_request_for_fast_response(),
        create_request_for_slow_response(1000)
    };

    for (auto & test_message : test_messages) {
        PointerToConstData res = serializeDelimited<WrapperMessage>(*test_message);
        for (auto& c : *res) {
            messages.push_back(c);
        }
    }

    typedef DelimitedMessagesStreamParser<WrapperMessage> Parser;
    Parser parser;

    std::list<std::vector<char>> packages;
    std::vector<char> package;
    for (int i = 0; i < messages.size(); i++) {
        if (i % 10 == 0) {
            packages.push_back(package);
            package.clear();
        }
        package.push_back(messages.at(i));
    }
    packages.push_back(package);
    
    for (auto pack : packages) {
        const std::list<std::shared_ptr<const WrapperMessage>>& parsedMessages = parser.parse(std::string(pack.begin(), pack.end()));
        for(const std::shared_ptr<const WrapperMessage>& parsedMessage : parsedMessages) {
            std::cout << parsedMessage->DebugString() << std::endl;
        }
    }

    google::protobuf::ShutdownProtobufLibrary();
    std::cout << "Shutdown Protobuf Library" << std::endl;

    for (auto& message : test_messages) {
        delete message;
    }

    return 0;
}

WrapperMessage* create_fast_response(std::string date) {
    WrapperMessage* message;

    try {
        message = new WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    message->mutable_fast_response()
            ->set_current_date_time(date);
    return message;
}

WrapperMessage* create_slow_response(unsigned count) {
    WrapperMessage* message;

    try {
        message = new WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    message->mutable_slow_response()
            ->set_connected_client_count(count);
    return message;
}

WrapperMessage* create_request_for_fast_response() {
    WrapperMessage* message;
    try {
        message = new WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    *message->mutable_request_for_fast_response() = Messages::RequestForFastResponse();
    return message;
}

WrapperMessage* create_request_for_slow_response(unsigned long time) {
    WrapperMessage* message;
    try {
        message = new WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    message->mutable_request_for_slow_response()
            ->set_time_in_seconds_to_sleep(time);
    return message;
}
