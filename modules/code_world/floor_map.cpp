/* floor_map.cpp */

#include "floor_map.h"
#include "room_map.h"

#define RETURN_NULL_IF(X) if(X) return NULL;
#define RETURN_IF(X) if(X) return;

bool Floor_Map::is_initialized() {
   return initialized;
}

Ref<Room_Map> Floor_Map::get_room(int x, int y) {
   RETURN_NULL_IF(!is_initialized())
   if (x < 0 || y < 0 || x >= size_x || y >= size_y) {
      return NULL;
   }
   
   Ref<Room_Map> room = rooms[x][y];
   
   return room;
}

void Floor_Map::set_room(Ref<Room_Map> room, int x, int y) {
   RETURN_IF(!is_initialized())
   if (x < 0 || y < 0 || x >= size_x || y >= size_y) {
      return;
   }
   
   rooms[x][y] = room;
}

int Floor_Map::get_size_x() {
   RETURN_NULL_IF(!is_initialized())
   return size_x;
}

int Floor_Map::get_size_y() {
   RETURN_NULL_IF(!is_initialized())
   return size_y;
}

void Floor_Map::init(int size_x, int size_y) {
   initialized = true;
	this->size_x = size_x;
   this->size_y = size_y;
   
   this->rooms = (Ref<Room_Map>**) calloc(size_x, sizeof(Ref<Room_Map>*));
   for (int x = 0; x < size_x; x++) {
      this->rooms[x] = (Ref<Room_Map>*) calloc(size_y, sizeof(Ref<Room_Map>));
   }
}

void Floor_Map::_bind_methods() {
	ObjectTypeDB::bind_method("get_room", &Floor_Map::get_room);
	ObjectTypeDB::bind_method("set_room", &Floor_Map::set_room);
	ObjectTypeDB::bind_method("get_size_x", &Floor_Map::get_size_x);
	ObjectTypeDB::bind_method("get_size_y", &Floor_Map::get_size_y);
	ObjectTypeDB::bind_method("init", &Floor_Map::init);
	ObjectTypeDB::bind_method("is_initialized", &Floor_Map::is_initialized);
}

Floor_Map::Floor_Map() {
   initialized = false;
}