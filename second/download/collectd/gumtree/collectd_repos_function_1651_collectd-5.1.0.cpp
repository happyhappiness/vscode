static PyObject *cpy_debug(PyObject *self, PyObject *args) {
#ifdef COLLECT_DEBUG
	const char *text;
	if (PyArg_ParseTuple(args, "et", NULL, &text) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
	plugin_log(LOG_DEBUG, "%s", text);
	Py_END_ALLOW_THREADS
#endif
	Py_RETURN_NONE;
}