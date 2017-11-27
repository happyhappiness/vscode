static PyObject *Values_write(Values *self, PyObject *args, PyObject *kwds) {
	int i, ret;
	const data_set_t *ds;
	int size;
	value_t *value;
	value_list_t value_list = VALUE_LIST_INIT;
	PyObject *values = self->values, *meta = self->meta;
	double time = self->data.time;
	int interval = self->interval;
	const char *host = self->data.host;
	const char *plugin = self->data.plugin;
	const char *plugin_instance = self->data.plugin_instance;
	const char *type = self->data.type;
	const char *type_instance = self->data.type_instance;
	const char *dest = NULL;
	
	static char *kwlist[] = {"destination", "type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", "meta", NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etOetetetetdiO", kwlist,
			NULL, &type, &values, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &time, &interval, &meta))
		return NULL;

	if (type[0] == 0) {
		PyErr_SetString(PyExc_RuntimeError, "type not set");
		return NULL;
	}
