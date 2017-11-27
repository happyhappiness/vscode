static int Config_clear(PyObject *self) {
	Config *c = (Config *) self;
	Py_CLEAR(c->parent);
	Py_CLEAR(c->key);
	Py_CLEAR(c->values);
	Py_CLEAR(c->children);
	return 0;
}