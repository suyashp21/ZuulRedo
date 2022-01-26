// Room (city) class

#include <iostream>
#include <cstring>

using namespace std;

class room {
 public:
  room(char*, int, int, int, int, int);
  char* getcity();
  int getid();
  // directions used to see what cities are in each direction
  int getnorth();
  int getsouth();
  int geteast();
  int getwest();
 protected:
  char* city;
  int id;
  int north;
  int south;
  int east;
  int west;
};
