/* room_tile.h */
#ifndef ROOM_TILE_H
#define ROOM_TILE_H

#include "reference.h"

class Room_Tile : public Reference {
   OBJ_TYPE(Room_Tile,Reference);
   
   String img_res;
   int pos_x, pos_y;
   int type;
   // Entity ent;

protected:
   static void _bind_methods();

public:
   Room_Tile();
};

#endif