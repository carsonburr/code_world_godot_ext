/* entity.h */
#ifndef ENTITY_H
#define ENTITY_H

#include "reference.h"
class Room_Tile;
class Room_Map;

class Entity : public Reference {
   OBJ_TYPE(Entity,Reference);
   bool initialized;
   
   NodePath node;
   Ref<Room_Tile> tile;

protected:
   static void _bind_methods();

public:
   bool is_initialized();
   void set_tile(Ref<Room_Tile> tile);
   Ref<Room_Tile> get_tile();
   void set_node_path(NodePath node);
   NodePath get_node_path();
   Ref<Room_Map> get_room();
   
   bool move_tile(int x, int y);
   bool move_tile_relative(int x, int y);
   bool move_tile_room(Ref<Room_Map> room, int x, int y);
   
   void init(NodePath node, Ref<Room_Tile> tile);
   Entity();
   ~Entity();
};

#endif