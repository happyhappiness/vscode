 	if (parent == NULL)
 		parent = Py_None;
 	
 	values = PyTuple_New(ci->values_num); /* New reference. */
 	for (i = 0; i < ci->values_num; ++i) {
 		if (ci->values[i].type == OCONFIG_TYPE_STRING) {
-			PyTuple_SET_ITEM(values, i, PyString_FromString(ci->values[i].value.string));
+			PyTuple_SET_ITEM(values, i, cpy_string_to_unicode_or_bytes(ci->values[i].value.string));
 		} else if (ci->values[i].type == OCONFIG_TYPE_NUMBER) {
 			PyTuple_SET_ITEM(values, i, PyFloat_FromDouble(ci->values[i].value.number));
 		} else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN) {
 			PyTuple_SET_ITEM(values, i, PyBool_FromLong(ci->values[i].value.boolean));
 		}
 	}
 	
-	item = PyObject_CallFunction((void *) &ConfigType, "sONO", ci->key, parent, values, Py_None);
+	tmp = cpy_string_to_unicode_or_bytes(ci->key);
+	item = PyObject_CallFunction((void *) &ConfigType, "NONO", tmp, parent, values, Py_None);
 	if (item == NULL)
 		return NULL;
 	children = PyTuple_New(ci->children_num); /* New reference. */
 	for (i = 0; i < ci->children_num; ++i) {
 		PyTuple_SET_ITEM(children, i, cpy_oconfig_to_pyconfig(ci->children + i, item));
 	}
 	tmp = ((Config *) item)->children;
 	((Config *) item)->children = children;
 	Py_XDECREF(tmp);
 	return item;
 }
 
+#ifdef IS_PY3K
+static struct PyModuleDef collectdmodule = {
+	PyModuleDef_HEAD_INIT,
+	"collectd",   /* name of module */
+	"The python interface to collectd", /* module documentation, may be NULL */
+	-1,
+	cpy_methods
+};
+
+PyMODINIT_FUNC PyInit_collectd(void) {
+	return PyModule_Create(&collectdmodule);
+}
+#endif
+
 static int cpy_config(oconfig_item_t *ci) {
 	int i;
-	char *argv = "";
 	PyObject *sys, *tb;
 	PyObject *sys_path;
 	PyObject *module;
 	
 	/* Ok in theory we shouldn't do initialization at this point
 	 * but we have to. In order to give python scripts a chance
 	 * to register a config callback we need to be able to execute
 	 * python code during the config callback so we have to start
 	 * the interpreter here. */
 	/* Do *not* use the python "thread" module at this point! */
+
+#ifdef IS_PY3K
+	/* Add a builtin module, before Py_Initialize */
+	PyImport_AppendInittab("collectd", PyInit_collectd);
+#endif
+	
 	Py_Initialize();
 	
 	PyType_Ready(&ConfigType);
 	PyType_Ready(&PluginDataType);
 	ValuesType.tp_base = &PluginDataType;
 	PyType_Ready(&ValuesType);
 	NotificationType.tp_base = &PluginDataType;
 	PyType_Ready(&NotificationType);
+	SignedType.tp_base = &PyLong_Type;
+	PyType_Ready(&SignedType);
+	UnsignedType.tp_base = &PyLong_Type;
+	PyType_Ready(&UnsignedType);
 	sys = PyImport_ImportModule("sys"); /* New reference. */
 	if (sys == NULL) {
 		cpy_log_exception("python initialization");
 		return 1;
 	}
 	sys_path = PyObject_GetAttrString(sys, "path"); /* New reference. */
 	Py_DECREF(sys);
 	if (sys_path == NULL) {
 		cpy_log_exception("python initialization");
 		return 1;
 	}
-	PySys_SetArgv(1, &argv);
-	PyList_SetSlice(sys_path, 0, 1, NULL);
-
+#ifdef IS_PY3K
+	module = PyImport_ImportModule("collectd");
+#else
 	module = Py_InitModule("collectd", cpy_methods); /* Borrowed reference. */
+#endif
 	PyModule_AddObject(module, "Config", (void *) &ConfigType); /* Steals a reference. */
 	PyModule_AddObject(module, "Values", (void *) &ValuesType); /* Steals a reference. */
 	PyModule_AddObject(module, "Notification", (void *) &NotificationType); /* Steals a reference. */
+	PyModule_AddObject(module, "Signed", (void *) &SignedType); /* Steals a reference. */
+	PyModule_AddObject(module, "Unsigned", (void *) &UnsignedType); /* Steals a reference. */
 	PyModule_AddIntConstant(module, "LOG_DEBUG", LOG_DEBUG);
 	PyModule_AddIntConstant(module, "LOG_INFO", LOG_INFO);
 	PyModule_AddIntConstant(module, "LOG_NOTICE", LOG_NOTICE);
 	PyModule_AddIntConstant(module, "LOG_WARNING", LOG_WARNING);
 	PyModule_AddIntConstant(module, "LOG_ERROR", LOG_ERR);
 	PyModule_AddIntConstant(module, "NOTIF_FAILURE", NOTIF_FAILURE);
