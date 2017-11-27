		"similar to Values but has a severity and a message instead of interval\n"
		"and time.\n"
		"Notifications can be dispatched at any time and can be received with register_notification.";

static int Notification_init(PyObject *s, PyObject *args, PyObject *kwds) {
	Notification *self = (Notification *) s;
	PyObject *tmp;
	int severity = 0, ret;
	double time = 0;
	const char *message = "";
	const char *type = "", *plugin_instance = "", *type_instance = "", *plugin = "", *host = "";
	static char *kwlist[] = {"type", "message", "plugin_instance", "type_instance",
			"plugin", "host", "time", "severity", NULL};
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ssssssdi", kwlist,
			&type, &message, &plugin_instance, &type_instance,
			&plugin, &host, &time, &severity))
		return -1;
	
	tmp = Py_BuildValue("sssssd", type, plugin_instance, type_instance, plugin, host, time);
	if (tmp == NULL)
		return -1;
	ret = PluginDataType.tp_init(s, tmp, NULL);
	Py_DECREF(tmp);
	if (ret != 0)
		return -1;
	
	sstrncpy(self->message, message, sizeof(self->message));
	self->severity = severity;
	return 0;
}

static PyObject *Notification_dispatch(Notification *self, PyObject *args, PyObject *kwds) {
