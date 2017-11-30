/* floor_map.cpp */

#include "floor_map.h"
#include "room_map.h"

Ref<Room_Map> Floor_Map::get_room(int x, int y) {
   if (x < 0 || y < 0 || x > size_x || y > size_y) {
      return NULL;
   }
   
   Ref<Room_Map> room = rooms[x][y];
   
   if (room == NULL) {
      set_room( memnew( Room_Map( Ref<Floor_Map>(this), x, y ) ), x, y );
      return rooms[x][y];
   }
   
   return room;
}

void Floor_Map::set_room(Ref<Room_Map> room, int x, int y) {
   if (x < 0 || y < 0 || x > size_x || y > size_y) {
      return;
   }
   
   rooms[x][y] = room;
}

int Floor_Map::get_size_x() {
   return size_x;
}

int Floor_Map::get_size_y() {
   return size_y;
}

void Floor_Map::_bind_methods() {
	ObjectTypeDB::bind_method("get_room", &Floor_Map::get_room);
	ObjectTypeDB::bind_method("set_room", &Floor_Map::set_room);
	ObjectTypeDB::bind_method("get_size_x", &Floor_Map::get_size_x);
	ObjectTypeDB::bind_method("get_size_y", &Floor_Map::get_size_y);
}

Floor_Map::Floor_Map(int size_x, int size_y) {
	this->size_x = size_x;
   this->size_y = size_y;
   
   this->rooms = (Ref<Room_Map>**) calloc(size_x, sizeof(Ref<Room_Map>*));
   for (int x = 0; x < size_x; x++) {
      this->rooms[x] = (Ref<Room_Map>*) calloc(size_y, sizeof(Ref<Room_Map>));
   }
}

Floor_Map::Floor_Map() {
   
}