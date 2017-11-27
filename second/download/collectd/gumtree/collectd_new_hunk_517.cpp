			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_BOOLEAN)
				continue;
			do_interactive = item->values[0].value.boolean;
		} else if (strcasecmp(item->key, "Encoding") == 0) {
			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_STRING)
				continue;
#ifdef IS_PY3K
			NOTICE("python: \"Encoding\" was used in the config file but Python3 was used, which does not support changing encodings. Ignoring this.");
#else
			/* Why is this even necessary? And undocumented? */
			if (PyUnicode_SetDefaultEncoding(item->values[0].value.string))
				cpy_log_exception("setting default encoding");
#endif
		} else if (strcasecmp(item->key, "LogTraces") == 0) {
			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_BOOLEAN)
				continue;
			if (!item->values[0].value.boolean) {
				Py_XDECREF(cpy_format_exception);
				cpy_format_exception = NULL;
