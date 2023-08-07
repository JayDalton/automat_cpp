#pragma once

#include "common.hpp"

#include "scheduler.hpp"
// #include "scheduler2.hpp"

namespace Example06
{

// task<int> suspend_none()
// {
//     std::printf("suspend_none\n");
//     co_return 0;
// }

// task<int> suspend_one()
// {
//     std::printf("suspend_one \\\n");
//     co_await std::suspend_always();
//     std::printf("suspend_one /\n");
//     co_return 1;
// }
// task<int> suspend_two()
// {
//     co_await suspend_none();
//     auto a = co_await suspend_one();
//     co_await suspend_none();
//     auto b = co_await suspend_one();
//     co_return a + b;
// }

// task<int> suspend_five()
// {
//     auto a = co_await suspend_two();
//     auto b = co_await suspend_two();
//     co_return 1 + a + b;
// }

Task TaskA1(Scheduler& sch) {
  std::cout << "Hello from TaskA-1\n";
  co_await sch.suspend();
  std::cout << "Executing the TaskA-1\n";
  co_await sch.suspend();
  std::cout << "TaskA-1 is finished\n";
}

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
  // sch.wait();

  return 0;
}

}

