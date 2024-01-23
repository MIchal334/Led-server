#include "Arduino.h"
#include "test.h"

Test::Test(String name, std::vector<String> list)
{
  this->name = name;
  this->list = list;
}

String Test::getName()
{
  return name;
}

std::vector<String> Test::getList()
{
  return list;
}