/*
 * DelimitedMessagesStreamParser.hpp
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */

#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

#include "helpers.h"
#include <list>


template <typename MessageType>
class DelimitedMessagesStreamParser {
 private:
  std::vector<char> m_buffer;

 public:
  typedef std::shared_ptr<const MessageType> PointerToConstValue;

  std::list<PointerToConstValue> parse(const std::string& data) {
    std::list<PointerToConstValue> list;
    m_buffer.push_back((char) data[0]);
    std::shared_ptr<MessageType> msg = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size());

    if (msg) {
      list.push_back(msg);
      m_buffer.clear();
    }
    return list;
  };
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */

