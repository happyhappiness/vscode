static PyObject *cpy_unregister_flush(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_flush, arg, "flush");
}