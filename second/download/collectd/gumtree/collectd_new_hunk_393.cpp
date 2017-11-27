	meta_data_t *m = NULL;
	PyObject *l;
	
	if (!meta)
		return NULL;

	l = PyDict_Items(meta); /* New reference. */
	if (!l) {
		cpy_log_exception("building meta data");
		return NULL;
	}
	m = meta_data_create();
	s = PyList_Size(l);
	for (i = 0; i < s; ++i) {
		const char *string, *keystring;
		PyObject *key, *value, *item, *tmp;
		
		item = PyList_GET_ITEM(l, i);
