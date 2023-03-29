#include <iostream>
#include <vector>
#include <fstream>
//#include "wrappermessage.pb.h"
#include "helpers.h"
//#include "boost/make_shared.hpp"
#include <list>

using Data = std::vector<char>;
using PointerToConstData = std::shared_ptr<const Data>;
using PointerToData = std::shared_ptr<Data> ;

using uint8 = google::protobuf::uint8;
using uint32 = google::protobuf::uint32;

/*
template <typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0);
template <typename Message>
PointerToConstData serializeDelimited(const Message& msg);
*/

Messages::WrapperMessage* create_fast_response(std::string date);
Messages::WrapperMessage* create_slow_response(unsigned count);
Messages::WrapperMessage* create_request_for_fast_response();
Messages::WrapperMessage* create_request_for_slow_response(unsigned long time);
void check_message_field(Messages::WrapperMessage* message);

template<typename MessageType>
class DelimitedMessagesStreamParser {
    private:
        std::vector<char> m_buffer;

    public:
        typedef std::shared_ptr<const MessageType> PointerToConstValue;

        std::list<PointerToConstValue> parse(const std::string& data) {
            
            //std::cout << "Run parse()" << std::endl;
            std::list<PointerToConstValue> list;
            m_buffer.push_back((char) data[0]);
            std::shared_ptr<MessageType> msg = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size());

            if (msg) {
                list.push_back(msg);
                m_buffer.clear();
            }

            return list;
        }
};

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

/*
template<typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed) {
    //std::cout << "Run parseDelimited()" << std::endl;
    if (size == 1) {
        return nullptr;
    }

    std::shared_ptr<Message> message {std::make_shared<Message>(Message())};
    std::string message_data;
    uint32 message_size;

    google::protobuf::io::CodedInputStream codedInput((uint8*)data, size);

    codedInput.ReadVarint32(&message_size);
    codedInput.ReadString(&message_data, message_size);
    if (message->ParseFromString(message_data)) {
        return message;
    } else {
        return nullptr;
    }
}

template <typename Message> PointerToConstData serializeDelimited(const Message& msg) {
    //std::cout << "Run serializeDelimited()" << std::endl;

    const size_t messageSize = msg.ByteSizeLong();
    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);

    const PointerToData& result = std::make_shared<Data>(headerSize + messageSize);

    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());

    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
    msg.SerializeToArray(buffer + headerSize, messageSize);

    return result;
}
*/


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

