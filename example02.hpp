#pragma once

#include "common.hpp"

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

namespace Example02
{

namespace sc = boost::statechart;

struct EvStartStop : sc::event< EvStartStop > {};
struct EvReset : sc::event< EvReset > {};

struct IElapsedTime
{
  virtual double ElapsedTime() const = 0;
};

struct Active;
struct StopWatch : sc::state_machine< StopWatch, Active > 
{
  double ElapsedTime() const
  {
    return state_cast< const IElapsedTime & >().ElapsedTime();
  }
};

struct Stopped;

// Active is the outermost state and therefore needs to pass the
// state machine class it belongs to
struct Active : sc::simple_state< Active, StopWatch, Stopped > 
{
  using reactions = sc::transition< EvReset, Active >;

  double ElapsedTime() const { return elapsedTime_; }
  double & ElapsedTime() { return elapsedTime_; }

  private:
    double elapsedTime_{0.0};
};

// Stopped and Running both specify Active as their Context,
// which makes them nested inside Active
struct Running : IElapsedTime, sc::simple_state< Running, Active > 
{
  using reactions = sc::transition< EvStartStop, Stopped >;

    Running() {}
    ~Running()
    {
      context< Active >().ElapsedTime() = ElapsedTime();
    }

    double ElapsedTime() const override
    {
      return context< Active >().ElapsedTime() +
        std::difftime( std::time( 0 ), startTime_ );
    }
  private:
    std::time_t startTime_{0};
};

struct Stopped : IElapsedTime, sc::simple_state< Stopped, Active > 
{
  using reactions = sc::transition< EvStartStop, Running >;

  double ElapsedTime() const override
  {
    return context< Active >().ElapsedTime();
  }
};

int main()
{
  StopWatch myWatch;
  myWatch.initiate();
  print("{}\n", myWatch.ElapsedTime());
  myWatch.process_event( EvStartStop() );
  print("{}\n", myWatch.ElapsedTime());
  myWatch.process_event( EvStartStop() );
  print("{}\n", myWatch.ElapsedTime());
  myWatch.process_event( EvStartStop() );
  print("{}\n", myWatch.ElapsedTime());
  myWatch.process_event( EvReset() );
  print("{}\n", myWatch.ElapsedTime());
  return 0;
}

}

