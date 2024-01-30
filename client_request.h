#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H

#include "Arduino.h"


class ClientRequest {
private:
    int red_value;
    int blue_value;
    int green_value;
    int change_mode_id;

public:
  ClientRequest(int red_value, int blue_value,int green_value,int change_mode_id);
  int get_red_value();
  int get_blue_value();
  int get_green_value();
  int get_change_mode_id(); 
};

#endif