static PyObject *cpy_flush(PyObject *self, PyObject *args, PyObject *kwds) {
  int timeout = -1;
  char *plugin = NULL, *identifier = NULL;
  static char *kwlist[] = {"plugin", "timeout", "identifier", NULL};

  if (PyArg_ParseTupleAndKeywords(args, kwds, "|etiet", kwlist, NULL, &plugin,
                                  &timeout, NULL, &identifier) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS;
  plugin_flush(plugin, timeout, identifier);
  Py_END_ALLOW_THREADS;
  PyMem_Free(plugin);
  PyMem_Free(identifier);
  Py_RETURN_NONE;
}