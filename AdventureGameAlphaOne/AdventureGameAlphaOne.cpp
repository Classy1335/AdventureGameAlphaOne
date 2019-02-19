// AdventureGameAlphaOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;


struct game_player {
public:
	string name;
	int bonus;
	long gold;
	bool isLiving=true;
	int rloc;
};

struct game_monster {
	string name;
	string description;
	bool isLiving=true;
	int difficulty;
};
/*I thought having dedicated structures to each monster, might be easier than only one monster structure. Maybe not though. I left them all in here as comments.

struct bat 
{
	string name;
	string description;
	bool isLiving = true;
	int difficulty = 6;
}
struct snake
{
	string name;
	string description;
	bool isLiving = true;
	int difficulty = 8;
};
struct goblin
{
	string name;
	string description;
	bool isLiving = true;
	int difficulty = 10
};
struct troll
{
	string name;
	string description;
	bool isLiving = true;;
	int difficulty = 12;
}
struct troll_king
{
	string name;
	string description;
	bool isLiving = true;
	int difficulty = 15;
}
*/

/* I also thought it might be helpful to have trap structures.
struct pit
{
	string name;
	string description;
	bool isActive = true;
	int difficulty = 6;
}
struct spikes
{
	string name;
	string description;
	bool isActive = true;
	int difficulty = 8;
}
struct darts
{
	string name;
	string description;
	bool isActive = true;
	int difficulty = 10;
}
struct poison_cloud
{
	string name;
	string description;
	bool isActive = true;
	int difficulty = 12;
}
	
*/
struct game_room {
	bool hasTraps, hasMonster, hasRelic, beenVisited;
	string name, description;
	game_monster monster;

	game_room() {
		name = description = "";
		hasTraps = hasMonster = hasRelic = beenVisited = false;
	}

	game_room(string name, string description, bool hasTraps, bool hasMonster, bool hasRelic) {
		this->name = name;
		this->description = description;
		this->hasTraps = hasTraps;
		this->hasMonster = hasMonster;
		this->hasRelic = hasRelic;
	}
};

enum game_commands {
	COMMAND_UNKNOWN = 0,
	COMMAND_CONTINUE,
	COMMAND_FIGHT,
	COMMAND_SEARCH,
	COMMAND_GO,
	COMMAND_DODGE,
	COMMAND_RUN,
	COMMAND_ESCAPE
};

enum game_locations {
	ENTRY = 0,
	HALLWAY,
	RED_1,
	RED_2,
	RED_3,
	RED_4,
	RED_5,
	RED_EXIT,
	GREEN_1,
	GREEN_2,
	GREEN_3,
	GREEN_4,
	GREEN_5,
	GREEN_EXIT,
	BLUE_1,
	BLUE_2,
	BLUE_3,
	BLUE_4,
	BLUE_5,
	BLUE_EXIT,
	YELLOW_1,
	YELLOW_2,
	YELLOW_3,
	YELLOW_4,
	YELLOW_5,
	YELLOW_EXIT,
	BOSS_ENTRY, 
	BOSS,
	EXIT
};
enum game_items {
	RED_KEY = 1,
	GREEN_KEY = 2,
	BLUE_KEY = 3,
	YELLOW_KEY = 4,
};
int choice;
int keys;

vector<string> delimit(const string &, char);
bool isMatch(string, string);
int determineAction(vector<string>);
vector<string> getInput();
void doContinue();
void doFight();
void initRooms();
int d20(int);

template<class T>
void find(string s, T & object) {
	if(object.cmd != 1) {
		cout << "Not equal to 1";
	}
};


const int GAME_ROOM_SIZE = EXIT+1;

int gameState;

game_player *player;
game_room *rooms;

int main()
{
	cout << "Would you like to play Adventure Game? ";
	cin >> choice;
	if (choice == 2)
		exit(0);
	else if (choice == 1)
		mainGame();
	return 0;
}
void mainGame() 
{
	srand(time(0));
	player = new game_player();
	initRooms();
	
	cout << "What is the player's name? ";
	cin >> player->name;
	player->bonus = 0;
	player->gold = 0;

	cout << player->name << ", you enter a cavern, as you walk inside, the entrance caves in behind you.";
	cout << "\nIn the dim torchlight you can make out five doors in front of you.";
	cout << "\nThe two doors to the left are Red and Green, the two doors to the right";
	cout << "\nare Blue and Yellow. In the center there is a large ornately decorated";
	cout << "\ndoor that appears to be made out of solid gold. What would you like to do first?";
	cout << "\nGo through the Red Door. Enter 1";
	cout << "\nGo through the Green Door. Enter 2";
	cout << "\nGo through the Blue Door. Enter 3";
	cout << "\nGo through the Yellow Door. Enter 4";
	cout << "\nGo through the Golden Door. Enter 5";
	cout << "\nWhere would you like to go, " << player->name << "? ";
	cin >> choice;
	switch (choice)
	{
		case 1:
		{
			cout << "You have chosen to go through the Red Door.";
			player->rloc = RED_1;
			//cin >> action
			break;
		}
		case 2:
		{
			cout << "You have chosen to go through the Green Door.";
			player->rloc = GREEN_1;
			//cin >> action
			break;
		}
		case 3:
		{
			cout << "You have chosen to go through the Blue Door.";
			player->rloc = BLUE_1;
			//cin >> action
			break;
		}
		case 4:
		{
			cout << "You have chosen to go through the Yellow Door.";
			player->rloc = YELLOW_1;
			//cin >> action;
			break;
		}
		case 5: 
		{
			/*If they have all the keys, I listed them as enumerators starting at 1, thinking that each time one is picked up add it's value
			to a variable called keys, and only if the total is the correct number (10) will they be able to go through the boss door.
			Otherwise it tells them they need the keys to unlock the door. it would look something like this.*/
			if (keys == 10)
			{
				cout << "You have chosen to go through the Golden Door.";
				player->rloc = BOSS_ENTRY;
				//cin >> action
			}
			else
			{
				cout << "As you approach the Golden Door, you notice it has four locks on it. The color ";
				cout << "\nof each lock matches one of the other doors in the room. Realizing that you must";
				cout << "\nfind the keys to unlock this door, you turn away. Which door will you enter first, " << player->name << "?";
				cin >> choice; // We also need to figure out how to get the program to run the switch again if they are not able to go into BOSS_ENTRY yet.
			}
				
		}
		
	}

	gameState = 1;
	string input;
	while(gameState!=0) {
		if (!player->isLiving) {
			cout << "You have died!" << endl;
			gameState = 0;
			continue;
		}
		vector<string> input = getInput();
		int action = determineAction(input);
		// identify target
		if (action && player->isLiving) {
			switch (action) {
				case COMMAND_CONTINUE:
					doContinue();
					break;
				case COMMAND_GO:
					break;
				case COMMAND_FIGHT:
					doFight();
					break;
				case COMMAND_RUN:
					break;
				case COMMAND_ESCAPE:
					break;
				case COMMAND_UNKNOWN:
					break;
				default:
					break;
			}
		}
	}
	delete [] rooms;
}

void doFight() {
	game_room *r = &rooms[player->rloc];
	game_monster *m = &r->monster;
	if(r->hasMonster && !m->isLiving) {
		cout << "But the " + m->name + "is already dead!";
	} else if (!r->hasMonster) {
		cout << "But there is nothing here!";
	} else {
		int pHit = d20(player->bonus);
		int mHit = d20(m->difficulty);
		if(pHit >= mHit) {
			cout << "The " + m->name + " crumbles to the ground lifelessly." << endl;
			m->isLiving = false;
		} else if(mHit > pHit) {
			cout << "The " + m->name + " lands a mighty blow that sends to ground." << endl;
			player->isLiving = false;
		}

	}
};

void doContinue() {
	game_room *r = &rooms[player->rloc];
	if(r->hasMonster && r->monster.isLiving) {
		cout << "You can't leave until you've vanquished the " + r->monster.name + "!";
	} else if(r->hasTraps) {
		cout << "The room is trapped! Are you trying to die?";
	} else {
		r->beenVisited = true;
		player->rloc++;
		r = &rooms[player->rloc];
		cout << "You continue on into the next area..." << endl;
		cout << r->name << endl;
		cout << r->description << endl;
		if (r->hasMonster) {
			cout << "You spot an enemy!" << endl;
		} else if (r->hasTraps) {
			cout << "You spot some traps!" << endl;
		}
	}
};


vector<string> getInput() {
	string input;
	cin >> input;
	cin.clear();
	cin.ignore(10000, '\n');
	return delimit(input, ' ');
};

vector<string> delimit(const string &toSplit, char delim) {
	vector<string> result;
	stringstream stringStream (toSplit);
	string item;

	while (getline(stringStream, item, delim)) {
		result.push_back(item);
	}

	return result;
}

int determineAction(vector<string> input) {
	string cmd, target;
	int cid;
	// identify command
	cmd = input.at(0);
	if(isMatch("fight", cmd)) {
		cid = COMMAND_FIGHT;
	} else if (isMatch("run", cmd)) {
		cid = COMMAND_RUN;
	} else if (isMatch("escape", cmd)) {
		cid = COMMAND_ESCAPE;
	} else if (isMatch("continue", cmd)) {
		cid = COMMAND_CONTINUE;
	} else {
		cout << "Unknown command";
		cid = COMMAND_UNKNOWN;
	}
	return cid;
};

bool isMatch(string src, string text) {
	int num = src.find(text, 0);
	if(num != -1 && num == 0) return true;
	return false;
};

void initRooms() {
	rooms = new game_room[GAME_ROOM_SIZE];
	for(int i=0;i < GAME_ROOM_SIZE; i++) {
		if(i != ENTRY && i != HALLWAY && i != RED_EXIT && i != GREEN_EXIT && i != BLUE_EXIT && i != YELLOW_EXIT && i != BOSS_ENTRY && i != EXIT) {
			rooms[i].hasTraps = rand() % 2;
			rooms[i].hasMonster = rand() % 2;
			rooms[i].hasRelic = rand() % 2;
		}
	}
	// neutral rooms
	rooms[HALLWAY].name = "Corridor, Chamber";
	rooms[RED_EXIT].name = "Red Door, Narrow Passage";
	rooms[RED_EXIT].description = "You're meandering through what seems an endless passage. Light is dim, and the only direction is forward.";
	rooms[GREEN_EXIT].name = "Green Corridor, Narrow Passage";
	rooms[GREEN_EXIT].description = "You're meandering through what seems an endless passage. Light is dim, and the only direction is forward.";
	rooms[BLUE_EXIT].name = "Blue Corridor, Narrow Passage";
	rooms[BLUE_EXIT].description = "You're meandering through what seems an endless passage. Light is dim, and the only direction is forward.";
	rooms[YELLOW_EXIT].name = "Yellow Corridor, Narrow Passage";
	rooms[YELLOW_EXIT].description = "You're meandering through what seems an endless passage. Light is dim, and the only direction is forward.";

	// populated rooms
};

int d20(int bias) {
	int roll = rand() % 20 + 1;
	roll += bias;
	(roll > 20 ? roll = 20 : 0);
	return roll;
}
