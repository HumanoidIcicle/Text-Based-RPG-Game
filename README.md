#   README: DUNGEONS NOT DRAGONS
## RUN INSTRUCTIONS:
- Go into "Project v1" directory.
- Then into the "cmake-build-debug" dir
- Inside is the .exe file to run to start playing.

*** Welcome to The Upside-Down! ***

Thrust into an unfamiliar world, you must use your wit and
skills to survive and fight monsters on you quest to get back
to the world you know.

## Game Description

The game consists of 6 rooms, with monsters and collectibles
scattered all throughout.

On start, the world is initialised and created by reading from
2 files.

### enCatalog.csv:
Holds all the items and enemies in the game.
- Item format-> category;name;type;id;
  e.g. ITEM;SWORD;weapon;5;damage
PS. Weapons have an extra field at the end specifying the damage they deal.

- Enemy format-> e.g. ENEMY;GOBLIN(skeleton or boss);hp=12,atk=4,def=1,hit=0.7,crit=0.2
  Designed to have only one boss level enemy.

### enRooms.csv:
Holds all the details about the rooms.
Format-> R1;room name;description;n;e;s;w;item1|item2;enemy1|enemy2

NB: Formats should be matched exactly, no spaces before or after the ";"
And the rooms.csv must contain 6 rooms.

### Menu Options
0 – View your status (HP, weapon, stats)

1 – Look around the current room (enemies, items, exits)

2 – Pick up items in the room

3 – Show your inventory

4 – Attack enemies in the room

5 – Equip a weapon using its ID

6 – Use a consumable using its ID

7 – Move to another room (enter n, e, s, or w)

8 – Help

9 – Exit the game

***To select an option, enter the corresponding number.***

### Gameplay Basics
- Explore rooms to find weapons, consumables, and keys
- Equip weapons to increase your attack power
- Use consumables to restore health
- Some rooms are locked and require specific keys
- Enemies attack back during combat, including bosses
- Defeat bosses to obtain special keys and progress

### Some game features
- For the first 3 player turns, a poison trap is activated.
- Player HP is displayed after each turn: Turn: 5 | HP 5 | #####
- The Boss has a two phase attack, becoming angrier when their HP
  reaches 60% and dealing more damage with every hit.

#### Game only ends on:
  - LOSS - if player hp is 0HP.
  - WIN - Player reaches the last room R6.