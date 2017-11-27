	PluginData *self = (PluginData *) s;
	double time = 0;
	const char *type = "", *plugin_instance = "", *type_instance = "", *plugin = "", *host = "";
	static char *kwlist[] = {"type", "plugin_instance", "type_instance",
			"plugin", "host", "time", NULL};
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sssssd", kwlist, &type,
			&plugin_instance, &type_instance, &plugin, &host, &time))
		return -1;
	
	if (type[0] != 0 && plugin_get_ds(type) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		return -1;
	}
