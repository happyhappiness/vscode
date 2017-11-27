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
	if (!cpy_format_exception) {
		PyErr_Clear();
		Py_XDECREF(type);
		Py_XDECREF(value);
		Py_XDECREF(traceback);
		return;
	}
	if (!traceback) {
		PyErr_Clear();
		return;
	}
	list = PyObject_CallFunction(cpy_format_exception, "NNN", type, value, traceback); /* New reference. */
	if (list)
		l = PyObject_Length(list);
	for (i = 0; i < l; ++i) {
		char *s;
		PyObject *line;
		
		line = PyList_GET_ITEM(list, i); /* Borrowed reference. */
		Py_INCREF(line);
		s = strdup(cpy_unicode_or_bytes_to_string(&line));
		Py_DECREF(line);
		if (s[strlen(s) - 1] == '\n')
			s[strlen(s) - 1] = 0;
		Py_BEGIN_ALLOW_THREADS
		ERROR("%s", s);
		Py_END_ALLOW_THREADS
		free(s);
	}
	Py_XDECREF(list);
	PyErr_Clear();
}