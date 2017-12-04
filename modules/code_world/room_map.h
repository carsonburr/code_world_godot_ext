/* room_map.h */
#ifndef ROOM_MAP_H
#define ROOM_MAP_H

#include "reference.h"
class Floor_Map;
class Room_Tile;

class Room_Map : public Reference {
   OBJ_TYPE(Room_Map,Reference);
   bool initialized;
   
   Ref<Floor_Map> floor;
   Ref<Room_Tile>** tiles;
   int size_x, size_y;
   int x, y;
   enum doordir : int {
      up,
      down,
      left,
      right
   };
   bool doors[4];
   
   void set_tile(Ref<Room_Tile> tile, int x, int y);

protected:
   static void _bind_methods();

public:
   bool is_initialized();
   Ref<Room_Tile> get_tile    (int x, int y);
   Ref<Floor_Map> get_floor   ();
   void           set_floor   (Ref<Floor_Map> floor);
   int            get_size_x  ();
   int            get_size_y  ();
   int            get_x       ();
   int            get_y       ();
   bool           get_door    (int dir);
   void           set_doors   (bool dup, bool ddown, bool dleft, bool dright);
   
   void           init        (Ref<Floor_Map> floor, int x, int y, int size_x, int size_y);
   Room_Map();
   ~Room_Map();
};

#endif