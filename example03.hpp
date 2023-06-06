#pragma once

#include "common.hpp"

#include <boost/asio.hpp>

namespace Example03
{
    void print(const boost::system::error_code& /*e*/)
    {
        std::cout << "Hello, world!" << std::endl;
    }

    int main()
    {
        boost::asio::io_context io;
        boost::asio::steady_timer t(io, boost::asio::chrono::seconds(3));

        // t.wait();

        t.async_wait(&print);
        io.run();

        std::cout << "Hello, world!" << std::endl;

        return 0;
    }

}
