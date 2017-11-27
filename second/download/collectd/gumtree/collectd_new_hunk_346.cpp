				Py_END_ALLOW_THREADS
				Py_DECREF(list);
				CPY_RETURN_FROM_THREADS 0;
			}
			if (PyErr_Occurred() != NULL) {
				cpy_log_exception("value building for write callback");
				Py_DECREF(list);
				CPY_RETURN_FROM_THREADS 0;
			}
		}
		v = PyObject_CallFunction((void *) &ValuesType, "sOssssdi", value_list->type,
				list, value_list->plugin_instance, value_list->type_instance,
				value_list->plugin, value_list->host, (double) value_list->time,
				value_list->interval); /* New reference. */
		Py_DECREF(list);
		ret = PyObject_CallFunctionObjArgs(c->callback, v, c->data, (void *) 0); /* New reference. */
		Py_XDECREF(v);
		if (ret == NULL) {
			cpy_log_exception("write callback");
		} else {
			Py_DECREF(ret);
		}
	CPY_RELEASE_THREADS
