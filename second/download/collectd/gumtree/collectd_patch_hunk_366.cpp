 	Py_XDECREF(mod);
 	
 	snprintf(buf, size, "python.%p", callback);
 	PyErr_Clear();
 }
 
-static void cpy_log_exception(const char *context) {
+void cpy_log_exception(const char *context) {
 	int l = 0, i;
 	const char *typename = NULL, *message = NULL;
 	PyObject *type, *value, *traceback, *tn, *m, *list;
 	
 	PyErr_Fetch(&type, &value, &traceback);
 	PyErr_NormalizeException(&type, &value, &traceback);
 	if (type == NULL) return;
 	tn = PyObject_GetAttrString(type, "__name__"); /* New reference. */
-	m = PyObject_GetAttrString(value, "message"); /* New reference. */
+	m = PyObject_Str(value); /* New reference. */
 	if (tn != NULL)
-		typename = PyString_AsString(tn);
+		typename = cpy_unicode_or_bytes_to_string(&tn);
 	if (m != NULL)
-		message = PyString_AsString(m);
+		message = cpy_unicode_or_bytes_to_string(&m);
 	if (typename == NULL)
 		typename = "NamelessException";
 	if (message == NULL)
 		message = "N/A";
 	Py_BEGIN_ALLOW_THREADS
 	ERROR("Unhandled python exception in %s: %s: %s", context, typename, message);
