#include "helpers.h"
#include "DelimitedMessagesStreamParser.h"

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
    //

    google::protobuf::ShutdownProtobufLibrary();
    std::cout << "Shutdown Protobuf Library" << std::endl;

    for (auto& message : test_messages) {
        delete message;
    }

    return 0;
}
