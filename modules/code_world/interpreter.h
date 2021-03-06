/* interpreter.h */
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "reference.h"
#include "Python.h"
#include <stdio.h>
#include <windows.h>
#include "entity.h"
#include "room_tile.h"
#include "room_map.h"
#include "floor_map.h"

class Interpreter : public Reference {
   OBJ_TYPE(Interpreter,Reference);
   
   bool initialized;
   PyObject* py_run_func;
   PyObject* py_module;

protected:
   static void _bind_methods();

public:
   
   #define INTERP_INPUTS I(up)I(down)I(left)I(right)I(use_arrow)
   #define I(x) x, 
   enum buttons : int {
      INTERP_INPUTS
      maxbutton
   };
   static bool inputs[maxbutton];
   static Ref<Entity> playerbot;
   static int test_output;
   
   bool is_initialized();
   
   bool init(String code, Ref<Entity> pb);
   bool run();
   bool finalize();
   
   bool is_button_pressed(int button);
   int get_test_output();
   void set_playerbot(Ref<Entity> pb);

   Interpreter();
   ~Interpreter();
};

#endif