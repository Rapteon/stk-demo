#include "TermInput.h"
#include <iostream>

TermInput::TermInput() : running{false} {
  std::cout << "Initialised TermInput.\n";
}

TermInput::~TermInput() { stop(); }

void TermInput::registerCallback(CallbackInterface *callback) {
  registered_callbacks.push_back(callback);
}

void TermInput::onEvent(char ch) {
  for (auto &cb : registered_callbacks) {
    cb->hasEvent(ch);
  }
}

void TermInput::start() {
  // Can do any other initialisations, if required.
  running = true;
  thread = std::thread(&TermInput::worker, this);
}
void TermInput::stop() {
  if (!running)
    return;
  running = false;
  thread.join();
  // Other cleanup operations, if required.
}

char TermInput::getRandomChar() {
    return static_cast<char>(uniform_distribution(mersenne_twister));
}
void TermInput::worker() {
  while (running) {
    char ch {getRandomChar()};
    std::cout << ch << '\n';
    onEvent(ch);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
