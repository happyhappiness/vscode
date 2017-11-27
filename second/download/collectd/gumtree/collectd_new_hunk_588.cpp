	PyModule_AddStringConstant(module, "DS_TYPE_DERIVE", DS_TYPE_TO_STRING(DS_TYPE_DERIVE));
	PyModule_AddStringConstant(module, "DS_TYPE_ABSOLUTE", DS_TYPE_TO_STRING(DS_TYPE_ABSOLUTE));
	return 0;
}

static int cpy_config(oconfig_item_t *ci) {
	PyObject *tb;
	int status = 0;

	/* Ok in theory we shouldn't do initialization at this point
	 * but we have to. In order to give python scripts a chance
	 * to register a config callback we need to be able to execute
	 * python code during the config callback so we have to start
	 * the interpreter here. */
	/* Do *not* use the python "thread" module at this point! */

	if (!Py_IsInitialized() && cpy_init_python()) return 1;

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		if (strcasecmp(item->key, "Interactive") == 0) {
			if (cf_util_get_boolean(item, &do_interactive) != 0) {
				status = 1;
				continue;
			}
		} else if (strcasecmp(item->key, "Encoding") == 0) {
			char *encoding = NULL;
			if (cf_util_get_string(item, &encoding) != 0) {
				status = 1;
				continue;
			}
#ifdef IS_PY3K
			ERROR("python: \"Encoding\" was used in the config file but Python3 was used, which does not support changing encodings");
			status = 1;
			sfree(encoding);
			continue;
#else
			/* Why is this even necessary? And undocumented? */
			if (PyUnicode_SetDefaultEncoding(encoding)) {
				cpy_log_exception("setting default encoding");
				status = 1;
			}
#endif
			sfree(encoding);
		} else if (strcasecmp(item->key, "LogTraces") == 0) {
			_Bool log_traces;
			if (cf_util_get_boolean(item, &log_traces) != 0) {
				status = 1;
				continue;
			}
			if (!log_traces) {
				Py_XDECREF(cpy_format_exception);
				cpy_format_exception = NULL;
				continue;
			}
			if (cpy_format_exception)
				continue;
			tb = PyImport_ImportModule("traceback"); /* New reference. */
			if (tb == NULL) {
				cpy_log_exception("python initialization");
				status = 1;
				continue;
			}
			cpy_format_exception = PyObject_GetAttrString(tb, "format_exception"); /* New reference. */
			Py_DECREF(tb);
			if (cpy_format_exception == NULL) {
				cpy_log_exception("python initialization");
				status = 1;
			}
		} else if (strcasecmp(item->key, "ModulePath") == 0) {
			char *dir = NULL;
			PyObject *dir_object;

			if (cf_util_get_string(item, &dir) != 0) {
				status = 1;
				continue;
			}
			dir_object = cpy_string_to_unicode_or_bytes(dir); /* New reference. */
			if (dir_object == NULL) {
				ERROR("python plugin: Unable to convert \"%s\" to "
				      "a python object.", dir);
				free(dir);
				cpy_log_exception("python initialization");
				status = 1;
				continue;
			}
			if (PyList_Insert(sys_path, 0, dir_object) != 0) {
				ERROR("python plugin: Unable to prepend \"%s\" to "
				      "python module path.", dir);
				cpy_log_exception("python initialization");
				status = 1;
			}
			Py_DECREF(dir_object);
			free(dir);
		} else if (strcasecmp(item->key, "Import") == 0) {
			char *module_name = NULL;
			PyObject *module;

			if (cf_util_get_string(item, &module_name) != 0) {
				status = 1;
				continue;
			}
			module = PyImport_ImportModule(module_name); /* New reference. */
			if (module == NULL) {
				ERROR("python plugin: Error importing module \"%s\".", module_name);
				cpy_log_exception("importing module");
				status = 1;
			}
			free(module_name);
			Py_XDECREF(module);
		} else if (strcasecmp(item->key, "Module") == 0) {
			char *name = NULL;
			cpy_callback_t *c;
			PyObject *ret;

			if (cf_util_get_string(item, &name) != 0) {
				status = 1;
				continue;
			}
			for (c = cpy_config_callbacks; c; c = c->next) {
				if (strcasecmp(c->name + 7, name) == 0)
					break;
			}
			if (c == NULL) {
				WARNING("python plugin: Found a configuration for the \"%s\" plugin, "
