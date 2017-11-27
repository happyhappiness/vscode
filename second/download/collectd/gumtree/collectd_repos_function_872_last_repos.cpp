static void Notification_dealloc(PyObject *self) {
  Notification_clear(self);
  self->ob_type->tp_free(self);
}