static PyObject *cpy_register_read(PyObject *self, PyObject *args,
                                   PyObject *kwds) {
  char buf[512];
  cpy_callback_t *c = NULL;
  double interval = 0;
  char *name = NULL;
  PyObject *callback = NULL, *data = NULL;
  static char *kwlist[] = {"callback", "interval", "data", "name", NULL};

  if (PyArg_ParseTupleAndKeywords(args, kwds, "O|dOet", kwlist, &callback,
                                  &interval, &data, NULL, &name) == 0)
    return NULL;
  if (PyCallable_Check(callback) == 0) {
    PyMem_Free(name);
    PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
    return NULL;
  }
  cpy_build_name(buf, sizeof(buf), callback, name);
  PyMem_Free(name);

  Py_INCREF(callback);
  Py_XINCREF(data);

  c = calloc(1, sizeof(*c));
  if (c == NULL)
    return NULL;

  c->name = strdup(buf);
  c->callback = callback;
  c->data = data;
  c->next = NULL;

  user_data_t user_data = {.data = c, .free_func = cpy_destroy_user_data};

  plugin_register_complex_read(/* group = */ "python", buf, cpy_read_callback,
                               DOUBLE_TO_CDTIME_T(interval), &user_data);
  ++cpy_num_callbacks;
  return cpy_string_to_unicode_or_bytes(buf);
}