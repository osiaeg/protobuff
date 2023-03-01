#include <iostream>
#include "wrappermessage.pb.h"

Messages::WrapperMessage* fast_response();


int main() {
    Messages::SlowResponse request;
    request.set_connected_client_count(10);
    std::cout << request.connected_client_count() << std::endl;
    google::protobuf::uint32 message_length = request.ByteSizeLong();
    std::cout << message_length << std::endl;


    
    std::cout << "message generated." << std::endl;
    fast_response();
}

Messages::WrapperMessage* fast_response() {
    Messages::WrapperMessage* message;
    Messages::FastResponse* link;

    link = message->mutable_fast_response();
    std::cout << link << std::endl;

    return message;
}
