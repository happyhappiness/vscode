	
	self->time = time;
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
	if (new == NULL) {
		Py_DECREF(value);
		return -1;
	}
	old = ((char *) self) + (intptr_t) data;
	sstrncpy(old, new, DATA_MAX_NAME_LEN);
	Py_DECREF(value);
	return 0;
}

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

static PyGetSetDef PluginData_getseters[] = {
	{"host", PluginData_getstring, PluginData_setstring, host_doc, (void *) offsetof(PluginData, host)},
	{"plugin", PluginData_getstring, PluginData_setstring, plugin_doc, (void *) offsetof(PluginData, plugin)},
