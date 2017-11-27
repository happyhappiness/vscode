static PyObject *cpy_unregister_log(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_log, arg, "log");
}