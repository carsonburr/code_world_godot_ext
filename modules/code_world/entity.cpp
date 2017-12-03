/* entity.cpp */

#include "entity.h"
#include "room_tile.h"
#include "room_map.h"

#define RETURN_NULL_IF(X) if(X) return NULL;
#define RETURN_IF(X) if(X) return;

bool Entity::is_initialized() {
   return initialized;
}

void Entity::set_tile(Ref<Room_Tile> tile) {
   RETURN_IF(!is_initialized())
   this->tile = tile;
}

Ref<Room_Tile> Entity::get_tile() {
   RETURN_NULL_IF(!is_initialized())
   return tile;
}

void Entity::set_node_path(NodePath node) {
   RETURN_IF(!is_initialized())
   this->node = node;
}

NodePath Entity::get_node_path() {
   if (!is_initialized()) return NodePath();
   return node;
}

Ref<Room_Map> Entity::get_room() {
   RETURN_NULL_IF(!is_initialized())
   return tile->get_room();
}

bool Entity::move_tile(int x, int y) {
   RETURN_NULL_IF(!is_initialized())
   return move_tile_room(tile->get_room(), x, y);
}

bool Entity::move_tile_room(Ref<Room_Map> room, int x, int y) {
   RETURN_NULL_IF(!is_initialized())
   Ref<Room_Tile> origin = tile;
   Ref<Room_Tile> destination = room->get_tile(x, y);
   
   if (origin == NULL || destination == NULL) return false;
   
   destination->set_entity(Ref<Entity>(this));
   origin->set_entity(NULL);
   set_tile(destination);
   
   return true;
}

bool Entity::move_tile_relative(int x, int y) { // move tile relative to current tile
   RETURN_NULL_IF(!is_initialized())
   int ax = tile->get_x() + x;
   int ay = tile->get_y() + y;
   return move_tile(ax, ay);
}

void Entity::init(NodePath node, Ref<Room_Tile> tile) {
   initialized = true;
   this->node = node;
   this->tile = tile;
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
	ObjectTypeDB::bind_method("init", &Entity::init);
	ObjectTypeDB::bind_method("is_initialized", &Entity::is_initialized);
}

Entity::Entity() {
   initialized = false;
}

Entity::~Entity() {
   
}