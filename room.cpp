// room (city) class

#include <iostream>
#include <cstring>
#include "room.h"

using namespace std;

room::room(char* newcity, int newid, int newnorth, int newsouth, int neweast, int newwest) {
  city = new char[14];
  strcpy(city, newcity);
  id = newid;
  north = newnorth;
  south = newsouth;
  east = neweast;
  west = newwest;
}

char* room::getcity() {
  return city;
}

int room::getid() {
  return id;
}

int room::getnorth() {
  return north;
}

int room::getsouth() {
  return south;
}

int room::geteast() {
  return east;
}

int room::getwest() {
  return west;
}
