static PyObject *cpy_register_generic(cpy_callback_t **list_head, PyObject *args, PyObject *kwds) {
	char buf[512];
	cpy_callback_t *c;
	const char *name = NULL;
	PyObject *callback = NULL, *data = NULL, *mod = NULL;
	static char *kwlist[] = {"callback", "data", "name", NULL};
	
	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oz", kwlist, &callback, &data, &name) == 0) return NULL;
	if (PyCallable_Check(callback) == 0) {
		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
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
	return PyString_FromString(buf);
}