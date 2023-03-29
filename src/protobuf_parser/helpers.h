/*
 * helpers.h
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */

#ifndef SRC_PROTOBUF_PARSER_HELPERS_H_
#define SRC_PROTOBUF_PARSER_HELPERS_H_

#include <iostream>
#include <vector>
#include <fstream>
#include "wrappermessage.pb.h"

using Data = std::vector<char>;
using PointerToData = std::shared_ptr<Data>;
using PointerToConstData = std::shared_ptr<const Data>;
using uint8 = google::protobuf::uint8;
using uint32 = google::protobuf::uint32;

template<typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0) {
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
#endif /* SRC_PROTOBUF_PARSER_HELPERS_H_ */
