/* room_map.h */
#ifndef ROOM_MAP_H
#define ROOM_MAP_H

#include "reference.h"

class Room_Map : public Reference {
   OBJ_TYPE(Room_Map,Reference);

protected:
   static void _bind_methods();

public:
   Room_Map();
};

#endif