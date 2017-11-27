 	return 0;
 }
 
 static int PluginData_settype(PyObject *self, PyObject *value, void *data) {
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
