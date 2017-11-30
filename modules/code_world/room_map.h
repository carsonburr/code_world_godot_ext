/* room_map.h */
#ifndef ROOM_MAP_H
#define ROOM_MAP_H

#include "reference.h"
class Floor_Map;
class Room_Tile;

class Room_Map : public Reference {
   OBJ_TYPE(Room_Map,Reference);
   
   // used for directions of doors
   const int RIGHT = 0;
   const int UP = 1;
   const int LEFT = 2;
   const int DOWN = 3;
   
   Ref<Floor_Map> floor;
   Ref<Room_Map> doors[4];
   Ref<Room_Tile>** tiles;
   int size_x, size_y;
   

protected:
   static void _bind_methods();

public:
   Ref<Room_Tile> get_tile(int x, int y);
   void set_tile(Ref<Room_Tile> tile, int x, int y);
   Ref<Floor_Map> get_floor();
   void set_floor(Ref<Floor_Map> floor);
   Ref<Room_Map> get_door(int dir);
   void set_door(Ref<Room_Map> nroom, int dir);
   int get_size_x();
   int get_size_y();
   
   void connect(int dir, Ref<Room_Map> nroom);
   
   Room_Map(Ref<Floor_Map> floor, int size_x, int size_y);
   Room_Map();
};

#endif