 
 static PyObject *cpy_register_generic_userdata(void *reg, void *handler, PyObject *args, PyObject *kwds) {
 	char buf[512];
 	reg_function_t *register_function = (reg_function_t *) reg;
 	cpy_callback_t *c = NULL;
 	user_data_t *user_data = NULL;
-	char *name = NULL;
+	const char *name = NULL;
 	PyObject *callback = NULL, *data = NULL;
 	static char *kwlist[] = {"callback", "data", "name", NULL};
 	
 	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oet", kwlist, &callback, &data, NULL, &name) == 0) return NULL;
 	if (PyCallable_Check(callback) == 0) {
-		PyMem_Free(name);
 		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
 		return NULL;
 	}
 	cpy_build_name(buf, sizeof(buf), callback, name);
-	PyMem_Free(name);
 	
 	Py_INCREF(callback);
 	Py_XINCREF(data);
 	c = malloc(sizeof(*c));
 	c->name = strdup(buf);
 	c->callback = callback;
