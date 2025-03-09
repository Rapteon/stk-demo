#ifndef TERMINPUT_H
#define TERMINPUT_H

#include <random>
#include <thread>
#include <vector>

class TermInput {
public:
  TermInput();
  ~TermInput();
  struct CallbackInterface {
    virtual void hasEvent(char ch) = 0;
  };

  void registerCallback(CallbackInterface *callback);

  // Start reading input from the user using worker thread.
  void start();

  // Stop listening to char input.
  void stop();

private:
  std::thread thread;
  bool running;
  std::random_device rd; // obtain a random number from hardware
  std::mt19937_64 mersenne_twister{rd()};
  // ASCII codes for A till L
  std::uniform_int_distribution<> uniform_distribution {65, 78};

  void worker();
  void onEvent(char ch);
  char getRandomChar();
  std::vector<CallbackInterface *> registered_callbacks;
};
#endif
