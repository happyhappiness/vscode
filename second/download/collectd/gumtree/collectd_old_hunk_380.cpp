	
	self = (Values *) PluginData_new(type, args, kwds);
	if (self == NULL)
		return NULL;
	
	self->values = PyList_New(0);
	self->interval = 0;
	return (PyObject *) self;
}

static int Values_init(PyObject *s, PyObject *args, PyObject *kwds) {
	Values *self = (Values *) s;
	int interval = 0, ret;
	double time = 0;
	PyObject *values = NULL, *tmp;
	const char *type = "", *plugin_instance = "", *type_instance = "", *plugin = "", *host = "";
	static char *kwlist[] = {"type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", NULL};
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sOssssdi", kwlist,
			&type, &values, &plugin_instance, &type_instance,
			&plugin, &host, &time, &interval))
		return -1;
	
	tmp = Py_BuildValue("sssssd", type, plugin_instance, type_instance, plugin, host, time);
	if (tmp == NULL)
		return -1;
	ret = PluginDataType.tp_init(s, tmp, NULL);
	Py_DECREF(tmp);
	if (ret != 0)
		return -1;
	
	if (values == NULL) {
		values = PyList_New(0);
		PyErr_Clear();
	} else {
		Py_INCREF(values);
	}
	
	tmp = self->values;
	self->values = values;
	Py_XDECREF(tmp);
	
	self->interval = interval;
	return 0;
}

static PyObject *Values_dispatch(Values *self, PyObject *args, PyObject *kwds) {
	int i, ret;
	const data_set_t *ds;
	int size;
	value_t *value;
	value_list_t value_list = VALUE_LIST_INIT;
	PyObject *values = self->values;
	double time = self->data.time;
	int interval = self->interval;
	const char *host = self->data.host;
	const char *plugin = self->data.plugin;
	const char *plugin_instance = self->data.plugin_instance;
	const char *type = self->data.type;
	const char *type_instance = self->data.type_instance;
	
	static char *kwlist[] = {"type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sOssssdi", kwlist,
			&type, &values, &plugin_instance, &type_instance,
			&plugin, &host, &time, &interval))
		return NULL;

	if (type[0] == 0) {
		PyErr_SetString(PyExc_RuntimeError, "type not set");
		return NULL;
	}
