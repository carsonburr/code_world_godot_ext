/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"
#include "code_world.h"

void register_code_world_types() {

        ObjectTypeDB::register_type<Code_World>();
}

void unregister_code_world_types() {
   
}