static PyObject *cpy_warning(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS;
  plugin_log(LOG_WARNING, "%s", text);
  Py_END_ALLOW_THREADS;
  PyMem_Free(text);
  Py_RETURN_NONE;
}