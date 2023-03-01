#include <iostream>
#include <fstream>
#include "wrappermessage.pb.h"

Messages::WrapperMessage create_fast_response(std::string date);


int main(int argc, char* argv[]) {
    std::cout << std::endl;
    std::cout << "Program start" << std::endl;
    Messages::WrapperMessage response = create_fast_response("19851019T050107.333");
    std::cout << &response << std::endl;








    Messages::SlowResponse request;
    request.set_connected_client_count(10);
    std::cout <<
        "Connected client cout: " <<
        request.connected_client_count()
        << std::endl;
    google::protobuf::uint32 message_length = request.ByteSizeLong();
    std::cout << message_length << std::endl;


    
    google::protobuf::ShutdownProtobufLibrary();
    std::cout << "Shutdown Protobuf Library" << std::endl;
    return 0;
}

Messages::WrapperMessage create_fast_response(std::string date) {
    std::cout <<
        "Create WrapperMessage with fast_response field."
        << std::endl;
    Messages::WrapperMessage fast_response;

    Messages::FastResponse* field = fast_response.mutable_fast_response();
    field->set_current_date_time(date);
    return fast_response;
}

