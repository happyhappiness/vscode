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
	
	if ((meta == NULL) || (meta == Py_None))
		return NULL;

	l = PyDict_Items(meta); /* New reference. */
	if (!l) {
		cpy_log_exception("building meta data");
