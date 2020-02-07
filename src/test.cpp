#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

extern "C"
int hello()
{
    auto fileStream = std::make_shared<ostream>();

    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        // Create http_client to send the request.
        http_client client(U("http://time.jsontest.com"));
        http_request request(methods::GET);
        request.headers().add("Content-Type","json");

        // Build request URI and start the request.
        //uri_builder builder(U("/search"));
        //builder.append_query(U("q"), U("cpprestsdk github"));
        return client.request(request);
    })

    // Handle response headers arriving.
    .then([=](http_response response)
    {
        json::value json = response.extract_json().get();
        // auto a = json.at(U("data")).as_array();
        // for (uint i = 0; i < a.size(); i++)
        // {
        //     std::cout << a[i].at("email") << std::endl;
        // }
        std::cout << json.at(U("time")) << std::endl;
        

        // Write response body into the file.
        return response.body().read_to_end(fileStream->streambuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
        return fileStream->close();
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }

    return 0;
}