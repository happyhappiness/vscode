static PyObject *cpy_info(PyObject *self, PyObject *args) {
	const char *text;
	if (PyArg_ParseTuple(args, "et", NULL, &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_INFO, "%s", text);
	Py_END_ALLOW_THREADS
	Py_RETURN_NONE;
}