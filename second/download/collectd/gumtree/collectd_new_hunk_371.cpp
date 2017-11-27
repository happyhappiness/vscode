	c->data = data;
	c->next = NULL;
	user_data = malloc(sizeof(*user_data));
	user_data->free_func = cpy_destroy_user_data;
	user_data->data = c;
	register_function(buf, handler, user_data);
	return cpy_string_to_unicode_or_bytes(buf);
}

static PyObject *cpy_register_read(PyObject *self, PyObject *args, PyObject *kwds) {
	char buf[512];
	cpy_callback_t *c = NULL;
	user_data_t *user_data = NULL;
	double interval = 0;
	const char *name = NULL;
	PyObject *callback = NULL, *data = NULL;
	struct timespec ts;
	static char *kwlist[] = {"callback", "interval", "data", "name", NULL};
	
	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|dOet", kwlist, &callback, &interval, &data, NULL, &name) == 0) return NULL;
	if (PyCallable_Check(callback) == 0) {
		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
		return NULL;
	}
	cpy_build_name(buf, sizeof(buf), callback, name);
	
