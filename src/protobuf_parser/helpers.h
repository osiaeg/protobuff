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

template <typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0);

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
PointerToConstData serializeDelimited(const Message& msg);

#endif /* SRC_PROTOBUF_PARSER_HELPERS_H_ */
