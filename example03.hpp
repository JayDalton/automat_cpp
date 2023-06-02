#pragma once

#include "common.hpp"

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

#include <boost/asio.hpp>

namespace Example03
{

    int main()
    {
        boost::asio::io_context io;
        boost::asio::steady_timer t(io, boost::asio::chrono::seconds(3));

        t.wait();

        std::cout << "Hello, world!" << std::endl;

        return 0;
    }

}
