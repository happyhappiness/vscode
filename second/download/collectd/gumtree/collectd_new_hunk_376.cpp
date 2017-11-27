		} else if (strcasecmp(item->key, "ModulePath") == 0) {
			char *dir = NULL;
			PyObject *dir_object;
			
			if (cf_util_get_string(item, &dir) != 0) 
				continue;
			dir_object = cpy_string_to_unicode_or_bytes(dir); /* New reference. */
			if (dir_object == NULL) {
				ERROR("python plugin: Unable to convert \"%s\" to "
				      "a python object.", dir);
				free(dir);
				cpy_log_exception("python initialization");
				continue;
