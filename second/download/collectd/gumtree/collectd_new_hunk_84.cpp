		sstrncpy(value_list.host, hostname_g, sizeof(value_list.host));
	if (value_list.plugin[0] == 0)
		sstrncpy(value_list.plugin, "python", sizeof(value_list.plugin));
	Py_BEGIN_ALLOW_THREADS;
	ret = plugin_write(dest, NULL, &value_list);
	Py_END_ALLOW_THREADS;
	meta_data_destroy(value_list.meta);
	free(value);
	if (ret != 0) {
		PyErr_SetString(PyExc_RuntimeError, "error dispatching values, read the logs");
		return NULL;
	}
	Py_RETURN_NONE;
}

static PyObject *Values_repr(PyObject *s) {
	PyObject *ret, *tmp;
	static PyObject *l_interval = NULL, *l_values = NULL, *l_meta = NULL, *l_closing = NULL;
