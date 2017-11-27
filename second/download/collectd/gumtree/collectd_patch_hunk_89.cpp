 	CPY_RELEASE_THREADS
 }
 
 static PyObject *cpy_register_generic(cpy_callback_t **list_head, PyObject *args, PyObject *kwds) {
 	char buf[512];
 	cpy_callback_t *c;
-	const char *name = NULL;
+	char *name = NULL;
 	PyObject *callback = NULL, *data = NULL, *mod = NULL;
 	static char *kwlist[] = {"callback", "data", "name", NULL};
 	
 	if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oet", kwlist, &callback, &data, NULL, &name) == 0) return NULL;
 	if (PyCallable_Check(callback) == 0) {
+		PyMem_Free(name);
 		PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
 		return NULL;
 	}
 	cpy_build_name(buf, sizeof(buf), callback, name);
 
 	Py_INCREF(callback);
