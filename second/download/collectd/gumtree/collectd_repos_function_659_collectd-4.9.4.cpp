static PyObject *Values_repr(PyObject *s) {
	PyObject *ret, *valuestring = NULL;
	Values *self = (Values *) s;
	
	if (self->values != NULL)
		valuestring = PyObject_Repr(self->values);
	if (valuestring == NULL)
		return NULL;
	
	ret = PyString_FromFormat("collectd.Values(type='%s%s%s%s%s%s%s%s%s',time=%lu,interval=%i,values=%s)", self->data.type,
			*self->data.type_instance ? "',type_instance='" : "", self->data.type_instance,
			*self->data.plugin ? "',plugin='" : "", self->data.plugin,
			*self->data.plugin_instance ? "',plugin_instance='" : "", self->data.plugin_instance,
			*self->data.host ? "',host='" : "", self->data.host,
			(long unsigned) self->data.time, self->interval,
			valuestring ? PyString_AsString(valuestring) : "[]");
	Py_XDECREF(valuestring);
	return ret;
}