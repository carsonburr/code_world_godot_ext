/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"
#include "interpreter.h"
#include "room_map.h"
#include "room_tile.h"
#include "entity.h"
#include "floor_map.h"

void register_code_world_types() {
   
   ObjectTypeDB::register_type<Interpreter>();
   ObjectTypeDB::register_type<Room_Map>();
   ObjectTypeDB::register_type<Room_Tile>();
   ObjectTypeDB::register_type<Entity>();
   ObjectTypeDB::register_type<Floor_Map>();
}

void unregister_code_world_types() {
   
}