static PyObject *cpy_unregister_init(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic(&cpy_init_callbacks, arg, "init");
}