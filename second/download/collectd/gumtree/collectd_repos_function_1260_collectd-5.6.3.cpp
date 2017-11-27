static int Config_init(PyObject *s, PyObject *args, PyObject *kwds) {
  PyObject *key = NULL, *parent = NULL, *values = NULL, *children = NULL, *tmp;
  Config *self = (Config *)s;
  static char *kwlist[] = {"key", "parent", "values", "children", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|OOO", kwlist, &key, &parent,
                                   &values, &children))
    return -1;

  if (!IS_BYTES_OR_UNICODE(key)) {
    PyErr_SetString(PyExc_TypeError, "argument 1 must be str");
    Py_XDECREF(parent);
    Py_XDECREF(values);
    Py_XDECREF(children);
    return -1;
  }
  if (values == NULL) {
    values = PyTuple_New(0);
    PyErr_Clear();
  }
  if (children == NULL) {
    children = PyTuple_New(0);
    PyErr_Clear();
  }
  tmp = self->key;
  Py_INCREF(key);
  self->key = key;
  Py_XDECREF(tmp);
  if (parent != NULL) {
    tmp = self->parent;
    Py_INCREF(parent);
    self->parent = parent;
    Py_XDECREF(tmp);
  }
  if (values != NULL) {
    tmp = self->values;
    Py_INCREF(values);
    self->values = values;
    Py_XDECREF(tmp);
  }
  if (children != NULL) {
    tmp = self->children;
    Py_INCREF(children);
    self->children = children;
    Py_XDECREF(tmp);
  }
  return 0;
}