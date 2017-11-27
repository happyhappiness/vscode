static PyObject *cpy_unregister_shutdown(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic(&cpy_shutdown_callbacks, arg, "shutdown");
}