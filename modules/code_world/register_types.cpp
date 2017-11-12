/* register_types.cpp */

#include "register_types.h"
#include "class_db.h"
#include "interpreter.h"

void register_code_world_types() {

        ClassDB::register_class<Interpreter>();
}

void unregister_code_world_types() {
   
}