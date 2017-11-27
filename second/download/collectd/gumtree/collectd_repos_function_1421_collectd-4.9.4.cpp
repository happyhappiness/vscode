static void cpy_log_callback(int severity, const char *message, user_data_t *data) {
	cpy_callback_t * c = data->data;
	PyObject *ret;

	CPY_LOCK_THREADS
	if (c->data == NULL)
		ret = PyObject_CallFunction(c->callback, "is", severity, message); /* New reference. */
	else
		ret = PyObject_CallFunction(c->callback, "isO", severity, message, c->data); /* New reference. */

	if (ret == NULL) {
		/* FIXME */
		/* Do we really want to trigger a log callback because a log callback failed?
		 * Probably not. */
		PyErr_Print();
		/* In case someone wanted to be clever, replaced stderr and failed at that. */
		PyErr_Clear();
	} else {
		Py_DECREF(ret);
	}
	CPY_RELEASE_THREADS
}