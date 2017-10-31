/* code_world.cpp */

#include "code_world.h"

static int c_output;

/***********************
   Embedded Functions
***********************/

// test function. making sure python embedding works
static PyObject* cw_get_n_by_three(PyObject* self, PyObject* args) {
   int py_n;
   if (PyArg_ParseTuple(args, "i:get_n_by_three", &py_n)) {
      printf("py_n is %d", py_n);
      return PyLong_FromLong(py_n*3);
   }
   return NULL;
}

static PyObject* cw_set_output(PyObject* self, PyObject* args) {
   int py_output;
   if (PyArg_ParseTuple(args, "i:set_output", &py_output)) {
      c_output = py_output;
      Py_RETURN_TRUE;
   }
   return NULL;
}



/**********************
   Module Definition
**********************/

static PyMethodDef cw_methods[] = {
   {"get_n_by_three", cw_get_n_by_three, METH_VARARGS, "Return n times three"},
   {"set_output", cw_set_output, METH_VARARGS, "Set a variable within C++"},
   {NULL, NULL, 0, NULL}
};

static PyModuleDef cw_module = {
   PyModuleDef_HEAD_INIT, "cw_emb", NULL, -1, cw_methods,
   NULL, NULL, NULL, NULL
};

static PyObject* PyInit_cw_emb() {
   return PyModule_Create(&cw_module);
}



/*********************
   Public Functions
*********************/

bool Code_World::init(String code) {
   
   // ***** temp init *****
   c_output = 0;
   
   // save file from code
   FILE* py_file = fopen("user_code.py", "w");
   fputs(code.ascii().get_data(), py_file);
   fclose(py_file);
   
   // import C++ module
   PyImport_AppendInittab("cw_emb", &PyInit_cw_emb);
   
   Py_Initialize();
   
   PyRun_SimpleString("import sys\n"
                      "sys.path.append(\".\")");
   
   // import user module
   PyObject* py_code = PyUnicode_DecodeFSDefault("user_code");
   py_module = PyImport_Import(py_code);
   Py_DECREF(py_code);
   
   if (py_module == NULL) {
      PyErr_Print();
      // handle error
      return false;
   }
   
   py_run_func = PyObject_GetAttrString(py_module, "run");
   
   if (!py_run_func || !PyCallable_Check(py_run_func)) {
      if (PyErr_Occurred()) {
         PyErr_Print();
      }
      // handle error
      Py_XDECREF(py_run_func);
      Py_DECREF(py_module);
      return false;
   }
   initialized = true;
   return true;
}

bool Code_World::run() {
   if (!initialized) {
      // handle error
      return false;
   }
   
   PyObject_CallObject(py_run_func, NULL);
   
   if (PyErr_Occurred()) {
      PyErr_Print();
      return false;
   }
   
   return true;
}

bool Code_World::finalize() {
   if (!initialized) {
      //handle error
      return false;
   }
   
   Py_DECREF(py_run_func);
   Py_DECREF(py_module);
   Py_Finalize();
   initialized = false;
   return true;
}

int Code_World::get_output() {
   return c_output;
}

void Code_World::_bind_methods() {
   ClassDB::bind_method("init", &Code_World::init);
   ClassDB::bind_method("run", &Code_World::run);
   ClassDB::bind_method("finalize", &Code_World::finalize);
   ClassDB::bind_method("get_output", &Code_World::get_output);
}

Code_World::Code_World() {
   // ***** temp init *****
   c_output = 0;
   
   initialized = false;
}