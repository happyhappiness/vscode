static int PluginData_init(PyObject *s, PyObject *args, PyObject *kwds) {
	PluginData *self = (PluginData *) s;
	double time = 0;
	char *type = NULL, *plugin_instance = NULL, *type_instance = NULL, *plugin = NULL, *host = NULL;
	static char *kwlist[] = {"type", "plugin_instance", "type_instance",
			"plugin", "host", "time", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etetetetetd", kwlist, NULL, &type,
			NULL, &plugin_instance, NULL, &type_instance, NULL, &plugin, NULL, &host, &time))
		return -1;

	if (type && plugin_get_ds(type) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		FreeAll();
		return -1;
	}

