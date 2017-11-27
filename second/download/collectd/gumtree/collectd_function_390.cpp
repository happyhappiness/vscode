static PyObject *Values_write(Values *self, PyObject *args, PyObject *kwds) {
	int i, ret;
	const data_set_t *ds;
	int size;
	value_t *value;
	value_list_t value_list = VALUE_LIST_INIT;
	PyObject *values = self->values, *meta = self->meta;
	double time = self->data.time, interval = self->interval;
	const char *host = self->data.host;
	const char *plugin = self->data.plugin;
	const char *plugin_instance = self->data.plugin_instance;
	const char *type = self->data.type;
	const char *type_instance = self->data.type_instance;
	const char *dest = NULL;
	
	static char *kwlist[] = {"destination", "type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", "meta", NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etOetetetetddO", kwlist,
			NULL, &type, &values, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &time, &interval, &meta))
		return NULL;

	if (type[0] == 0) {
		PyErr_SetString(PyExc_RuntimeError, "type not set");
		return NULL;
	}
	ds = plugin_get_ds(type);
	if (ds == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		return NULL;
	}
	if (values == NULL || (PyTuple_Check(values) == 0 && PyList_Check(values) == 0)) {
		PyErr_Format(PyExc_TypeError, "values must be list or tuple");
		return NULL;
	}
	size = (int) PySequence_Length(values);
	if (size != ds->ds_num) {
		PyErr_Format(PyExc_RuntimeError, "type %s needs %d values, got %i", type, ds->ds_num, size);
		return NULL;
	}
	value = malloc(size * sizeof(*value));
	for (i = 0; i < size; ++i) {
		PyObject *item, *num;
		item = PySequence_Fast_GET_ITEM(values, i); /* Borrowed reference. */
		if (ds->ds->type == DS_TYPE_COUNTER) {
			num = PyNumber_Long(item); /* New reference. */
			if (num != NULL) {
				value[i].counter = PyLong_AsUnsignedLongLong(num);
				Py_XDECREF(num);
			}
		} else if (ds->ds->type == DS_TYPE_GAUGE) {
			num = PyNumber_Float(item); /* New reference. */
			if (num != NULL) {
				value[i].gauge = PyFloat_AsDouble(num);
				Py_XDECREF(num);
			}
		} else if (ds->ds->type == DS_TYPE_DERIVE) {
			/* This might overflow without raising an exception.
			 * Not much we can do about it */
			num = PyNumber_Long(item); /* New reference. */
			if (num != NULL) {
				value[i].derive = PyLong_AsLongLong(num);
				Py_XDECREF(num);
			}
		} else if (ds->ds->type == DS_TYPE_ABSOLUTE) {
			/* This might overflow without raising an exception.
			 * Not much we can do about it */
			num = PyNumber_Long(item); /* New reference. */
			if (num != NULL) {
				value[i].absolute = PyLong_AsUnsignedLongLong(num);
				Py_XDECREF(num);
			}
		} else {
			free(value);
			PyErr_Format(PyExc_RuntimeError, "unknown data type %d for %s", ds->ds->type, type);
			return NULL;
		}
		if (PyErr_Occurred() != NULL) {
			free(value);
			return NULL;
		}
	}
	value_list.values = value;
	value_list.values_len = size;
	value_list.time = DOUBLE_TO_CDTIME_T(time);
	value_list.interval = DOUBLE_TO_CDTIME_T(interval);
	sstrncpy(value_list.host, host, sizeof(value_list.host));
	sstrncpy(value_list.plugin, plugin, sizeof(value_list.plugin));
	sstrncpy(value_list.plugin_instance, plugin_instance, sizeof(value_list.plugin_instance));
	sstrncpy(value_list.type, type, sizeof(value_list.type));
	sstrncpy(value_list.type_instance, type_instance, sizeof(value_list.type_instance));
	value_list.meta = cpy_build_meta(meta);;
	if (value_list.host[0] == 0)
		sstrncpy(value_list.host, hostname_g, sizeof(value_list.host));
	if (value_list.plugin[0] == 0)
		sstrncpy(value_list.plugin, "python", sizeof(value_list.plugin));
	Py_BEGIN_ALLOW_THREADS;
	ret = plugin_write(dest, NULL, &value_list);
	Py_END_ALLOW_THREADS;
	meta_data_destroy(value_list.meta);
	free(value);
	if (ret != 0) {
		PyErr_SetString(PyExc_RuntimeError, "error dispatching values, read the logs");
		return NULL;
	}
	Py_RETURN_NONE;
}