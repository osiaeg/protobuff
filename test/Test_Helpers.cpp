/*
 * Test_Helpers.cpp
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */
#include <gtest/gtest.h>
#include "helpers.h"


TEST(ParseDelimitedTest, Message) {
    Messages::WrapperMessage* message = create_fast_response("19851019T050107.333");
    PointerToConstData res = serializeDelimited<Messages::WrapperMessage>(*message);
    std::shared_ptr<Messages::WrapperMessage> parsed_message = parseDelimited<Messages::WrapperMessage>(&*res->begin(), res->size());

    EXPECT_EQ(message->fast_response().current_date_time(),
              parsed_message->fast_response().current_date_time());
    
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
