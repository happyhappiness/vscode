static PyObject *cpy_register_init(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic(&cpy_init_callbacks, args, kwds);
}