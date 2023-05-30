#include "console.h"

// cmake -A Win32 -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\Packages\scripts\buildsystems\vcpkg.cmake
// mkdir build && cd build && cmake .. && cmake --build . --config Release
// cmake --build .\build\ --config Release
// .\build\Release\features.exe
// rm -Recurse -Force .\build

// auto main() -> int
// {
//     if constexpr (std::endian::native == std::endian::little) {
//         print("This system is little endian\n\n");
//     } else if constexpr (std::endian::native == std::endian::big) {
//         print("This system is big endian\n\n");
//     }

//     Console app;
//     return app.run();
// }


// // $CXX -std=c++14 hello_world.cpp
// #include <boost/sml.hpp>
// #include <cassert>

// namespace sml = boost::sml;

// namespace {
// struct release {};
// struct ack {};
// struct fin {};
// struct timeout {};

// const auto is_ack_valid = [](const ack&) { return true; };
// const auto is_fin_valid = [](const fin&) { return true; };

// const auto send_fin = [] {};
// const auto send_ack = [] {};

// #if !defined(_MSC_VER)
// struct hello_world {
//   auto operator()() const {
//     using namespace sml;
//     return make_transition_table(
//       *"established"_s + event<release> / send_fin = "fin wait 1"_s,
//        "fin wait 1"_s + event<ack> [ is_ack_valid ] = "fin wait 2"_s,
//        "fin wait 2"_s + event<fin> [ is_fin_valid ] / send_ack = "timed wait"_s,
//        "timed wait"_s + event<timeout> / send_ack = X
//     );
//   }
// };
// }

// int main() {
//   using namespace sml;

//   sm<hello_world> sm;
//   static_assert(1 == sizeof(sm), "sizeof(sm) != 1b");
//   assert(sm.is("established"_s));

//   sm.process_event(release{});
//   assert(sm.is("fin wait 1"_s));

//   sm.process_event(ack{});
//   assert(sm.is("fin wait 2"_s));

//   sm.process_event(fin{});
//   assert(sm.is("timed wait"_s));

//   sm.process_event(timeout{});
//   assert(sm.is(X));  // released
// }
// #else
// class established;
// class fin_wait_1;
// class fin_wait_2;
// class timed_wait;

// struct hello_world {
//   auto operator()() const {
//     using namespace sml;
//     return make_transition_table(
//       *state<established> + event<release> / send_fin = state<fin_wait_1>,
//        state<fin_wait_1> + event<ack> [ is_ack_valid ] = state<fin_wait_2>,
//        state<fin_wait_2> + event<fin> [ is_fin_valid ] / send_ack = state<timed_wait>,
//        state<timed_wait> + event<timeout> / send_ack = X
//     );
//   }
// };
// }

// int main() {
//   using namespace sml;

//   sm<hello_world> sm;
//   assert(sm.is(state<established>));

//   sm.process_event(release{});
//   assert(sm.is(state<fin_wait_1>));

//   sm.process_event(ack{});
//   assert(sm.is(state<fin_wait_2>));

//   sm.process_event(fin{});
//   assert(sm.is(state<timed_wait>));

//   sm.process_event(timeout{});
//   assert(sm.is(X));  // released
// }
// #endif



#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

namespace sc = boost::statechart;

// We are declaring all types as structs only to avoid having to
// type public. If you don't mind doing so, you can just as well
// use class.

// We need to forward-declare the initial state because it can
// only be defined at a point where the state machine is
// defined.
struct Greeting;

// Boost.Statechart makes heavy use of the curiously recurring
// template pattern. The deriving class must always be passed as
// the first parameter to all base class templates.
//
// The state machine must be informed which state it has to
// enter when the machine is initiated. That's why Greeting is
// passed as the second template parameter.
struct Machine : sc::state_machine< Machine, Greeting > {};

// For each state we need to define which state machine it
// belongs to and where it is located in the statechart. Both is
// specified with Context argument that is passed to
// simple_state<>. For a flat state machine as we have it here,
// the context is always the state machine. Consequently,
// Machine must be passed as the second template parameter to
// Greeting's base (the Context parameter is explained in more
// detail in the next example).
struct Greeting : sc::simple_state< Greeting, Machine >
{
  // Whenever the state machine enters a state, it creates an
  // object of the corresponding state class. The object is then
  // kept alive as long as the machine remains in the state.
  // Finally, the object is destroyed when the state machine
  // exits the state. Therefore, a state entry action can be
  // defined by adding a constructor and a state exit action can
  // be defined by adding a destructor.
  Greeting() { std::cout << "Hello World!\n"; } // entry
  ~Greeting() { std::cout << "Bye Bye World!\n"; } // exit
};

int main()
{
  Machine myMachine;
  // The machine is not yet running after construction. We start
  // it by calling initiate(). This triggers the construction of
  // the initial state Greeting
  myMachine.initiate();
  // When we leave main(), myMachine is destructed what leads to
  // the destruction of all currently active states.
  return 0;
}