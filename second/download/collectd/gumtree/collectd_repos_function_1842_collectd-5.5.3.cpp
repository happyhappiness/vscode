static void cpy_flush_callback(int timeout, const char *id, user_data_t *data) {
	cpy_callback_t * c = data->data;
	PyObject *ret, *text;

	CPY_LOCK_THREADS
	text = cpy_string_to_unicode_or_bytes(id);
	if (c->data == NULL)
		ret = PyObject_CallFunction(c->callback, "iN", timeout, text); /* New reference. */
	else
		ret = PyObject_CallFunction(c->callback, "iNO", timeout, text, c->data); /* New reference. */

	if (ret == NULL) {
		cpy_log_exception("flush callback");
	} else {
		Py_DECREF(ret);
	}
	CPY_RELEASE_THREADS
}