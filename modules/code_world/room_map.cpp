/* room_map.cpp */

#include "room_map.h"
#include "floor_map.h"
#include "room_tile.h"

#define RETURN_NULL_IF(X) if(X) return NULL;
#define RETURN_IF(X) if(X) return;

bool Room_Map::is_initialized() {
   return initialized;
}

Ref<Room_Tile> Room_Map::get_tile(int x, int y) {
   RETURN_NULL_IF(!is_initialized())
   if (x < 1 || x >= size_x-1) {
      if (y < ((int)(size_y/2))-1 || y > ((int)(size_y/2))+1) {
         return NULL;
      }
   }
   if (y < 1 || y >= size_y-1) {
      if (x < ((int)(size_x/2))-1 || x > ((int)(size_x/2))+1) {
         return NULL;
      }
   }
   
   Ref<Room_Tile> tile = tiles[x][y];
   
   if (tile == NULL) {
      tile = (Ref<Room_Tile>) memnew( Room_Tile );
      tile->init(Ref<Room_Map>(this), x, y);
      tile->get_room().unref();
      set_tile(tile, x, y);
      return tiles[x][y];
   }
   
   return tile;
}

void Room_Map::set_tile(Ref<Room_Tile> tile, int x, int y) {
   RETURN_IF(!is_initialized())
   RETURN_IF(x < 0 || y < 0 || x >= size_x || y >= size_y)
   tiles[x][y] = tile;
}

Ref<Floor_Map> Room_Map::get_floor() {
   RETURN_NULL_IF(!is_initialized())
   return floor;
}

int Room_Map::get_size_x() {
   RETURN_NULL_IF(!is_initialized())
   return size_x;
}

int Room_Map::get_size_y() {
   RETURN_NULL_IF(!is_initialized())
   return size_y;
}

int Room_Map::get_x() {
   RETURN_NULL_IF(!is_initialized())
   return x;
}

int Room_Map::get_y() {
   RETURN_NULL_IF(!is_initialized())
   return y;
}

bool Room_Map::get_door(int dir) {
   RETURN_NULL_IF(!is_initialized())
   RETURN_NULL_IF(dir < 0 || dir > 3)
   return doors[dir];
}

void Room_Map::set_doors(bool dup, bool ddown, bool dleft, bool dright) {
   this->doors[up] = dup;
   this->doors[down] = ddown;
   this->doors[left] = dleft;
   this->doors[right] = dright;
}

void Room_Map::init(Ref<Floor_Map> floor, int x, int y, int size_x, int size_y) {
   initialized = true;
   this->floor = floor;
   this->size_x = size_x;
   this->size_y = size_y;
   this->x = x;
   this->y = y;
   this->doors[up] = false;
   this->doors[down] = false;
   this->doors[left] = false;
   this->doors[right] = false;
   
   this->tiles = (Ref<Room_Tile>**) calloc(size_x, sizeof(Ref<Room_Tile>*));
   for (int x = 0; x < size_x; x++) {
      this->tiles[x] = (Ref<Room_Tile>*) calloc(size_y, sizeof(Ref<Room_Tile>));
   }
}

void Room_Map::uninit() {
   initialized = false;
   
   if (initialized) {
      for (int cx = 0; cx < size_x; ++cx) {
         for (int cy = 0; cy < size_y; ++cy) {
            tiles[cx][cy].unref();
         }
         free(tiles[cx]);
      }
      free(tiles);
   }
}

void Room_Map::_bind_methods() {
	ObjectTypeDB::bind_method("get_tile", &Room_Map::get_tile);
	ObjectTypeDB::bind_method("set_tile", &Room_Map::set_tile);
	ObjectTypeDB::bind_method("get_floor", &Room_Map::get_floor);
	ObjectTypeDB::bind_method("get_size_x", &Room_Map::get_size_x);
	ObjectTypeDB::bind_method("get_size_y", &Room_Map::get_size_y);
	ObjectTypeDB::bind_method("get_door", &Room_Map::get_door);
	ObjectTypeDB::bind_method("set_doors", &Room_Map::set_doors);
	ObjectTypeDB::bind_method("init", &Room_Map::init);
	ObjectTypeDB::bind_method("uninit", &Room_Map::uninit);
	ObjectTypeDB::bind_method("is_initialized", &Room_Map::is_initialized);
   BIND_CONSTANT(up);
   BIND_CONSTANT(down);
   BIND_CONSTANT(left);
   BIND_CONSTANT(right);
}

Room_Map::Room_Map() {
   initialized = false;
}

Room_Map::~Room_Map() {
   uninit();
}