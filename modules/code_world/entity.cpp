/* entity.cpp */

#include "entity.h"
#include "room_tile.h"
#include "room_map.h"

void Entity::set_tile(Ref<Room_Tile> tile) {
   this->tile = tile;
}

Ref<Room_Tile> Entity::get_tile() {
   return tile;
}

void Entity::set_node_path(NodePath node) {
   this->node = node;
}

NodePath Entity::get_node_path() {
   return node;
}

Ref<Room_Map> Entity::get_room() {
   return tile->get_room();
}

bool Entity::move_tile(int x, int y) {
   return move_tile_room(tile->get_room(), x, y);
}

bool Entity::move_tile_room(Ref<Room_Map> room, int x, int y) {
   Ref<Room_Tile> origin = tile;
   Ref<Room_Tile> destination = room->get_tile(x, y);
   
   if (origin == NULL || destination == NULL) return false;
   
   destination->set_entity(Ref<Entity>(this));
   origin->set_entity(NULL);
   tile = destination;
   
   return true;
}

bool Entity::move_tile_relative(int x, int y) { // move tile relative to current tile
   int ax = tile->get_x() + x;
   int ay = tile->get_y() + y;
   return move_tile(ax, ay);
}

void Entity::_bind_methods() {
	ObjectTypeDB::bind_method("get_tile", &Entity::get_tile);
	ObjectTypeDB::bind_method("set_tile", &Entity::set_tile);
	ObjectTypeDB::bind_method("get_node_path", &Entity::get_node_path);
	ObjectTypeDB::bind_method("set_node_path", &Entity::set_node_path);
	ObjectTypeDB::bind_method("get_room", &Entity::get_room);
	ObjectTypeDB::bind_method("move_tile", &Entity::move_tile);
	ObjectTypeDB::bind_method("move_tile_relative", &Entity::move_tile_relative);
	ObjectTypeDB::bind_method("move_tile_room", &Entity::move_tile_room);
}

Entity::Entity(NodePath node, Ref<Room_Tile> tile) {
   this->node = node;
   this->tile = tile;
}

Entity::Entity() {
	
}