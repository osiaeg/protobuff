#include "DelimitedMessagesStreamParser.h"

template<typename MessageType>
std::list<typename DelimitedMessagesStreamParser<MessageType>::PointerToConstValue>
DelimitedMessagesStreamParser<MessageType>::parse(const std::string &data) {
    typedef std::shared_ptr<const MessageType> PointerToConstValue;
    std::list<PointerToConstValue> list;
    for (auto& byte : data) {
        m_buffer.push_back(byte);
        size_t readedBytes{ 0 };
        std::shared_ptr<MessageType> msg = parseDelimited<MessageType>(&*m_buffer.begin(), m_buffer.size(), &readedBytes);
        if (readedBytes != 0 && msg) {
            list.push_back(msg);
            m_buffer.clear();
        }
    }

    return list;
}

template class DelimitedMessagesStreamParser<WrapperMessage>;
