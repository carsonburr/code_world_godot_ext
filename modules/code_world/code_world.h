/* code_world.h */
#ifndef CODE_WORLD_H
#define CODE_WORLD_H

#include "reference.h"
#include "Python.h"
#include <stdio.h>
#include <windows.h>

class Code_World : public Reference {
   GDCLASS(Code_World,Reference);
   
   bool initialized;
   PyObject* py_run_func;
   PyObject* py_module;

protected:
   static void _bind_methods();

public:
   bool init(String code);
   bool run();
   bool finalize();
   
   int get_output();

   Code_World();
};

#endif