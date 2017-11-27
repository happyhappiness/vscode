}

static PyObject *cpy_error(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_ERR, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_warning(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_WARNING, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_notice(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_NOTICE, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_info(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_INFO, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_debug(PyObject *self, PyObject *args) {
#ifdef COLLECT_DEBUG
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_DEBUG, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
#endif
  Py_RETURN_NONE;
}

static PyObject *cpy_unregister_generic(cpy_callback_t **list_head,
                                        PyObject *arg, const char *desc) {
