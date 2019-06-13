#include "TimedPrint.h"

#include <thread>
#include <chrono>

int main()
{
  TimedPrint tp("Yo");

  std::this_thread::sleep_for(std::chrono::seconds(5));
}
