typedef int cpy_unregister_function_t(const char *name);

static PyObject *cpy_unregister_generic_userdata(cpy_unregister_function_t *unreg, PyObject *arg, const char *desc) {
	char buf[512];
	const char *name;

	Py_INCREF(arg);
	name = cpy_unicode_or_bytes_to_string(&arg);
	if (name == NULL) {
		PyErr_Clear();
		if (!PyCallable_Check(arg)) {
			PyErr_SetString(PyExc_TypeError, "This function needs a string or a callable object as its only parameter.");
			Py_DECREF(arg);
			return NULL;
		}
		cpy_build_name(buf, sizeof(buf), arg, NULL);
		name = buf;
	}
	if (unreg(name) == 0) {
		Py_DECREF(arg);
		Py_RETURN_NONE;
	}
	PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.", desc, name);
	Py_DECREF(arg);
	return NULL;
}

static PyObject *cpy_unregister_log(PyObject *self, PyObject *arg) {
	return cpy_unregister_generic_userdata(plugin_unregister_log, arg, "log");
}
