	
	self = (Values *) PluginData_new(type, args, kwds);
	if (self == NULL)
		return NULL;
	
	self->values = PyList_New(0);
	self->meta = PyDict_New();
	self->interval = 0;
	return (PyObject *) self;
}

static int Values_init(PyObject *s, PyObject *args, PyObject *kwds) {
	Values *self = (Values *) s;
	int interval = 0;
	double time = 0;
	PyObject *values = NULL, *meta = NULL, *tmp;
	const char *type = "", *plugin_instance = "", *type_instance = "", *plugin = "", *host = "";
	static char *kwlist[] = {"type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", "meta", NULL};
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etOetetetetdiO", kwlist,
			NULL, &type, &values, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &time, &interval, &meta))
		return -1;
	
	if (type[0] != 0 && plugin_get_ds(type) == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
		return -1;
	}

	sstrncpy(self->data.host, host, sizeof(self->data.host));
	sstrncpy(self->data.plugin, plugin, sizeof(self->data.plugin));
	sstrncpy(self->data.plugin_instance, plugin_instance, sizeof(self->data.plugin_instance));
	sstrncpy(self->data.type, type, sizeof(self->data.type));
	sstrncpy(self->data.type_instance, type_instance, sizeof(self->data.type_instance));
	self->data.time = time;

	if (values == NULL) {
		values = PyList_New(0);
		PyErr_Clear();
	} else {
		Py_INCREF(values);
	}
	
	if (meta == NULL) {
		meta = PyDict_New();
		PyErr_Clear();
	} else {
		Py_INCREF(meta);
	}
	
	tmp = self->values;
	self->values = values;
	Py_XDECREF(tmp);
	
	tmp = self->meta;
	self->meta = meta;
	Py_XDECREF(tmp);

	self->interval = interval;
	return 0;
}

static meta_data_t *cpy_build_meta(PyObject *meta) {
	int i, s;
	meta_data_t *m = NULL;
	PyObject *l;
	
	if (!meta)
		return NULL;

	m = meta_data_create();
	l = PyDict_Items(meta);
	s = PyList_Size(l);
	for (i = 0; i < s; ++i) {
		const char *string, *keystring;
		PyObject *key, *value, *item, *tmp;
		
		item = PyList_GET_ITEM(l, i);
		key = PyTuple_GET_ITEM(item, 0);
		Py_INCREF(key);
		keystring = cpy_unicode_or_bytes_to_string(&key);
		if (!keystring) {
			PyErr_Clear();
			Py_XDECREF(key);
			continue;
		}
		value = PyTuple_GET_ITEM(item, 1);
		Py_INCREF(value);
		if (value == Py_True) {
			meta_data_add_boolean(m, keystring, 1);
		} else if (value == Py_False) {
			meta_data_add_boolean(m, keystring, 0);
		} else if (PyFloat_Check(value)) {
			meta_data_add_double(m, keystring, PyFloat_AsDouble(value));
		} else if (PyObject_TypeCheck(value, &SignedType)) {
			long long int lli;
			lli = PyLong_AsLongLong(value);
			if (!PyErr_Occurred() && (lli == (int64_t) lli))
				meta_data_add_signed_int(m, keystring, lli);
		} else if (PyObject_TypeCheck(value, &UnsignedType)) {
			long long unsigned llu;
			llu = PyLong_AsUnsignedLongLong(value);
			if (!PyErr_Occurred() && (llu == (uint64_t) llu))
				meta_data_add_unsigned_int(m, keystring, llu);
		} else if (PyNumber_Check(value)) {
			long long int lli;
			long long unsigned llu;
			tmp = PyNumber_Long(value);
			lli = PyLong_AsLongLong(tmp);
			if (!PyErr_Occurred() && (lli == (int64_t) lli)) {
				meta_data_add_signed_int(m, keystring, lli);
			} else {
				PyErr_Clear();
				llu = PyLong_AsUnsignedLongLong(tmp);
				if (!PyErr_Occurred() && (llu == (uint64_t) llu))
					meta_data_add_unsigned_int(m, keystring, llu);
			}
			Py_XDECREF(tmp);
		} else {
			string = cpy_unicode_or_bytes_to_string(&value);
			if (string) {
				meta_data_add_string(m, keystring, string);
			} else {
				PyErr_Clear();
				tmp = PyObject_Str(value);
				string = cpy_unicode_or_bytes_to_string(&tmp);
				if (string)
					meta_data_add_string(m, keystring, string);
				Py_XDECREF(tmp);
			}
		}
		if (PyErr_Occurred())
			cpy_log_exception("building meta data");
		Py_XDECREF(value);
		Py_DECREF(key);
	}
	return m;
}

static PyObject *Values_dispatch(Values *self, PyObject *args, PyObject *kwds) {
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
	
	static char *kwlist[] = {"type", "values", "plugin_instance", "type_instance",
			"plugin", "host", "time", "interval", "meta", NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etOetetetetdiO", kwlist,
			NULL, &type, &values, NULL, &plugin_instance, NULL, &type_instance,
			NULL, &plugin, NULL, &host, &time, &interval, &meta))
		return NULL;

	if (type[0] == 0) {
		PyErr_SetString(PyExc_RuntimeError, "type not set");
		return NULL;
	}
