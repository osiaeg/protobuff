/*
 * Test_Helpers.cpp
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */
#include <gtest/gtest.h>
#include "helpers.h"
using namespace Messages;

TEST(FastResponseTest, Message) {
    WrapperMessage* message = create_fast_response("19851019T050107.333");
    PointerToConstData res = serializeDelimited<WrapperMessage>(*message);
//    size_t sucssesBytes = 0;
    std::shared_ptr<WrapperMessage> parsed_message = parseDelimited<WrapperMessage>(&*res->begin(), res->size());

    EXPECT_EQ(message->fast_response().current_date_time(),
              parsed_message->fast_response().current_date_time());

    delete message;
}

TEST(SlowResponseTest, Message) {
    WrapperMessage* message = create_slow_response(10);
    PointerToConstData res = serializeDelimited<WrapperMessage>(*message);
 //   size_t sucssesBytes = 0;
    std::shared_ptr<WrapperMessage> parsed_message = parseDelimited<WrapperMessage>(&*res->begin(), res->size());

    EXPECT_EQ(message->slow_response().connected_client_count(),
              parsed_message->slow_response().connected_client_count());
    
    delete message;
}

TEST(RequesForSlowResponseTest, Message) {
    WrapperMessage* message = create_request_for_slow_response(1000);
    PointerToConstData res = serializeDelimited<WrapperMessage>(*message);
  //  size_t sucssesBytes = 0;
    std::shared_ptr<WrapperMessage> parsed_message = parseDelimited<WrapperMessage>(&*res->begin(), res->size());

    EXPECT_EQ(message->request_for_slow_response().time_in_seconds_to_sleep(),
              parsed_message->request_for_slow_response().time_in_seconds_to_sleep());

    delete message;
}

Messages::WrapperMessage* create_fast_response(std::string date) {
    Messages::WrapperMessage* message;

    try {
        message = new Messages::WrapperMessage();
    } catch (std::bad_alloc& ex) {
        std::cout << "Caught bad_alloc: " << ex.what() << std::endl;
    }

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

    message->mutable_request_for_slow_response()
            ->set_time_in_seconds_to_sleep(time);
    return message;
}
