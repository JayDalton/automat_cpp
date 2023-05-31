#pragma once

#include "common.hpp"

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>

namespace Example01
{

namespace sc = boost::statechart;

// We need to forward-declare the initial state because it can
// only be defined at a point where the state machine is
// defined.
struct Greeting;

struct Machine : sc::state_machine<Machine, Greeting> {};

// For each state we need to define which state machine it
// belongs to and where it is located in the statechart. Both is
// specified with Context argument that is passed to
// simple_state<>. For a flat state machine as we have it here,
// the context is always the state machine. Consequently,
// Machine must be passed as the second template parameter to
// Greeting's base (the Context parameter is explained in more
// detail in the next example).
struct Greeting : sc::simple_state<Greeting, Machine>
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

}

