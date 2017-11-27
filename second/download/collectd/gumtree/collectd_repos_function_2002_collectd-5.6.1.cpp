static PyObject *cpy_unregister_write(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic_userdata(plugin_unregister_write, arg, "write");
}