static PyObject *cpy_register_notification(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic_userdata((void *) plugin_register_notification,
			(void *) cpy_notification_callback, args, kwds);
}