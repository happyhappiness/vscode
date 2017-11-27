			if (num != NULL) {
				value[i].absolute = PyLong_AsUnsignedLongLong(num);
				Py_XDECREF(num);
			}
		} else {
			free(value);
			PyErr_Format(PyExc_RuntimeError, "unknown data type %d for %s", ds->ds->type, type);
			return NULL;
		}
		if (PyErr_Occurred() != NULL) {
			free(value);
			return NULL;
		}
	}
	value_list.values = value;
	value_list.meta = cpy_build_meta(meta);
	value_list.values_len = size;
	value_list.time = time;
	value_list.interval = interval;
	sstrncpy(value_list.host, host, sizeof(value_list.host));
	sstrncpy(value_list.plugin, plugin, sizeof(value_list.plugin));
	sstrncpy(value_list.plugin_instance, plugin_instance, sizeof(value_list.plugin_instance));
	sstrncpy(value_list.type, type, sizeof(value_list.type));
	sstrncpy(value_list.type_instance, type_instance, sizeof(value_list.type_instance));
	if (value_list.host[0] == 0)
		sstrncpy(value_list.host, hostname_g, sizeof(value_list.host));
	if (value_list.plugin[0] == 0)
		sstrncpy(value_list.plugin, "python", sizeof(value_list.plugin));
	Py_BEGIN_ALLOW_THREADS;
	ret = plugin_dispatch_values(&value_list);
