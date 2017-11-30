/* room_tile.cpp */

#include "room_tile.h"
#include "entity.h"
#include "room_map.h"

Ref<Entity> Room_Tile::get_entity() {
   return ent;
}

void Room_Tile::set_entity(Ref<Entity> ent) {
   this->ent = ent;
}

int Room_Tile::get_x() {
   return x;
}

int Room_Tile::get_y() {
   return y;
}

Ref<Room_Map> Room_Tile::get_room() {
   return room;
}

void Room_Tile::_bind_methods() {
	ObjectTypeDB::bind_method("get_entity", &Room_Tile::get_entity);
	ObjectTypeDB::bind_method("set_entity", &Room_Tile::set_entity);
	ObjectTypeDB::bind_method("get_x", &Room_Tile::get_x);
	ObjectTypeDB::bind_method("get_y", &Room_Tile::get_y);
	ObjectTypeDB::bind_method("get_room", &Room_Tile::get_room);
}

Room_Tile::Room_Tile(Ref<Room_Map> room, int x, int y) {
	this->room = room;
   this->x = x;
   this->y = y;
}

Room_Tile::Room_Tile() {
   
}