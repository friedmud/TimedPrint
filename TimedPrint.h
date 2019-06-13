//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include <chrono>
#include <iostream>
#include <thread>

/**
 * Object to print a message after enough time has passed.
 * Should help when there is a long running process.
 * It will wait to print a message, then it will start
 * print dots.
 *
 * Use it as a scope guard.  As long as it is alive it
 * will print out periodically
 */
class TimedPrint final {
public:
  /**
   * Start the timing and printing
   *
   * @param message The message to print out
   * @param initial_wait The amount of time (in seconds) to wait before printing
   * message
   * @param dot_interval The amount of time (in seconds) to wait before printing
   * each dot
   */
  TimedPrint(const std::string &message,
             std::chrono::seconds initial_wait = std::chrono::seconds(1),
             std::chrono::seconds dot_interval = std::chrono::seconds(1))
      : _done(false) {

    // This is using move assignment
    _thread = std::thread{[message, initial_wait, dot_interval, this] {
      std::this_thread::sleep_for(initial_wait);

      if (!_done)
        std::cout << message << std::flush;

      while (!this->_done) {
        std::this_thread::sleep_for(dot_interval);
        std::cout << "." << std::flush;
      }
    }};
  }

  ~TimedPrint() {
    // Tell the thread to end
    _done = true;

    // Wait for it to end
    _thread.join();

    // Finish the line
    std::cout << std::endl;
  }

protected:
  bool _done;
  std::thread _thread;
};
