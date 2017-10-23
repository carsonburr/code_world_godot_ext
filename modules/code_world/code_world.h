/* code_world.h */
#ifndef CODE_WORLD_H
#define CODE_WORLD_H

#include "reference.h"
#include "ustring.h"
#include "Python.h"

class Code_World : public Reference {
    OBJ_TYPE(Code_World,Reference);

    String test_str;

protected:
    static void _bind_methods();

public:
    bool init(String code);
    bool run();
    bool finalize();
    
    String get_str();

    Code_World();
};

#endif