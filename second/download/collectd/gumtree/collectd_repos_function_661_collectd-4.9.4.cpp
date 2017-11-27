static int Values_clear(PyObject *self) {
	Values *v = (Values *) self;
	Py_CLEAR(v->values);
	return 0;
}