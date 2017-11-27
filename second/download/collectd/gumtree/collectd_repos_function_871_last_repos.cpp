static int Notification_clear(PyObject *self) {
  Notification *n = (Notification *)self;
  Py_CLEAR(n->meta);
  return 0;
}