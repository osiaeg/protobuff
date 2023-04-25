#include "helpers.h"
using namespace google::protobuf::io;

template<typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed) {
/*!
 * \brief Расшифровывает сообщение, предваренное длиной из массива байтов.
 *
 * \tparam Message Тип сообщения, для работы с которым предназначена данная
 * функция.
 *
 * \param data Указатель на буфер данных.
 * \param size Размер буфера данных.
 * \param bytesConsumed Количество байт, которое потребовалось для расшифровки
 * сообщения в случае успеха.
 *
 * \return Умный указатель на сообщение. Если удалось расшифровать сообщение, то
 * он не пустой.
 */
    std::shared_ptr<Message> message {std::make_shared<Message>(Message())};
    uint32 message_size;

    CodedInputStream codedInput((uint8*)data, size);

    if (codedInput.ReadVarint32(&message_size)) {
        const size_t varintSize = CodedOutputStream::VarintSize32(message_size);
        const size_t totalFrameSize = varintSize + message_size;

        if (size >= totalFrameSize) {
            if (message->ParseFromCodedStream(&codedInput)) {
                if (bytesConsumed) {
                    *bytesConsumed = totalFrameSize;
                }
                return message;
            } else {
                std::cout << "Parsing failed" << std::endl;
                return nullptr;
            }
        } else {
            //std::cout << "Don't have enough bytes in buffer" << std::endl;
            return nullptr;
        }
    
    } else {
        std::cout << "Cant't raed varint" << std::endl;
        return nullptr;
    }
}

template <typename Message>
PointerToConstData serializeDelimited(const Message& msg) {
    //std::cout << "Run serializeDelimited()" << std::endl;

    const size_t messageSize = msg.ByteSizeLong();
    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);

    const PointerToData& result = std::make_shared<Data>(headerSize + messageSize);

    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());

    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
    msg.SerializeToArray(buffer + headerSize, messageSize);

    return result;
}

template PointerToConstData serializeDelimited(const WrapperMessage & msg);
template std::shared_ptr<WrapperMessage> parseDelimited(const void* data, size_t size, size_t* bytesConsumed);

Messages::WrapperMessage* create_fast_response(std::string date) {
    Messages::WrapperMessage* message;

    try {
        message = new Messages::WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

    //std::cout << "Create WrapperMessage with fast_response field." << std::endl;

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

    //std::cout << "Create WrapperMessage with slow_response field." << std::endl;

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

    //std::cout << "Create WrapperMessage with request_for_fast_response field." << std::endl;

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

    //std::cout << "Create WrapperMessage with request_for_slow_response field." << std::endl;

    message->mutable_request_for_slow_response()
           ->set_time_in_seconds_to_sleep(time);
    return message;
}
