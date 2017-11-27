static PyObject *cpy_register_write(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic_userdata((void *) plugin_register_write,
			(void *) cpy_write_callback, args, kwds);
}