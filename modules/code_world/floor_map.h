/* floor_map.h */
#ifndef FLOOR_MAP_H
#define FLOOR_MAP_H

#include "reference.h"
class Room_Map;

class Floor_Map : public Reference {
   OBJ_TYPE(Floor_Map,Reference);
   bool initialized;
   
   Ref<Room_Map>** rooms;
   int size_x, size_y;
   
   void set_room(Ref<Room_Map> room, int x, int y);

protected:
   static void _bind_methods();

public:
   bool is_initialized();
   Ref<Room_Map> get_room(int x, int y);
   int get_size_x();
   int get_size_y();
   
   void init(int size_x, int size_y);
   Floor_Map();
};

#endif