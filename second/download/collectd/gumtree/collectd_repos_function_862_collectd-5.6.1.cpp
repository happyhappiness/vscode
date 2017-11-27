static PyObject *Notification_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
	Notification *self;

	self = (Notification *) PluginData_new(type, args, kwds);
	if (self == NULL)
		return NULL;

	self->message[0] = 0;
	self->severity = 0;
	return (PyObject *) self;
}