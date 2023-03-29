//#include "helpers.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include "wrappermessage.pb.h"

using Data = std::vector<char>;
using PointerToConstData = std::shared_ptr<const Data>;
using PointerToData = std::shared_ptr<Data>;
using uint8 = google::protobuf::uint8;
using uint32 = google::protobuf::uint32;

template<typename Message> std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed) {
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
