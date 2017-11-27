static int Notification_init(PyObject *s, PyObject *args, PyObject *kwds) {
	Notification *self = (Notification *) s;
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

	sstrncpy(self->data.host, host ? host : "", sizeof(self->data.host));
	sstrncpy(self->data.plugin, plugin ? plugin : "", sizeof(self->data.plugin));
	sstrncpy(self->data.plugin_instance, plugin_instance ? plugin_instance : "", sizeof(self->data.plugin_instance));
	sstrncpy(self->data.type, type ? type : "", sizeof(self->data.type));
	sstrncpy(self->data.type_instance, type_instance ? type_instance : "", sizeof(self->data.type_instance));
	sstrncpy(self->message, message ? message : "", sizeof(self->message));
	self->data.time = time;
	self->severity = severity;

	FreeAll();
	PyMem_Free(message);
	return 0;
}