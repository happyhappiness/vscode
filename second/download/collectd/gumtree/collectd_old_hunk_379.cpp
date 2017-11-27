	
	self->time = time;
	return 0;
}

static PyObject *PluginData_repr(PyObject *s) {
	PluginData *self = (PluginData *) s;
	
	return PyString_FromFormat("collectd.Values(type='%s%s%s%s%s%s%s%s%s',time=%lu)", self->type,
			*self->type_instance ? "',type_instance='" : "", self->type_instance,
			*self->plugin ? "',plugin='" : "", self->plugin,
			*self->plugin_instance ? "',plugin_instance='" : "", self->plugin_instance,
			*self->host ? "',host='" : "", self->host,
			(long unsigned) self->time);
}

static PyMemberDef PluginData_members[] = {
	{"time", T_DOUBLE, offsetof(PluginData, time), 0, time_doc},
	{NULL}
};

static PyObject *PluginData_getstring(PyObject *self, void *data) {
	const char *value = ((char *) self) + (intptr_t) data;
	
	return PyString_FromString(value);
}

static int PluginData_setstring(PyObject *self, PyObject *value, void *data) {
	char *old;
	const char *new;
	
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
		return -1;
	}
	new = PyString_AsString(value);
	if (new == NULL) return -1;
	old = ((char *) self) + (intptr_t) data;
	sstrncpy(old, new, DATA_MAX_NAME_LEN);
	return 0;
}

static int PluginData_settype(PyObject *self, PyObject *value, void *data) {
	char *old;
	const char *new;
	
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
		return -1;
	}
	new = PyString_AsString(value);
	if (new == NULL) return -1;

	if (plugin_get_ds(new) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", new);
		return -1;
	}

	old = ((char *) self) + (intptr_t) data;
	sstrncpy(old, new, DATA_MAX_NAME_LEN);
	return 0;
}

static PyGetSetDef PluginData_getseters[] = {
	{"host", PluginData_getstring, PluginData_setstring, host_doc, (void *) offsetof(PluginData, host)},
	{"plugin", PluginData_getstring, PluginData_setstring, plugin_doc, (void *) offsetof(PluginData, plugin)},
