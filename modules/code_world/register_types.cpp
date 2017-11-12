/* register_types.cpp */

#include "register_types.h"
#include "class_db.h"
#include "interpreter.h"
#include "room_map.h"
#include "room_tile.h"
#include "entity.h"
#include "floor_map.h"

void register_code_world_types() {
   
   ClassDB::register_class<Interpreter>();
   ClassDB::register_class<Room_Map>();
   ClassDB::register_class<Room_Tile>();
   ClassDB::register_class<Entity>();
   ClassDB::register_class<Floor_Map>();
}

void unregister_code_world_types() {
   
}