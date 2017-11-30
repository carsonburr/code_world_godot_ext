/* room_map.cpp */

#include "room_map.h"
#include "floor_map.h"
#include "room_tile.h"

Ref<Room_Tile> Room_Map::get_tile(int x, int y) {
   if (x < 0 || y < 0 || x > size_x || y > size_y) {
      return NULL;
   }
   
   Ref<Room_Tile> tile = tiles[x][y];
   
   if (tile == NULL) {
      set_tile( memnew( Room_Tile( Ref<Room_Map>(this), x, y ) ), x, y );
      return tiles[x][y];
   }
   
   return tile;
}

void Room_Map::set_tile(Ref<Room_Tile> tile, int x, int y) {
   if (x < 0 || y < 0 || x > size_x || y > size_y) {
      return;
   }
   
   tiles[x][y] = tile;
}

Ref<Floor_Map> Room_Map::get_floor() {
   return floor;
}

void Room_Map::set_floor(Ref<Floor_Map> floor) {
   this->floor = floor;
}

Ref<Room_Map> Room_Map::get_door(int dir) {
   if (dir < 0 || dir > 3) {
      return NULL;
   }
   return doors[dir];
}

void Room_Map::set_door(Ref<Room_Map> nroom, int dir) {
   if (dir < 0 || dir > 3) {
      return;
   }
   doors[dir] = nroom;
}

int Room_Map::get_size_x() {
   return size_x;
}

int Room_Map::get_size_y() {
   return size_y;
}

void Room_Map::connect(int dir, Ref<Room_Map> nroom) {
   if (dir < 0 || dir > 3) {
      return;
   }
   set_door(nroom, dir);
   nroom->set_door( Ref<Room_Map>(this), (dir+2)%4 );
}

void Room_Map::_bind_methods() {
	ObjectTypeDB::bind_method("get_tile", &Room_Map::get_tile);
	ObjectTypeDB::bind_method("set_tile", &Room_Map::set_tile);
	ObjectTypeDB::bind_method("get_floor", &Room_Map::get_floor);
	ObjectTypeDB::bind_method("set_floor", &Room_Map::set_floor);
	ObjectTypeDB::bind_method("get_door", &Room_Map::get_door);
	ObjectTypeDB::bind_method("set_door", &Room_Map::set_door);
	ObjectTypeDB::bind_method("get_size_x", &Room_Map::get_size_x);
	ObjectTypeDB::bind_method("get_size_y", &Room_Map::get_size_y);
}

Room_Map::Room_Map(Ref<Floor_Map> floor, int size_x, int size_y) {
   this->floor = floor;
   this->size_x = size_x;
   this->size_y = size_y;
   
   this->tiles = (Ref<Room_Tile>**) calloc(size_x, sizeof(Ref<Room_Tile>*));
   for (int x = 0; x < size_x; x++) {
      this->tiles[x] = (Ref<Room_Tile>*) calloc(size_y, sizeof(Ref<Room_Tile>));
   }
}

Room_Map::Room_Map() {
   this->size_x = 11;
   this->size_y = 11;
   
   this->tiles = (Ref<Room_Tile>**) calloc(size_x, sizeof(Ref<Room_Tile>*));
   for (int x = 0; x < size_x; x++) {
      this->tiles[x] = (Ref<Room_Tile>*) calloc(size_y, sizeof(Ref<Room_Tile>));
   }
}