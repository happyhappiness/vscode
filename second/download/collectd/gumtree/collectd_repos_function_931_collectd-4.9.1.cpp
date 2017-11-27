static PyObject *Config_repr(PyObject *s) {
	Config *self = (Config *) s;
	
	return PyString_FromFormat("<collectd.Config %snode %s>", self->parent == Py_None ? "root " : "", PyString_AsString(PyObject_Str(self->key)));
}