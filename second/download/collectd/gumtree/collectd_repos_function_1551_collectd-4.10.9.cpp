static int cpy_init_python() {
	char *argv = "";
	PyObject *sys;
	PyObject *module;

#ifdef IS_PY3K
	/* Add a builtin module, before Py_Initialize */
	PyImport_AppendInittab("collectd", PyInit_collectd);
#endif
	
	Py_Initialize();
	
	PyType_Ready(&ConfigType);
	PyType_Ready(&PluginDataType);
	ValuesType.tp_base = &PluginDataType;
	PyType_Ready(&ValuesType);
	NotificationType.tp_base = &PluginDataType;
	PyType_Ready(&NotificationType);
	SignedType.tp_base = &PyLong_Type;
	PyType_Ready(&SignedType);
	UnsignedType.tp_base = &PyLong_Type;
	PyType_Ready(&UnsignedType);
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
	PySys_SetArgv(1, &argv);
	PyList_SetSlice(sys_path, 0, 1, NULL);

#ifdef IS_PY3K
	module = PyImport_ImportModule("collectd");
#else
	module = Py_InitModule("collectd", cpy_methods); /* Borrowed reference. */
#endif
	PyModule_AddObject(module, "Config", (void *) &ConfigType); /* Steals a reference. */
	PyModule_AddObject(module, "Values", (void *) &ValuesType); /* Steals a reference. */
	PyModule_AddObject(module, "Notification", (void *) &NotificationType); /* Steals a reference. */
	PyModule_AddObject(module, "Signed", (void *) &SignedType); /* Steals a reference. */
	PyModule_AddObject(module, "Unsigned", (void *) &UnsignedType); /* Steals a reference. */
	PyModule_AddIntConstant(module, "LOG_DEBUG", LOG_DEBUG);
	PyModule_AddIntConstant(module, "LOG_INFO", LOG_INFO);
	PyModule_AddIntConstant(module, "LOG_NOTICE", LOG_NOTICE);
	PyModule_AddIntConstant(module, "LOG_WARNING", LOG_WARNING);
	PyModule_AddIntConstant(module, "LOG_ERROR", LOG_ERR);
	PyModule_AddIntConstant(module, "NOTIF_FAILURE", NOTIF_FAILURE);
	PyModule_AddIntConstant(module, "NOTIF_WARNING", NOTIF_WARNING);
	PyModule_AddIntConstant(module, "NOTIF_OKAY", NOTIF_OKAY);
	return 0;
}