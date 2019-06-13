#include "TimedPrint.h"

#include <thread>
#include <chrono>

int main()
{
  TimedPrint tp("Yo", std::chrono::duration<double>(0.2), std::chrono::duration<double>(0.4));

  std::this_thread::sleep_for(std::chrono::duration<double>(5));
}
