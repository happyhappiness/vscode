static PyObject *Values_new(PyTypeObject *type, PyObject *args,
                            PyObject *kwds) {
  Values *self;

  self = (Values *)PluginData_new(type, args, kwds);
  if (self == NULL)
    return NULL;

  self->values = PyList_New(0);
  self->meta = PyDict_New();
  self->interval = 0;
  return (PyObject *)self;
}