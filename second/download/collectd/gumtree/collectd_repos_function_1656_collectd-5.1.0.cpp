static PyObject *cpy_unregister_config(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic(&cpy_config_callbacks, arg, "config");
}