static PyObject *Notification_dispatch(Notification *self, PyObject *args, PyObject *kwds) {
	int ret;
	const data_set_t *ds;
	notification_t notification;
	double t = self->data.time;
	int severity = self->severity;
	char *host = NULL, *plugin = NULL, *plugin_instance = NULL, *type = NULL, *type_instance = NULL;
	char *message = NULL;

	static char *kwlist[] = {"type", "message", "plugin_instance", "type_instance",
			"plugin", "host", "time", "severity", NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etetetetetetdi", kwlist,
			NULL, &type, NULL, &message, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &t, &severity))
		return NULL;

	notification.time = DOUBLE_TO_CDTIME_T(t);
	notification.severity = severity;
	sstrncpy(notification.message, message ? message : self->message, sizeof(notification.message));
	sstrncpy(notification.host, host ? host : self->data.host, sizeof(notification.host));
	sstrncpy(notification.plugin, plugin ? plugin : self->data.plugin, sizeof(notification.plugin));
	sstrncpy(notification.plugin_instance, plugin_instance ? plugin_instance : self->data.plugin_instance, sizeof(notification.plugin_instance));
	sstrncpy(notification.type, type ? type : self->data.type, sizeof(notification.type));
	sstrncpy(notification.type_instance, type_instance ? type_instance : self->data.type_instance, sizeof(notification.type_instance));
	notification.meta = NULL;
	FreeAll();
	PyMem_Free(message);

	if (notification.type[0] == 0) {
		PyErr_SetString(PyExc_RuntimeError, "type not set");
		return NULL;
	}
	ds = plugin_get_ds(notification.type);
	if (ds == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", notification.type);
		return NULL;
	}

	if (notification.time == 0)
		notification.time = cdtime();
	if (notification.host[0] == 0)
		sstrncpy(notification.host, hostname_g, sizeof(notification.host));
	if (notification.plugin[0] == 0)
		sstrncpy(notification.plugin, "python", sizeof(notification.plugin));
	Py_BEGIN_ALLOW_THREADS;
	ret = plugin_dispatch_notification(&notification);
	Py_END_ALLOW_THREADS;
	if (ret != 0) {
		PyErr_SetString(PyExc_RuntimeError, "error dispatching notification, read the logs");
		return NULL;
	}
	Py_RETURN_NONE;
}