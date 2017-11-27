static void cpy_build_name(char *buf, size_t size, PyObject *callback, const char *name) {
	const char *module = NULL;
	PyObject *mod = NULL;
	
	if (name != NULL) {
		snprintf(buf, size, "python.%s", name);
		return;
	}
	
	mod = PyObject_GetAttrString(callback, "__module__"); /* New reference. */
	if (mod != NULL)
		module = PyString_AsString(mod);
	
	if (module != NULL) {
		snprintf(buf, size, "python.%s", module);
		Py_XDECREF(mod);
		PyErr_Clear();
		return;
	}
	Py_XDECREF(mod);
	
	snprintf(buf, size, "python.%p", callback);
	PyErr_Clear();
}