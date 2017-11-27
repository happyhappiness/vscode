	return (PyObject *) self;
}

static int PluginData_init(PyObject *s, PyObject *args, PyObject *kwds) {
	PluginData *self = (PluginData *) s;
	double time = 0;
	const char *type = "", *plugin_instance = "", *type_instance = "", *plugin = "", *host = "";
	static char *kwlist[] = {"type", "plugin_instance", "type_instance",
			"plugin", "host", "time", NULL};
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etetetetetd", kwlist, NULL, &type,
			NULL, &plugin_instance, NULL, &type_instance, NULL, &plugin, NULL, &host, &time))
		return -1;
	
	if (type[0] != 0 && plugin_get_ds(type) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		return -1;
	}

	sstrncpy(self->host, host, sizeof(self->host));
	sstrncpy(self->plugin, plugin, sizeof(self->plugin));
	sstrncpy(self->plugin_instance, plugin_instance, sizeof(self->plugin_instance));
	sstrncpy(self->type, type, sizeof(self->type));
	sstrncpy(self->type_instance, type_instance, sizeof(self->type_instance));
	
	self->time = time;
	return 0;
}

static PyObject *PluginData_repr(PyObject *s) {
	PyObject *ret;
	static PyObject *l_closing = NULL;
