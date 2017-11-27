static PyObject *cpy_register_log(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic_userdata((void *) plugin_register_log,
			(void *) cpy_log_callback, args, kwds);
}