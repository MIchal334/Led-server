#ifndef test_h
#define test_h

#include "Arduino.h"
#include <vector>

class Test {
public:
  Test(String name, std::vector<String> list);
  String getName();
  std::vector<String> getList();

private:
  String name;
  std::vector<String> list;
};

#endif
