/* interpreter.cpp */

#include "interpreter.h"

#undef I
#define I(x) false, 
bool Interpreter::inputs[maxbutton] = { INTERP_INPUTS };
Ref<Entity> Interpreter::playerbot = NULL;
int Interpreter::test_output = -1;
/***********************
   Embedded Functions
***********************/
static PyObject* cw_press_left(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":press_left")) {
      return NULL;
   }
   Interpreter::inputs[Interpreter::left] = true;
   Py_RETURN_TRUE;
}

static PyObject* cw_press_up(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":press_up")) {
      return NULL;
   }
   Interpreter::inputs[Interpreter::up] = true;
   Py_RETURN_TRUE;
}

static PyObject* cw_press_right(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":press_right")) {
      return NULL;
   }
   Interpreter::inputs[Interpreter::right] = true;
   Py_RETURN_TRUE;
}

static PyObject* cw_press_down(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":press_down")) {
      return NULL;
   }
   Interpreter::inputs[Interpreter::down] = true;
   Py_RETURN_TRUE;
}

static PyObject* cw_press_use_arrow(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":press_use_arrow")) {
      return NULL;
   }
   Interpreter::inputs[Interpreter::use_arrow] = true;
   Py_RETURN_TRUE;
}

static PyObject* cw_get_pos_x(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":get_pos_x")) {
      return NULL;
   }
   int pos_x = Interpreter::playerbot->get_tile()->get_x();
   return PyLong_FromLong(pos_x);
}

static PyObject* cw_get_pos_y(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":get_pos_y")) {
      return NULL;
   }
   int pos_y = Interpreter::playerbot->get_tile()->get_y();
   return PyLong_FromLong(pos_y);
}

static PyObject* cw_get_room_x(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":get_room_x")) {
      return NULL;
   }
   int room_x = Interpreter::playerbot->get_tile()->get_room()->get_x();
   return PyLong_FromLong(room_x);
}

static PyObject* cw_get_room_y(PyObject* self, PyObject* args) {
   if (!PyArg_ParseTuple(args, ":get_room_y")) {
      return NULL;
   }
   int room_y = Interpreter::playerbot->get_tile()->get_room()->get_y();
   return PyLong_FromLong(room_y);
}

static PyObject* cw_get_enemy_at(PyObject* self, PyObject* args) {
   int x, y;
   if (!PyArg_ParseTuple(args, "ii:get_enemy_at", &x, &y)) {
      return NULL;
   }
   Ref<Entity> ent = Interpreter::playerbot->get_tile()->get_room()->get_tile(x, y)->get_entity();
   if (ent != NULL) {
      Py_RETURN_TRUE;
   }
   Py_RETURN_FALSE;
}

static PyObject* cw_is_room_explored(PyObject* self, PyObject* args) {
   int x, y;
   if (!PyArg_ParseTuple(args, "ii:is_room_explored", &x, &y)) {
      return NULL;
   }
   Ref<Room_Map> room = Interpreter::playerbot->get_tile()->get_room()->get_floor()->get_room(x, y);
   if (room != NULL) {
      Py_RETURN_TRUE;
   }
   Py_RETURN_FALSE;
}

static PyObject* cw_get_door(PyObject* self, PyObject* args) {
   int dir;
   if (!PyArg_ParseTuple(args, "C:get_door_up", &dir)) {
      return NULL;
   }
   Ref<Room_Map> room = Interpreter::playerbot->get_tile()->get_room();
   bool door;
   switch (dir) {
      case 117:
         door = room->get_door(Interpreter::up);
         break;
      case 100:
         door = room->get_door(Interpreter::down);
         break;
      case 108:
         door = room->get_door(Interpreter::left);
         break;
      case 114:
         door = room->get_door(Interpreter::right);
         break;
   }
   if (door) {
      Py_RETURN_TRUE;
   }
   Py_RETURN_FALSE;
}

static PyObject* cw_get_door_room(PyObject* self, PyObject* args) {
   int dir, x, y;
   if (!PyArg_ParseTuple(args, "Cii:get_door_up", &dir, &x, &y)) {
      return NULL;
   }
   Ref<Room_Map> room = Interpreter::playerbot->get_tile()->get_room()->get_floor()->get_room(x, y);
   if (room == NULL) {
      Py_RETURN_NONE;
   }
   bool door;
   switch (dir) {
      case 117:
         door = room->get_door(Interpreter::up);
         break;
      case 100:
         door = room->get_door(Interpreter::down);
         break;
      case 108:
         door = room->get_door(Interpreter::left);
         break;
      case 114:
         door = room->get_door(Interpreter::right);
         break;
      default:
         break;
   }
   if (door) {
      Py_RETURN_TRUE;
   }
   Py_RETURN_FALSE;
}

static PyObject* cw_test(PyObject* self, PyObject* args) {
   int test;
   if (!PyArg_ParseTuple(args, "C:test", &test)) {
      return NULL;
   }
   Interpreter::test_output = test;
   Py_RETURN_TRUE;
}

/**********************
   Module Definition
**********************/

static PyMethodDef cw_methods[] = {
   {"press_left", cw_press_left, METH_VARARGS, "Press left input"},
   {"press_up", cw_press_up, METH_VARARGS, "Press up input"},
   {"press_right", cw_press_right, METH_VARARGS, "Press right input"},
   {"press_down", cw_press_down, METH_VARARGS, "Press down input"},
   {"press_use_arrow", cw_press_use_arrow, METH_VARARGS, "Press use_arrow input"},
   {"get_pos_x", cw_get_pos_x, METH_VARARGS, "Get bot x"},
   {"get_pos_y", cw_get_pos_y, METH_VARARGS, "Get bot y"},
   {"get_room_x", cw_get_room_x, METH_VARARGS, "Get current room's x"},
   {"get_room_y", cw_get_room_y, METH_VARARGS, "Get current room's y"},
   {"get_enemy_at", cw_get_enemy_at, METH_VARARGS, "Returns true if there is an enemy at tile (x, y)"},
   {"get_door", cw_get_door, METH_VARARGS, "returns whether there is a door in the current room. Takes in \"u\" \"d\" \"l\" or \"r\""},
   {"get_door_room", cw_get_door_room, METH_VARARGS, "returns whether there is a door in the specified room.\nTakes in \"u\" \"d\" \"l\" or \"r\", x, y"},
   {"test", cw_test, METH_VARARGS, "test"},
   {NULL, NULL, 0, NULL}
};

static PyModuleDef cw_module = {
   PyModuleDef_HEAD_INIT, "cw", NULL, -1, cw_methods,
   NULL, NULL, NULL, NULL
};

static PyObject* PyInit_cw_emb() {
   return PyModule_Create(&cw_module);
}



/*********************
   Public Functions
*********************/

bool Interpreter::is_initialized() {
   return initialized;
}

bool Interpreter::init(String code, Ref<Entity> pb) {
   if (initialized) {
      return false;
   }
   
   playerbot = pb;
   
   // save file from code
   FILE* py_file = fopen("user_code.py", "w");
   fputs(code.ascii().get_data(), py_file);
   fclose(py_file);
   
   // import C++ module
   PyImport_AppendInittab("cw", &PyInit_cw_emb);
   
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

bool Interpreter::run() {
   if (!initialized) {
      // handle error
      return false;
   }
   
   for (int i = 0; i < maxbutton; i++) inputs[i] = false;
   
   PyObject_CallObject(py_run_func, NULL);
   
   if (PyErr_Occurred()) {
      PyErr_Print();
      return false;
   }
   
   return true;
}

bool Interpreter::finalize() {
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

bool Interpreter::is_button_pressed(int button) {
   if (button < 0 || button > maxbutton) {
      return false;
   }
   return inputs[button];
}

int Interpreter::get_test_output() {
   return test_output;
}

void Interpreter::set_playerbot(Ref<Entity> pb) {
   if (!initialized) {
      // handle error
      return;
   }
   playerbot = pb;
}

void Interpreter::_bind_methods() {
   ObjectTypeDB::bind_method("init", &Interpreter::init);
   ObjectTypeDB::bind_method("run", &Interpreter::run);
   ObjectTypeDB::bind_method("finalize", &Interpreter::finalize);
   ObjectTypeDB::bind_method("is_button_pressed", &Interpreter::is_button_pressed);
	ObjectTypeDB::bind_method("is_initialized", &Interpreter::is_initialized);
	ObjectTypeDB::bind_method("get_test_output", &Interpreter::get_test_output);
	ObjectTypeDB::bind_method("set_playerbot", &Interpreter::set_playerbot);
   #undef I
   #define I(x) BIND_CONSTANT(x);\
   
   INTERP_INPUTS
}

Interpreter::Interpreter() {
   initialized = false;
}

Interpreter::~Interpreter() {
   finalize();
}

#undef I