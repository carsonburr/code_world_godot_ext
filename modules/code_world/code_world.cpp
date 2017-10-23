/* code_world.cpp */

#include "code_world.h"



/***********************
   Embedded Functions
***********************/

// test function. making sure python embedding works
static PyObject* cw_get_n_by_three(PyObject* self, PyObject *args) {
   PyObject* result = NULL;
   PyObject* py_n;
   if (PyArg_ParseTuple(args, "i:get_n_by_three", &py_n)) {
      long c_n = PyLong_AsLong(py_n);
      result = PyLong_FromLong(c_n*3);
   }
   return result;
}



/**********************
   Module Definition
**********************/

static PyMethodDef cw_methods[] = {
   {"get_n_by_three", cw_get_n_by_three, METH_VARARGS, "Return n times three"},
   {NULL, NULL, 0, NULL}
};

static PyModuleDef cw_module = {
   PyModuleDef_HEAD_INIT, "cw_emb", NULL, -1, cw_methods,
   NULL, NULL, NULL, NULL
};



/*********************
   Public Functions
*********************/

bool Code_World::init(String code) {
   const char* mod_name = "cw_ex";
   const char* cstr_code = code.c_str();
   PyObject* py_mod = PyModule_New(MyModuleName);
   
   // set properties of the new module object
   PyModule_AddStringConstant(py_mod, "__file__", "");
   PyObject* localDict = PyModule_GetDict(py_mod);
   PyObject* builtins = PyEval_GetBuiltins();
   PyDict_SetItemString(localDict, "__builtins__", builtins);
   
   // define code in the newly created module
   PyObject* pyValue = PyRun_String(cstr_code, Py_file_input, localDict, localDict);
   
}

bool Code_World::run() {
   char* cstr_code = code.c_str();
   Py_Initailize();
   PyRun_SimpleString(cstr_code);
   Py_FinalizeEx();
}