/* entity.h */
#ifndef ENTITY_H
#define ENTITY_H

#include "reference.h"

class Entity : public Reference {
   OBJ_TYPE(Entity,Reference);

protected:
   static void _bind_methods();

public:
   Entity();
};

#endif