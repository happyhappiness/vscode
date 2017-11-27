static int Values_traverse(PyObject *self, visitproc visit, void *arg) {
  Values *v = (Values *)self;
  Py_VISIT(v->values);
  Py_VISIT(v->meta);
  return 0;
}