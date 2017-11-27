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