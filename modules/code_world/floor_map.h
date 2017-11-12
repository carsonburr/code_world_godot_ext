/* floor_map.h */
#ifndef FLOOR_MAP_H
#define FLOOR_MAP_H

#include "reference.h"

class Floor_Map : public Reference {
   GDCLASS(Floor_Map,Reference);

protected:
   static void _bind_methods();

public:
   Floor_Map();
};

#endif