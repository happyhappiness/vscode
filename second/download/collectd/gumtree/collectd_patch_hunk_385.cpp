 	const char *new;
 	
 	if (value == NULL) {
 		PyErr_SetString(PyExc_TypeError, "Cannot delete this attribute");
 		return -1;
 	}
-	new = PyString_AsString(value);
-	if (new == NULL) return -1;
+	Py_INCREF(value);
+	new = cpy_unicode_or_bytes_to_string(&value);
+	if (new == NULL) {
+		Py_DECREF(value);
+		return -1;
+	}
 	old = ((char *) self) + (intptr_t) data;
 	sstrncpy(old, new, NOTIF_MAX_MSG_LEN);
+	Py_DECREF(value);
 	return 0;
 }
 
 static PyObject *Notification_repr(PyObject *s) {
-	PyObject *ret;
+	PyObject *ret, *tmp;
+	static PyObject *l_severity = NULL, *l_message = NULL, *l_closing = NULL;
 	Notification *self = (Notification *) s;
 	
-	ret = PyString_FromFormat("collectd.Values(type='%s%s%s%s%s%s%s%s%s%s%s',time=%lu,interval=%i)", self->data.type,
-			*self->data.type_instance ? "',type_instance='" : "", self->data.type_instance,
-			*self->data.plugin ? "',plugin='" : "", self->data.plugin,
-			*self->data.plugin_instance ? "',plugin_instance='" : "", self->data.plugin_instance,
-			*self->data.host ? "',host='" : "", self->data.host,
-			*self->message ? "',message='" : "", self->message,
-			(long unsigned) self->data.time, self->severity);
+	if (l_severity == NULL)
+		l_severity = cpy_string_to_unicode_or_bytes(",severity=");
+	if (l_message == NULL)
+		l_message = cpy_string_to_unicode_or_bytes(",message=");
+	if (l_closing == NULL)
+		l_closing = cpy_string_to_unicode_or_bytes(")");
+	
+	if (l_severity == NULL || l_message == NULL || l_closing == NULL)
+		return NULL;
+	
+	ret = cpy_common_repr(s);
+	if (self->severity != 0) {
+		CPY_STRCAT(&ret, l_severity);
+		tmp = PyInt_FromLong(self->severity);
+		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
+		CPY_STRCAT_AND_DEL(&ret, tmp);
+	}
+	if (self->message[0] != 0) {
+		CPY_STRCAT(&ret, l_message);
+		tmp = cpy_string_to_unicode_or_bytes(self->message);
+		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
+		CPY_STRCAT_AND_DEL(&ret, tmp);
+	}
+	CPY_STRCAT(&ret, l_closing);
 	return ret;
 }
 
 static PyMethodDef Notification_methods[] = {
 	{"dispatch", (PyCFunction) Notification_dispatch, METH_VARARGS | METH_KEYWORDS, dispatch_doc},
 	{NULL}
