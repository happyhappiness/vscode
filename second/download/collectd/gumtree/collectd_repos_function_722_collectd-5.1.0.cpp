static int Values_clear(PyObject *self) {
	Values *v = (Values *) self;
	Py_CLEAR(v->values);
	Py_CLEAR(v->meta);
	return 0;
}