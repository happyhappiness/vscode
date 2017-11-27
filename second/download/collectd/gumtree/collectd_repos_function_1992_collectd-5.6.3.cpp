static PyObject *cpy_register_shutdown(PyObject *self, PyObject *args,
                                       PyObject *kwds) {
  return cpy_register_generic(&cpy_shutdown_callbacks, args, kwds);
}