static int cpy_config(oconfig_item_t *ci) {
	int i;
	PyObject *sys, *tb;
	PyObject *sys_path;
	PyObject *module;
	
	/* Ok in theory we shouldn't do initialization at this point
	 * but we have to. In order to give python scripts a chance
	 * to register a config callback we need to be able to execute
	 * python code during the config callback so we have to start
	 * the interpreter here. */
	/* Do *not* use the python "thread" module at this point! */
	Py_Initialize();
	
	PyType_Ready(&ConfigType);
	PyType_Ready(&PluginDataType);
	ValuesType.tp_base = &PluginDataType;
	PyType_Ready(&ValuesType);
	NotificationType.tp_base = &PluginDataType;
	PyType_Ready(&NotificationType);
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
	module = Py_InitModule("collectd", cpy_methods); /* Borrowed reference. */
	PyModule_AddObject(module, "Config", (void *) &ConfigType); /* Steals a reference. */
	PyModule_AddObject(module, "Values", (void *) &ValuesType); /* Steals a reference. */
	PyModule_AddObject(module, "Notification", (void *) &NotificationType); /* Steals a reference. */
	PyModule_AddIntConstant(module, "LOG_DEBUG", LOG_DEBUG);
	PyModule_AddIntConstant(module, "LOG_INFO", LOG_INFO);
	PyModule_AddIntConstant(module, "LOG_NOTICE", LOG_NOTICE);
	PyModule_AddIntConstant(module, "LOG_WARNING", LOG_WARNING);
	PyModule_AddIntConstant(module, "LOG_ERROR", LOG_ERR);
	PyModule_AddIntConstant(module, "NOTIF_FAILURE", NOTIF_FAILURE);
	PyModule_AddIntConstant(module, "NOTIF_WARNING", NOTIF_WARNING);
	PyModule_AddIntConstant(module, "NOTIF_OKAY", NOTIF_OKAY);
	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;
		
		if (strcasecmp(item->key, "Interactive") == 0) {
			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_BOOLEAN)
				continue;
			do_interactive = item->values[0].value.boolean;
		} else if (strcasecmp(item->key, "Encoding") == 0) {
			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_STRING)
				continue;
			/* Why is this even necessary? And undocumented? */
			if (PyUnicode_SetDefaultEncoding(item->values[0].value.string))
				cpy_log_exception("setting default encoding");
		} else if (strcasecmp(item->key, "LogTraces") == 0) {
			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_BOOLEAN)
				continue;
			if (!item->values[0].value.boolean) {
				Py_XDECREF(cpy_format_exception);
				cpy_format_exception = NULL;
				continue;
			}
			if (cpy_format_exception)
				continue;
			tb = PyImport_ImportModule("traceback"); /* New reference. */
			if (tb == NULL) {
				cpy_log_exception("python initialization");
				continue;
			}
			cpy_format_exception = PyObject_GetAttrString(tb, "format_exception"); /* New reference. */
			Py_DECREF(tb);
			if (cpy_format_exception == NULL)
				cpy_log_exception("python initialization");
		} else if (strcasecmp(item->key, "ModulePath") == 0) {
			char *dir = NULL;
			PyObject *dir_object;
			
			if (cf_util_get_string(item, &dir) != 0) 
				continue;
			dir_object = PyString_FromString(dir); /* New reference. */
			if (dir_object == NULL) {
				ERROR("python plugin: Unable to convert \"%s\" to "
				      "a python object.", dir);
				free(dir);
				cpy_log_exception("python initialization");
				continue;
			}
			if (PyList_Append(sys_path, dir_object) != 0) {
				ERROR("python plugin: Unable to append \"%s\" to "
				      "python module path.", dir);
				cpy_log_exception("python initialization");
			}
			Py_DECREF(dir_object);
			free(dir);
		} else if (strcasecmp(item->key, "Import") == 0) {
			char *module_name = NULL;
			PyObject *module;
			
			if (cf_util_get_string(item, &module_name) != 0) 
				continue;
			module = PyImport_ImportModule(module_name); /* New reference. */
			if (module == NULL) {
				ERROR("python plugin: Error importing module \"%s\".", module_name);
				cpy_log_exception("importing module");
				PyErr_Print();
			}
			free(module_name);
			Py_XDECREF(module);
		} else if (strcasecmp(item->key, "Module") == 0) {
			char *name = NULL;
			cpy_callback_t *c;
			PyObject *ret;
			
			if (cf_util_get_string(item, &name) != 0)
				continue;
			for (c = cpy_config_callbacks; c; c = c->next) {
				if (strcasecmp(c->name + 7, name) == 0)
					break;
			}
			if (c == NULL) {
				WARNING("python plugin: Found a configuration for the \"%s\" plugin, "
					"but the plugin isn't loaded or didn't register "
					"a configuration callback.", name);
				free(name);
				continue;
			}
			free(name);
			if (c->data == NULL)
				ret = PyObject_CallFunction(c->callback, "N",
					cpy_oconfig_to_pyconfig(item, NULL)); /* New reference. */
			else
				ret = PyObject_CallFunction(c->callback, "NO",
					cpy_oconfig_to_pyconfig(item, NULL), c->data); /* New reference. */
			if (ret == NULL)
				cpy_log_exception("loading module");
			else
				Py_DECREF(ret);
		} else {
			WARNING("python plugin: Ignoring unknown config key \"%s\".", item->key);
		}
	}
	Py_DECREF(sys_path);
	return 0;
}