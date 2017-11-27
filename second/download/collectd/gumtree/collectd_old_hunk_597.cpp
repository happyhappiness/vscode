	int severity = 0;
	double time = 0;
	char *message = NULL;
	char *type = NULL, *plugin_instance = NULL, *type_instance = NULL, *plugin = NULL, *host = NULL;
	static char *kwlist[] = {"type", "message", "plugin_instance", "type_instance",
			"plugin", "host", "time", "severity", NULL};
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etetetetetetdi", kwlist,
			NULL, &type, NULL, &message, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &time, &severity))
		return -1;
	
	if (type && plugin_get_ds(type) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		FreeAll();
		PyMem_Free(message);
		return -1;
	}
