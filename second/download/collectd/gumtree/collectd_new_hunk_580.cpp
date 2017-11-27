static char children_doc[] = "This is a tuple of child nodes. For most nodes this will be\n"
		"empty. If this node represents a block instead of a single line of the config\n"
		"file it will contain all nodes in this block.\n";

static PyObject *Config_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
	Config *self;

	self = (Config *) type->tp_alloc(type, 0);
	if (self == NULL)
		return NULL;

	self->parent = NULL;
	self->key = NULL;
	self->values = NULL;
	self->children = NULL;
	return (PyObject *) self;
}

static int Config_init(PyObject *s, PyObject *args, PyObject *kwds) {
	PyObject *key = NULL, *parent = NULL, *values = NULL, *children = NULL, *tmp;
	Config *self = (Config *) s;
	static char *kwlist[] = {"key", "parent", "values", "children", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|OOO", kwlist,
			&key, &parent, &values, &children))
		return -1;

	if (!IS_BYTES_OR_UNICODE(key)) {
		PyErr_SetString(PyExc_TypeError, "argument 1 must be str");
		Py_XDECREF(parent);
		Py_XDECREF(values);
		Py_XDECREF(children);
		return -1;
