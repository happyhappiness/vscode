	sys_path = PyObject_GetAttrString(sys, "path"); /* New reference. */
	Py_DECREF(sys);
	if (sys_path == NULL) {
		cpy_log_exception("python initialization");
		return 1;
	}
#ifdef IS_PY3K
	module = PyImport_ImportModule("collectd");
#else
	module = Py_InitModule("collectd", cpy_methods); /* Borrowed reference. */
#endif
	PyModule_AddObject(module, "Config", (void *) &ConfigType); /* Steals a reference. */
