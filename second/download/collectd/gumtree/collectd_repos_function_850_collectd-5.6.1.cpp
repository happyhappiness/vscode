static int PluginData_settype(PyObject *self, PyObject *value, void *data) {
	char *old;
	const char *new;

	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
		return -1;
	}
	Py_INCREF(value);
	new = cpy_unicode_or_bytes_to_string(&value);
	if (new == NULL) {
		Py_DECREF(value);
		return -1;
	}

	if (plugin_get_ds(new) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", new);
		Py_DECREF(value);
		return -1;
	}

	old = ((char *) self) + (intptr_t) data;
	sstrncpy(old, new, DATA_MAX_NAME_LEN);
	Py_DECREF(value);
	return 0;
}