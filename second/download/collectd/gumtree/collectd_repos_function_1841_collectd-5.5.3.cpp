static void cpy_log_callback(int severity, const char *message, user_data_t *data) {
	cpy_callback_t * c = data->data;
	PyObject *ret, *text;

	CPY_LOCK_THREADS
	text = cpy_string_to_unicode_or_bytes(message);  /* New reference. */
	if (c->data == NULL)
		ret = PyObject_CallFunction(c->callback, "iN", severity, text); /* New reference. Steals a reference from "text". */
	else
		ret = PyObject_CallFunction(c->callback, "iNO", severity, text, c->data); /* New reference. Steals a reference from "text". */

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