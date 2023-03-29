#include "DelimitedMessagesStreamParser.h"
#include "helpers.h"

template <typename MessageType>
DelimitedMessagesStreamParser<MessageType>::parse( const std::string& data) {
    std::list<PointerToConstValue> list;
    m_buffer.push_back((char) data[0]);
    std::shared_ptr<Message_type> msg = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size());

    if (msg) {
      list.push_back(msg);
      m_buffer.clear();
    }
}
