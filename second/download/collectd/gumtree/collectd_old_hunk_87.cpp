			if (PyErr_Occurred() != NULL) {
				cpy_log_exception("value building for write callback");
				Py_DECREF(list);
				CPY_RETURN_FROM_THREADS 0;
			}
		}
		dict = PyDict_New();
		if (value_list->meta) {
			int i, num;
			char **table;
			meta_data_t *meta = value_list->meta;

			num = meta_data_toc(meta, &table);
