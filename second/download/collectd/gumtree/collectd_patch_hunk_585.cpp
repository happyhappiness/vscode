 typedef int reg_function_t(const char *name, void *callback, void *data);
 
 static PyObject *cpy_register_generic_userdata(void *reg, void *handler, PyObject *args, PyObject *kwds) {
 	char buf[512];
 	reg_function_t *register_function = (reg_function_t *) reg;
 	cpy_callback_t *c = NULL;
-	user_data_t user_data;
 	char *name = NULL;
 	PyObject *callback = NULL, *data = NULL;
 	static char *kwlist[] = {"callback", "data", "name", NULL};
-	
+
 	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oet", kwlist, &callback, &data, NULL, &name) == 0) return NULL;
 	if (PyCallable_Check(callback) == 0) {
 		PyMem_Free(name);
 		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
 		return NULL;
 	}
 	cpy_build_name(buf, sizeof(buf), callback, name);
 	PyMem_Free(name);
-	
+
 	Py_INCREF(callback);
 	Py_XINCREF(data);
 
-	c = malloc(sizeof(*c));
+	c = calloc(1, sizeof(*c));
 	if (c == NULL)
 		return NULL;
-	memset (c, 0, sizeof (*c));
 
 	c->name = strdup(buf);
 	c->callback = callback;
 	c->data = data;
 	c->next = NULL;
 
-	memset (&user_data, 0, sizeof (user_data));
-	user_data.free_func = cpy_destroy_user_data;
-	user_data.data = c;
+	user_data_t user_data = {
+		.data = c,
+		.free_func = cpy_destroy_user_data
+	};
 
 	register_function(buf, handler, &user_data);
+	++cpy_num_callbacks;
 	return cpy_string_to_unicode_or_bytes(buf);
 }
 
 static PyObject *cpy_register_read(PyObject *self, PyObject *args, PyObject *kwds) {
 	char buf[512];
 	cpy_callback_t *c = NULL;
-	user_data_t user_data;
 	double interval = 0;
 	char *name = NULL;
 	PyObject *callback = NULL, *data = NULL;
-	struct timespec ts;
 	static char *kwlist[] = {"callback", "interval", "data", "name", NULL};
-	
+
 	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|dOet", kwlist, &callback, &interval, &data, NULL, &name) == 0) return NULL;
 	if (PyCallable_Check(callback) == 0) {
 		PyMem_Free(name);
 		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
 		return NULL;
 	}
 	cpy_build_name(buf, sizeof(buf), callback, name);
 	PyMem_Free(name);
-	
+
 	Py_INCREF(callback);
 	Py_XINCREF(data);
 
-	c = malloc(sizeof(*c));
+	c = calloc(1, sizeof(*c));
 	if (c == NULL)
 		return NULL;
-	memset (c, 0, sizeof (*c));
 
 	c->name = strdup(buf);
 	c->callback = callback;
 	c->data = data;
 	c->next = NULL;
 
-	memset (&user_data, 0, sizeof (user_data));
-	user_data.free_func = cpy_destroy_user_data;
-	user_data.data = c;
+	user_data_t user_data = {
+		.data = c,
+		.free_func = cpy_destroy_user_data
+	};
 
-	ts.tv_sec = interval;
-	ts.tv_nsec = (interval - ts.tv_sec) * 1000000000;
 	plugin_register_complex_read(/* group = */ "python", buf,
-			cpy_read_callback, &ts, &user_data);
-
+			cpy_read_callback, DOUBLE_TO_CDTIME_T (interval), &user_data);
+	++cpy_num_callbacks;
 	return cpy_string_to_unicode_or_bytes(buf);
 }
 
 static PyObject *cpy_register_log(PyObject *self, PyObject *args, PyObject *kwds) {
 	return cpy_register_generic_userdata((void *) plugin_register_log,
 			(void *) cpy_log_callback, args, kwds);
