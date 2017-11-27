	const char *new;
	
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
		return -1;
	}
	new = PyString_AsString(value);
	if (new == NULL) return -1;
	old = ((char *) self) + (intptr_t) data;
	sstrncpy(old, new, NOTIF_MAX_MSG_LEN);
	return 0;
}

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

static PyMethodDef Notification_methods[] = {
	{"dispatch", (PyCFunction) Notification_dispatch, METH_VARARGS | METH_KEYWORDS, dispatch_doc},
	{NULL}
