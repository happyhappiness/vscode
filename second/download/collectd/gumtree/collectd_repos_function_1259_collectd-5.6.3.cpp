static PyObject *Config_new(PyTypeObject *type, PyObject *args,
                            PyObject *kwds) {
  Config *self;

  self = (Config *)type->tp_alloc(type, 0);
  if (self == NULL)
    return NULL;

  self->parent = NULL;
  self->key = NULL;
  self->values = NULL;
  self->children = NULL;
  return (PyObject *)self;
}