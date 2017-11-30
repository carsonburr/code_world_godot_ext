/* room_tile.h */
#ifndef ROOM_TILE_H
#define ROOM_TILE_H

#include "reference.h"
class Entity;
class Room_Map;

class Room_Tile : public Reference {
   OBJ_TYPE(Room_Tile,Reference);
   
   Ref<Room_Map> room;
   int x, y;
   
   Ref<Entity> ent;

protected:
   static void _bind_methods();

public:
   Ref<Entity> get_entity();
   void set_entity(Ref<Entity> ent);
   int get_x();
   int get_y();
   Ref<Room_Map> get_room();
   
   Room_Tile(Ref<Room_Map> room, int x, int y);
   Room_Tile();
};

#endif