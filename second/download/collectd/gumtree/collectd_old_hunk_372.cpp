static PyObject *cpy_register_shutdown(PyObject *self, PyObject *args, PyObject *kwds) {
	return cpy_register_generic(&cpy_shutdown_callbacks, args, kwds);
}

static PyObject *cpy_error(PyObject *self, PyObject *args) {
	const char *text;
	if (PyArg_ParseTuple(args, "s", &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_ERR, "%s", text);
	Py_END_ALLOW_THREADS
	Py_RETURN_NONE;
}

static PyObject *cpy_warning(PyObject *self, PyObject *args) {
	const char *text;
	if (PyArg_ParseTuple(args, "s", &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_WARNING, "%s", text);
	Py_END_ALLOW_THREADS
	Py_RETURN_NONE;
}

static PyObject *cpy_notice(PyObject *self, PyObject *args) {
	const char *text;
	if (PyArg_ParseTuple(args, "s", &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_NOTICE, "%s", text);
	Py_END_ALLOW_THREADS
	Py_RETURN_NONE;
}

static PyObject *cpy_info(PyObject *self, PyObject *args) {
	const char *text;
	if (PyArg_ParseTuple(args, "s", &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_INFO, "%s", text);
	Py_END_ALLOW_THREADS
	Py_RETURN_NONE;
}

static PyObject *cpy_debug(PyObject *self, PyObject *args) {
#ifdef COLLECT_DEBUG
	const char *text;
	if (PyArg_ParseTuple(args, "s", &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_DEBUG, "%s", text);
	Py_END_ALLOW_THREADS
#endif
	Py_RETURN_NONE;
}

static PyObject *cpy_unregister_generic(cpy_callback_t **list_head, PyObject *arg, const char *desc) {
	char buf[512];
	const char *name;
	cpy_callback_t *prev = NULL, *tmp;

	if (PyUnicode_Check(arg)) {
		arg = PyUnicode_AsEncodedString(arg, NULL, NULL);
		if (arg == NULL)
			return NULL;
		name = PyString_AsString(arg);
		Py_DECREF(arg);
	} else if (PyString_Check(arg)) {
		name = PyString_AsString(arg);
	} else {
		if (!PyCallable_Check(arg)) {
			PyErr_SetString(PyExc_TypeError, "This function needs a string or a callable object as its only parameter.");
			return NULL;
		}
		cpy_build_name(buf, sizeof(buf), arg, NULL);
		name = buf;
	}
	for (tmp = *list_head; tmp; prev = tmp, tmp = tmp->next)
		if (strcmp(name, tmp->name) == 0)
			break;
	
	if (tmp == NULL) {
		PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.", desc, name);
		return NULL;
	}
	/* Yes, this is actually save. To call this function the caller has to
	 * hold the GIL. Well, save as long as there is only one GIL anyway ... */
