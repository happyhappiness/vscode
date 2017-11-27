	}
	CPY_RELEASE_THREADS
}

static void cpy_flush_callback(int timeout, const char *id, user_data_t *data) {
	cpy_callback_t * c = data->data;
	PyObject *ret;

	CPY_LOCK_THREADS
	if (c->data == NULL)
		ret = PyObject_CallFunction(c->callback, "is", timeout, id); /* New reference. */
	else
		ret = PyObject_CallFunction(c->callback, "isO", timeout, id, c->data); /* New reference. */

	if (ret == NULL) {
		cpy_log_exception("flush callback");
	} else {
		Py_DECREF(ret);
	}
