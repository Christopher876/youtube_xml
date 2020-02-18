#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>

extern "C"
char* test_ip(){
    std::string test_string;
    web::http::client::http_client client(U("http://ip.jsontest.com/"));
    client.request(web::http::methods::GET).then([&test_string](web::http::http_response response){
        test_string = response.extract_string().get();
    })
    .wait();

    const std::string::size_type size = test_string.size();
    char *buffer = new char[size + 1];   //we need extra char for NUL
    memcpy(buffer, test_string.c_str(), size + 1);

    std::cout << "Hello from C++: " << buffer << std::endl;
    return buffer;
}

extern "C"
int hello(char* url)
{
    std::string s;
    web::http::client::http_client client(U(url));
    auto response = client.request(web::http::methods::GET).then([&s](web::http::http_response response){
        s = response.extract_string().get();
    })
    .wait();
    std::cout << s << std::endl;
    return 0;
}