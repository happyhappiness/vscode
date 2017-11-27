static PyObject *cpy_unregister_read(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic_userdata(plugin_unregister_read, arg, "read");
}