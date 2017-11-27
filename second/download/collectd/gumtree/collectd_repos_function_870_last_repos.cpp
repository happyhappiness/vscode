static int Notification_traverse(PyObject *self, visitproc visit, void *arg) {
  Notification *n = (Notification *)self;
  Py_VISIT(n->meta);
  return 0;
}