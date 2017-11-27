typedef int cpy_unregister_function_t(const char *name);

static PyObject *cpy_unregister_generic_userdata(cpy_unregister_function_t *unreg, PyObject *arg, const char *desc) {
	char buf[512];
	const char *name;

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
	if (unreg(name) == 0)
		Py_RETURN_NONE;
	PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.", desc, name);
	return NULL;
}

static PyObject *cpy_unregister_log(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic_userdata(plugin_unregister_log, arg, "log");
}
