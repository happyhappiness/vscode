static PyObject *Notification_repr(PyObject *s) {
	PyObject *ret;
	Notification *self = (Notification *) s;
	
	ret = PyString_FromFormat("collectd.Values(type='%s%s%s%s%s%s%s%s%s%s%s',time=%lu,interval=%i)", self->data.type,
			*self->data.type_instance ? "',type_instance='" : "", self->data.type_instance,
			*self->data.plugin ? "',plugin='" : "", self->data.plugin,
			*self->data.plugin_instance ? "',plugin_instance='" : "", self->data.plugin_instance,
			*self->data.host ? "',host='" : "", self->data.host,
			*self->message ? "',message='" : "", self->message,
			(long unsigned) self->data.time, self->severity);
	return ret;
}