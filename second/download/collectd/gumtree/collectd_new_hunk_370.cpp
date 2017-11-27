	cpy_callback_t *c = NULL;
	user_data_t *user_data = NULL;
	const char *name = NULL;
	PyObject *callback = NULL, *data = NULL;
	static char *kwlist[] = {"callback", "data", "name", NULL};
	
	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oet", kwlist, &callback, &data, NULL, &name) == 0) return NULL;
	if (PyCallable_Check(callback) == 0) {
		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
		return NULL;
	}
	cpy_build_name(buf, sizeof(buf), callback, name);
	
