		return NULL;
	}
	cpy_build_name(buf, sizeof(buf), callback, name);

	Py_INCREF(callback);
	Py_XINCREF(data);
	c = malloc(sizeof(*c));
	c->name = strdup(buf);
	c->callback = callback;
	c->data = data;
	c->next = *list_head;
	*list_head = c;
	Py_XDECREF(mod);
	PyMem_Free(name);
	return cpy_string_to_unicode_or_bytes(buf);
}

static PyObject *float_or_none(float number) {
	if (isnan(number)) {
		Py_RETURN_NONE;
	}
	return PyFloat_FromDouble(number);
}

static PyObject *cpy_get_dataset(PyObject *self, PyObject *args) {
	int i;
	char *name;
	const data_set_t *ds;
	PyObject *list, *tuple;

	if (PyArg_ParseTuple(args, "et", NULL, &name) == 0) return NULL;
	ds = plugin_get_ds(name);
	PyMem_Free(name);
	if (ds == NULL) {
		PyErr_Format(PyExc_TypeError, "Dataset %s not found", name);
		return NULL;
	}
	list = PyList_New(ds->ds_num); /* New reference. */
	for (i = 0; i < ds->ds_num; ++i) {
		tuple = PyTuple_New(4);
		PyTuple_SET_ITEM(tuple, 0, cpy_string_to_unicode_or_bytes(ds->ds[i].name));
		PyTuple_SET_ITEM(tuple, 1, cpy_string_to_unicode_or_bytes(DS_TYPE_TO_STRING(ds->ds[i].type)));
		PyTuple_SET_ITEM(tuple, 2, float_or_none(ds->ds[i].min));
		PyTuple_SET_ITEM(tuple, 3, float_or_none(ds->ds[i].max));
		PyList_SET_ITEM(list, i, tuple);
	}
	return list;
}

static PyObject *cpy_flush(PyObject *self, PyObject *args, PyObject *kwds) {
	int timeout = -1;
	char *plugin = NULL, *identifier = NULL;
	static char *kwlist[] = {"plugin", "timeout", "identifier", NULL};
	
	if (PyArg_ParseTupleAndKeywords(args, kwds, "|etiet", kwlist, NULL, &plugin, &timeout, NULL, &identifier) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
