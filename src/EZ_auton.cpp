#include "main.h"
#include "EZ_auton.hpp"

Auton::Auton() {
  Name = "";
  auton_call = nullptr;
}
Auton::Auton(std::string name, std::function<void()> callback) {
  Name = name;
  auton_call = callback;
}