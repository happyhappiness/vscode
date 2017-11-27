	const char *type = self->data.type;
	const char *type_instance = self->data.type_instance;
	const char *message = self->message;
	
	static char *kwlist[] = {"type", "message", "plugin_instance", "type_instance",
			"plugin", "host", "time", "severity", NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ssssssdi", kwlist,
			&type, &message, &plugin_instance, &type_instance,
			&plugin, &host, &t, &severity))
		return NULL;

	if (type[0] == 0) {
		PyErr_SetString(PyExc_RuntimeError, "type not set");
		return NULL;
	}
