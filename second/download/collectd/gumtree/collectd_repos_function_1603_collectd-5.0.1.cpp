static PyObject *cpy_register_flush(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic_userdata((void *) plugin_register_flush,
			(void *) cpy_flush_callback, args, kwds);
}