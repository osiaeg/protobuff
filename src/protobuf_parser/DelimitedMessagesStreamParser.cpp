#include "DelimitedMessagesStreamParser.h"

template<typename MessageType>
std::list<typename DelimitedMessagesStreamParser<MessageType>::PointerToConstValue> DelimitedMessagesStreamParser<MessageType>::parse(const std::string &data) {
    typedef std::shared_ptr<const MessageType> PointerToConstValue;
    std::list<PointerToConstValue> list;
    m_buffer.push_back((char) data[0]);
    std::shared_ptr<MessageType> msg = parseDelimited<MessageType>(m_buffer.data(), m_buffer.size());

    if (msg) {
        list.push_back(msg);
        m_buffer.clear();
    }

    return list;
}

template class DelimitedMessagesStreamParser<WrapperMessage>;
