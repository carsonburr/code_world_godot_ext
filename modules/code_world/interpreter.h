/* interpreter.h */
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "reference.h"
#include "Python.h"
#include <stdio.h>
#include <windows.h>

class Interpreter : public Reference {
   GDCLASS(Interpreter,Reference);
   
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

   Interpreter();
};

#endif