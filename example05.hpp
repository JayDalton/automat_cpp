#pragma once

#include "common.hpp"

// #include "scheduler.hpp"
#include "scheduler2.hpp"

namespace Example05
{

Task TaskA(Scheduler& sch) {
  std::cout << "Hello from TaskA\n";
  co_await sch.suspend();
  std::cout << "Executing the TaskA\n";
  co_await sch.suspend();
  std::cout << "TaskA is finished\n";
}

Task TaskB(Scheduler& sch) {
  std::cout << "Hello from TaskB\n";
  co_await sch.suspend();
  std::cout << "Executing the TaskB\n";
  co_await sch.suspend();
  std::cout << "TaskB is finished\n";
}

int main()
{
  Scheduler sch;

  sch.emplace(TaskA(sch).get_handle());
  sch.emplace(TaskB(sch).get_handle());

  std::cout << "Start scheduling...\n";

  sch.schedule();
  sch.wait();

  return 0;
}

}

