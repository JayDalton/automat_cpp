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

using clock = std::chrono::steady_clock;

struct IElapsedTime
{
  virtual double ElapsedTime() const = 0;
  virtual auto Duration() const -> clock::duration = 0;
};

struct Active;
struct StopWatch : sc::state_machine< StopWatch, Active > 
{
  double ElapsedTime() const
  {
    return state_cast< const IElapsedTime & >().ElapsedTime();
  }

  clock::duration Duration() const
  {
    return state_cast< const IElapsedTime & >().Duration();
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

  clock::duration Duration() const { return duration; }
  clock::duration & Duration() { return duration; }

  private:
    double elapsedTime_{0.0};
    clock::duration duration{0};
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
      context< Active >().Duration() = Duration();
    }

    double ElapsedTime() const override
    {
      return context< Active >().ElapsedTime() +
        std::difftime( std::time( 0 ), startTime_ );
    }

    auto Duration() const -> clock::duration override
    {
      return context< Active >().Duration() + (clock::now() - start);
    }

  private:
    std::time_t startTime_{0};
    clock::time_point start{ clock::now() };
};

struct Stopped : IElapsedTime, sc::simple_state< Stopped, Active > 
{
  using reactions = sc::transition< EvStartStop, Running >;

  double ElapsedTime() const override
  {
    return context< Active >().ElapsedTime();
  }

  auto Duration() const -> clock::duration override
  {
    return context< Active >().Duration();
  }
};

int main()
{
  StopWatch myWatch;
  myWatch.initiate();
  // print("{}\n", myWatch.ElapsedTime());
  print("{}\n", myWatch.Duration());
  myWatch.process_event( EvStartStop() );
  // print("{}\n", myWatch.ElapsedTime());
  print("{}\n", myWatch.Duration());
  myWatch.process_event( EvStartStop() );
  // print("{}\n", myWatch.ElapsedTime());
  print("{}\n", myWatch.Duration());
  myWatch.process_event( EvStartStop() );
  // print("{}\n", myWatch.ElapsedTime());
  print("{}\n", myWatch.Duration());
  myWatch.process_event( EvReset() );
  // print("{}\n", myWatch.ElapsedTime());
  print("{}\n", myWatch.Duration());
  return 0;
}

}

