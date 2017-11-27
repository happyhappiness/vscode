		return NULL;
	}
	cpy_build_name(buf, sizeof(buf), callback, name);

	Py_INCREF(callback);
	Py_XINCREF(data);

	c = malloc(sizeof(*c));
	if (c == NULL)
		return NULL;
	memset (c, 0, sizeof (*c));

	c->name = strdup(buf);
	c->callback = callback;
	c->data = data;
	c->next = *list_head;
	*list_head = c;
	Py_XDECREF(mod);
	PyMem_Free(name);
	return cpy_string_to_unicode_or_bytes(buf);
}

static PyObject *cpy_flush(cpy_callback_t **list_head, PyObject *args, PyObject *kwds) {
	int timeout = -1;
	char *plugin = NULL, *identifier = NULL;
	static char *kwlist[] = {"plugin", "timeout", "identifier", NULL};
	
	if (PyArg_ParseTupleAndKeywords(args, kwds, "|etiet", kwlist, NULL, &plugin, &timeout, NULL, &identifier) == 0) return NULL;
	Py_BEGIN_ALLOW_THREADS
