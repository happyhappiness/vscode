void cpy_log_exception(const char *context) {
	int l = 0, i;
	const char *typename = NULL, *message = NULL;
	PyObject *type, *value, *traceback, *tn, *m, *list;
	
	PyErr_Fetch(&type, &value, &traceback);
	PyErr_NormalizeException(&type, &value, &traceback);
	if (type == NULL) return;
	tn = PyObject_GetAttrString(type, "__name__"); /* New reference. */
	m = PyObject_Str(value); /* New reference. */
	if (tn != NULL)
		typename = cpy_unicode_or_bytes_to_string(&tn);
	if (m != NULL)
		message = cpy_unicode_or_bytes_to_string(&m);
	if (typename == NULL)
		typename = "NamelessException";
	if (message == NULL)
		message = "N/A";
	Py_BEGIN_ALLOW_THREADS
	ERROR("Unhandled python exception in %s: %s: %s", context, typename, message);
	Py_END_ALLOW_THREADS
	Py_XDECREF(tn);
	Py_XDECREF(m);
	if (!cpy_format_exception || !traceback) {
		PyErr_Clear();
		Py_DECREF(type);
		Py_XDECREF(value);
		Py_XDECREF(traceback);
		return;
	}
	list = PyObject_CallFunction(cpy_format_exception, "NNN", type, value, traceback); /* New reference. Steals references from "type", "value" and "traceback". */
	if (list)
		l = PyObject_Length(list);

	for (i = 0; i < l; ++i) {
		PyObject *line;
		char const *msg;
		char *cpy;

		line = PyList_GET_ITEM(list, i); /* Borrowed reference. */
		Py_INCREF(line);

		msg = cpy_unicode_or_bytes_to_string(&line);
		Py_DECREF(line);
		if (msg == NULL)
			continue;

		cpy = strdup(msg);
		if (cpy == NULL)
			continue;

		if (cpy[strlen(cpy) - 1] == '\n')
			cpy[strlen(cpy) - 1] = 0;

		Py_BEGIN_ALLOW_THREADS
		ERROR("%s", cpy);
		Py_END_ALLOW_THREADS

		free(cpy);
	}

	Py_XDECREF(list);
	PyErr_Clear();
}