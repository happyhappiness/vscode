static PyObject *PluginData_new(PyTypeObject *type, PyObject *args,
                                PyObject *kwds) {
  PluginData *self;

  self = (PluginData *)type->tp_alloc(type, 0);
  if (self == NULL)
    return NULL;

  self->time = 0;
  self->host[0] = 0;
  self->plugin[0] = 0;
  self->plugin_instance[0] = 0;
  self->type[0] = 0;
  self->type_instance[0] = 0;
  return (PyObject *)self;
}