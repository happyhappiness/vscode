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

