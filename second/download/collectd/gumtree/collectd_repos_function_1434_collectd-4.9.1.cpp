static PyObject *cpy_warning(PyObject *self, PyObject *args) {
	const char *text;
	if (PyArg_ParseTuple(args, "s", &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_WARNING, "%s", text);
	Py_END_ALLOW_THREADS
	Py_RETURN_NONE;
}