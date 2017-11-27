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
