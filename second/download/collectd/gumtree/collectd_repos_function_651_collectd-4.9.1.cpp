static PyObject *PluginData_repr(PyObject *s) {
	PluginData *self = (PluginData *) s;
	
	return PyString_FromFormat("collectd.Values(type='%s%s%s%s%s%s%s%s%s',time=%lu)", self->type,
			*self->type_instance ? "',type_instance='" : "", self->type_instance,
			*self->plugin ? "',plugin='" : "", self->plugin,
			*self->plugin_instance ? "',plugin_instance='" : "", self->plugin_instance,
			*self->host ? "',host='" : "", self->host,
			(long unsigned) self->time);
}