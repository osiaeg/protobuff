/*
 * Test_DelimitedMessagesStreamParser.cpp
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */
#include <gtest/gtest.h>
#include "DelimitedMessagesStreamParser.h"

using namespace Messages;

TEST(StreamParser, List) {
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
    typedef DelimitedMessagesStreamParser<Messages::WrapperMessage> Parser;
    Parser parser;

    int i = 0;
    for(const char byte : messages) {
        const std::list<std::shared_ptr<const Messages::WrapperMessage>>& parsedMessages = parser.parse(std::string(1, byte));
        for(const std::shared_ptr<const Messages::WrapperMessage>& value : parsedMessages) {
            EXPECT_EQ(test_messages[i]->DebugString(),
                      value->DebugString());
            i++;
        }
    }
    
    google::protobuf::ShutdownProtobufLibrary();
    for (auto& message : test_messages) {
        delete message;
    }
}