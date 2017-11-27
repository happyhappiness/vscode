static int Values_init(PyObject *s, PyObject *args, PyObject *kwds) {
	Values *self = (Values *) s;
	double interval = 0, time = 0;
	PyObject *values = NULL, *meta = NULL, *tmp;
	char *type = NULL, *plugin_instance = NULL, *type_instance = NULL, *plugin = NULL, *host = NULL;
	static char *kwlist[] = {"type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", "meta", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etOetetetetddO", kwlist,
			NULL, &type, &values, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &time, &interval, &meta))
		return -1;

	if (type && plugin_get_ds(type) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		FreeAll();
		return -1;
	}

	sstrncpy(self->data.host, host ? host : "", sizeof(self->data.host));
	sstrncpy(self->data.plugin, plugin ? plugin : "", sizeof(self->data.plugin));
	sstrncpy(self->data.plugin_instance, plugin_instance ? plugin_instance : "", sizeof(self->data.plugin_instance));
	sstrncpy(self->data.type, type ? type : "", sizeof(self->data.type));
	sstrncpy(self->data.type_instance, type_instance ? type_instance : "", sizeof(self->data.type_instance));
	self->data.time = time;

	FreeAll();

	if (values == NULL) {
		values = PyList_New(0);
		PyErr_Clear();
	} else {
		Py_INCREF(values);
	}

	if (meta == NULL) {
		meta = PyDict_New();
		PyErr_Clear();
	} else {
		Py_INCREF(meta);
	}

	tmp = self->values;
	self->values = values;
	Py_XDECREF(tmp);

	tmp = self->meta;
	self->meta = meta;
	Py_XDECREF(tmp);

	self->interval = interval;
	return 0;
}