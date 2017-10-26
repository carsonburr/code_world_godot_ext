/* code_world.cpp */

#include "code_world.h"

long c_output;

/***********************
   Embedded Functions
***********************/

// test function. making sure python embedding works
static PyObject* cw_get_n_by_three(PyObject* self, PyObject* args) {
   PyObject* result = NULL;
   PyObject* py_n;
   if (PyArg_ParseTuple(args, "i:get_n_by_three", &py_n)) {
      long c_n = PyLong_AsLong(py_n);
      result = PyLong_FromLong(c_n*3);
   }
   return result;
}

static void cw_set_output(PyObject* self, PyObject* args) {
   PyObject* py_output;
   if (PyArg_ParseTuple(args, "i:set_output", &py_output)) {
      c_output = PyLong_AsLong(py_output);
   }
   return;
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



/**********************
   Private Functions
**********************/



/*********************
   Public Functions
*********************/

PyObject* py_run_func;
PyObject* py_module;

bool Code_World::init(String code) {
   
   // ***** temp init *****
   c_output = 0;
   
   PyImport_AppendInittab("cw_emb", &PyInit_cw_emb);
   
   Py_Initialize();
   
   PyObject* py_code = PyUnicode_FromString(code.ascii().get_data());
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
   
   return true;
}

bool Code_World::run() {
   PyObject_CallObject(py_run_func, NULL);
   
   if (PyErr_Occurred()) {
      PyErr_Print();
      return false;
   }
   
   return true;
}

bool Code_World::finalize() {
   Py_DECREF(py_run_func);
   Py_DECREF(py_module);
   Py_Finalize();
   return true;
}