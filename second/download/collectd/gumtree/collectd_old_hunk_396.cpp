		sstrncpy(value_list.host, hostname_g, sizeof(value_list.host));
	if (value_list.plugin[0] == 0)
		sstrncpy(value_list.plugin, "python", sizeof(value_list.plugin));
	Py_BEGIN_ALLOW_THREADS;
	ret = plugin_dispatch_values(&value_list);
	Py_END_ALLOW_THREADS;
	if (ret != 0) {
		PyErr_SetString(PyExc_RuntimeError, "error dispatching values, read the logs");
		return NULL;
	}
	free(value);
	Py_RETURN_NONE;
}

static PyObject *Values_write(Values *self, PyObject *args, PyObject *kwds) {
	int i, ret;
	const data_set_t *ds;
