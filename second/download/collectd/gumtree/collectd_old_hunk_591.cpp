	return 0;
}

static PyObject *PluginData_repr(PyObject *s) {
	PyObject *ret;
	static PyObject *l_closing = NULL;
	
	if (l_closing == NULL)
		l_closing = cpy_string_to_unicode_or_bytes(")");
	
	if (l_closing == NULL)
		return NULL;
	
	ret = cpy_common_repr(s);
	CPY_STRCAT(&ret, l_closing);
	return ret;
}

static PyMemberDef PluginData_members[] = {
	{"time", T_DOUBLE, offsetof(PluginData, time), 0, time_doc},
	{NULL}
};

static PyObject *PluginData_getstring(PyObject *self, void *data) {
	const char *value = ((char *) self) + (intptr_t) data;
	
	return cpy_string_to_unicode_or_bytes(value);
}

static int PluginData_setstring(PyObject *self, PyObject *value, void *data) {
	char *old;
	const char *new;
	
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
		return -1;
	}
	Py_INCREF(value);
	new = cpy_unicode_or_bytes_to_string(&value);
