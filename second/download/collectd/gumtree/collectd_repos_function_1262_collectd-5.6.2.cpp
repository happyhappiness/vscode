static int Config_traverse(PyObject *self, visitproc visit, void *arg) {
  Config *c = (Config *)self;
  Py_VISIT(c->parent);
  Py_VISIT(c->key);
  Py_VISIT(c->values);
  Py_VISIT(c->children);
  return 0;
}