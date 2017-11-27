static void Config_dealloc(PyObject *self) {
  Config_clear(self);
  self->ob_type->tp_free(self);
}