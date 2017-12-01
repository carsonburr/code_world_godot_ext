/* room_tile.cpp */

#include "room_tile.h"
#include "entity.h"
#include "room_map.h"

#define RETURN_NULL_IF(X) if(X) return NULL;
#define RETURN_IF(X) if(X) return;

bool Room_Tile::is_initialized() {
   return initialized;
}

Ref<Entity> Room_Tile::get_entity() {
   RETURN_NULL_IF(!is_initialized())
   return ent;
}

void Room_Tile::set_entity(Ref<Entity> ent) {
   RETURN_IF(!is_initialized())
   this->ent = ent;
}

int Room_Tile::get_x() {
   RETURN_NULL_IF(!is_initialized())
   return x;
}

int Room_Tile::get_y() {
   RETURN_NULL_IF(!is_initialized())
   return y;
}

Ref<Room_Map> Room_Tile::get_room() {
   RETURN_NULL_IF(!is_initialized())
   return room;
}

void Room_Tile::init(Ref<Room_Map> room, int x, int y) {
   initialized = true;
	this->room = room;
   this->x = x;
   this->y = y;
}

void Room_Tile::_bind_methods() {
	ObjectTypeDB::bind_method("get_entity", &Room_Tile::get_entity);
	ObjectTypeDB::bind_method("set_entity", &Room_Tile::set_entity);
	ObjectTypeDB::bind_method("get_x", &Room_Tile::get_x);
	ObjectTypeDB::bind_method("get_y", &Room_Tile::get_y);
	ObjectTypeDB::bind_method("get_room", &Room_Tile::get_room);
	ObjectTypeDB::bind_method("init", &Room_Tile::init);
	ObjectTypeDB::bind_method("is_initialized", &Room_Tile::is_initialized);
}

Room_Tile::Room_Tile() {
   initialized = false;
}