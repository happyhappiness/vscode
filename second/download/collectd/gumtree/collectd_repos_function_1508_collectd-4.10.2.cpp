static PyObject *cpy_register_config(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic(&cpy_config_callbacks, args, kwds);
}