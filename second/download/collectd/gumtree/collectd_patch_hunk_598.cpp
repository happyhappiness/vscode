 	}
 	Py_RETURN_NONE;
 }
 
 static PyObject *Notification_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
 	Notification *self;
-	
+
 	self = (Notification *) PluginData_new(type, args, kwds);
 	if (self == NULL)
 		return NULL;
-	
+
 	self->message[0] = 0;
 	self->severity = 0;
 	return (PyObject *) self;
 }
 
 static int Notification_setstring(PyObject *self, PyObject *value, void *data) {
 	char *old;
 	const char *new;
-	
+
 	if (value == NULL) {
 		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
 		return -1;
 	}
 	Py_INCREF(value);
 	new = cpy_unicode_or_bytes_to_string(&value);
