#include "client_request.h"

ClientRequest::ClientRequest(int red_value, int blue_value, int green_value, int change_mode_id)
    : red_value(red_value), blue_value(blue_value), green_value(green_value), change_mode_id(change_mode_id) {}

int ClientRequest::get_red_value() {
  return red_value;
}

int ClientRequest::get_blue_value() {
  return blue_value;
}

int ClientRequest::get_green_value() {
  return green_value;
}

int ClientRequest::get_change_mode_id() {
  return change_mode_id;
}
