/* Author: Suyash Pandit
December 16, 2021
This is a C++ implementation of the classic text based adventure game Zuul (with a slight twist) */

#include <vector>
#include <iostream>
#include <cstring>
#include <cctype>
#include "room.h"

using namespace std;

struct Item {
  char itemname[20];
  int location;
};

int main() {
  // introduction
  cout << "Welcome to Zuul: Europe edition!" << endl;
  cout << "You've spent the past two months exploring the wonders Europe has to offer. You were back in London, ready to finally head home. All was well." << endl;
  cout << "Suddenly, you realize you've lost all your important belongings. Without them, you'll never make it back home!" << endl;
  cout << "It's your job to navigate through 15 European cities in search of these items, or you may be stuck here for the foreseeable future..." << endl;
  char command[20];
  char name[20];
  char getdrop[20];
  int currentcity = 0; // start in London
  int nextcity = 0;
  int invsize = 0;
  bool empty = true;
  bool here = false;
  bool won = false;
  vector <room*> cities;
  vector <Item*> items;
  
  // set up cities

  strcpy(name, "London");
  room* london = new room(name, 0, 3, 9, 7, 1);
  strcpy(name, "Dublin");
  room* dublin = new room(name, 1, 2, -1, 0, -1);
  strcpy(name, "Reyjkavik");
  room* reykjavik = new room(name, 2, -1, 1, 3, -1);
  strcpy(name, "Bergen");
  room* bergen = new room(name, 3, -1, 0, 4, 2);
  strcpy(name, "Stockholm");
  room* stockholm = new room(name, 4, -1, 6, 5, 3);
  strcpy(name, "St.Petersburg");
  room* stpetersburg = new room(name, 5, -1, -1, -1, 4);
  strcpy(name, "Copenhagen");
  room* copenhagen = new room(name, 6, 4, 7, -1, -1);
  strcpy(name, "Amsterdam");
  room* amsterdam = new room(name, 7, 6, 8, -1, 0);
  strcpy(name, "Munich");
  room* munich = new room(name, 8, 7, 12, 14, 9);
  strcpy(name, "Paris");
  room* paris = new room(name, 9, 0, 10, 8, -1);
  strcpy(name, "Madrid");
  room* madrid = new room(name, 10, 9, -1, 11, -1);
  strcpy(name, "Rome");
  room* rome = new room(name, 11, 12, -1, 13, 10);
  strcpy(name, "Venice");
  room* venice = new room(name, 12, 8, 11, -1, -1);
  strcpy(name, "Athens");
  room* athens = new room(name, 13, 14, -1, -1, 11);
  strcpy(name, "Prague");
  room* prague = new room(name, 14, -1, 13, -1, 8);

  // add these cities to vector

  cities.push_back(london);
  cities.push_back(dublin);
  cities.push_back(reykjavik);
  cities.push_back(bergen);
  cities.push_back(stockholm);
  cities.push_back(stpetersburg);
  cities.push_back(copenhagen);
  cities.push_back(amsterdam);
  cities.push_back(munich);
  cities.push_back(paris);
  cities.push_back(madrid);
  cities.push_back(rome);
  cities.push_back(venice);
  cities.push_back(athens);
  cities.push_back(prague);

  // set up items

  Item* suitcase = new Item();
  strcpy(name, "suitcase");
  strcpy(suitcase->itemname, name);
  suitcase->location=5;
  items.push_back(suitcase);

  Item* note = new Item();
  strcpy(name, "note");
  strcpy(note->itemname, name);
  note->location = 14;
  items.push_back(note);

  Item* license = new Item();
  strcpy(name, "license");
  strcpy(license->itemname, name);
  license->location = 2;
  items.push_back(license);

  Item* passport = new Item();
  strcpy(name, "passport");
  strcpy(passport->itemname, name);
  passport->location = 10;
  items.push_back(passport);

  Item* book = new Item();
  strcpy(name, "book");
  strcpy(book->itemname, name);
  book->location = 12;
  items.push_back(book);
  
  while (true) {
    // continue until game ends
    cout << "\nYou are in " << cities[currentcity]->getcity() << endl;

    empty = true;

    // show items in room
    
    cout << "Items in this room: ";
    for (int i=0; i< items.size(); i++) {
      if (items[i]->location == currentcity and strcmp(items[i]->itemname,"passport")!=0) { // passport is a hidden item
	empty = false;
	cout << items[i]->itemname << " ";
      }
    }
    cout << endl;

    // show possible directions
    
    cout << "You can go: ";
    if (cities[currentcity]->getnorth()!=-1){
      cout << "north ";
    }
    if (cities[currentcity]->getsouth()!=-1){
      cout << "south ";
    }
    if (cities[currentcity]->geteast()!=-1){
      cout << "east ";
    }
    if (cities[currentcity]->getwest()!=-1){
      cout << "west ";
    }

    cout << "\nOr use one of these commands: get drop inventory read quit" << endl;

    while (true) {
      cin >> command;
      if (strcmp(command,"north")==0) {
        nextcity = cities[currentcity]->getnorth();
      }
      else if (strcmp(command,"south")==0) {
        nextcity = cities[currentcity]->getsouth();
      }
      else if (strcmp(command,"east")==0) {
        nextcity = cities[currentcity]->geteast();
      }
      else if (strcmp(command,"west")==0) {
        nextcity = cities[currentcity]->getwest();
      }
      else if (strcmp(command,"get")==0) {
	invsize = 0;
	for (int i=0; i<5; i++) {
	  if (items[i]->location==-1) {
	    invsize++;
	  }
	}
	if (invsize>=3) {
	  cout << "You can't carry more than 3 items. You must drop something before picking something else up!" << endl;
	}
	else {
	  here = false;
	  cout << "What item do you want to get? ";
	  cin >> getdrop;
	  for (int i=0; i<items.size(); i++) {
	    if (strcmp(items[i]->itemname,getdrop)==0 && items[i]->location==currentcity) { // check if item is available
	      here = true;
	      cout << "Getting " << items[i]->itemname << endl;
	      items[i]->location = -1;
	    }
  	  }

	  if (here == false) {
	    cout << "That item isn't in this city.";
	  }
	}
		
	continue;
      }
      else if (strcmp(command,"drop")==0) {
	here = false;
	cout << "What item do you want to drop? ";
	cin >> getdrop;
	for (int i=0; i<items.size(); i++) {
	  if (strcmp(items[i]->itemname,getdrop)==0 && items[i]->location==-1) {
	    here = true;
	    cout << "Dropping " << items[i]->itemname << endl;
	    items[i]->location = currentcity;
	  }
	}

	if (here == false) {
	  cout << "That item isn't in your inventory.";
	}
	
	continue;
      }
      else if (strcmp(command,"inventory")==0) {
        cout << "Items in your inventory: ";
        empty = true;
        for (int i=0; i<items.size(); i++) {
          if (items[i]->location == -1) {
            empty = false;
            cout << items[i]->itemname << " ";
          }
        }
        if (empty == true) {
          cout << "(none)";
        }
        cout << endl;
        empty = true;
	continue;
      }
      else if (strcmp(command,"read")==0) {
	cout << "What item do you want to read? ";
	cin >> getdrop;
	if (strcmp(getdrop,"note")==0 && items[1]->location==-1) {
	  // the spanish indicates a spanish speaking city (ie madrid)
	  cout << "Tu pasaporte esta escondido algun lado. Puedes advinar donde? Lo necesitas para ganar. Ve al lugar correcto, usa el comando \"get\" y escribe \"passport\". Buena suerte!" << endl;
	}
	else if (strcmp(getdrop,"book")==0 && items[4]->location==-1) {
	  // the book is a red herring
	  cout << "\nMr. and Mrs. Dursley, of number four, Privet Drive, were proud to say that they were perfectly normal, thank you very much." << endl;
	  cout << "They were the last people you'd expect to be involved in anything strange or mysterious, because they just didn't hold with such nonsense..." << endl;
	  cout << "What a waste of your time. Why are you reading Harry Potter???" << endl;
	}
	else {
	  cout << "You either don't have that item, or it cannot be read." << endl;
	}
	continue;
      }
      else if (strcmp(command,"quit")==0) {break;}
      else {cout << "Command not recognized." << endl; continue;}

      if (nextcity == -1) {
        cout << "You can't go in that direction." << endl;
      }
      else {
        currentcity = nextcity;
	if (items[0]->location == -1 && items[2]->location == -1 && items[3]->location == -1 && currentcity==0) {
	  won = true;
	}
	break;
      }

    }

    if (won == true) {
      cout << "Congratulations! You've made it back to London with everything you need. You can now safely return home." << endl;
      cout << "You've won Zuul: Europe Edition. Thanks for playing!" << endl;
      break;
    }

    if (strcmp(command,"quit")==0){
      cout << "Quitting Zuul: Europe Edition." << endl;
      break;
    }
    
  }
  return 0;
}
