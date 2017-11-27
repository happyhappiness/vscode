		return NULL;
	}
	value = malloc(size * sizeof(*value));
	for (i = 0; i < size; ++i) {
		PyObject *item, *num;
		item = PySequence_Fast_GET_ITEM(values, i); /* Borrowed reference. */
		switch (ds->ds[i].type) {
		case DS_TYPE_COUNTER:
			num = PyNumber_Long(item); /* New reference. */
			if (num != NULL) {
				value[i].counter = PyLong_AsUnsignedLongLong(num);
				Py_XDECREF(num);
			}
			break;
		case DS_TYPE_GAUGE:
			num = PyNumber_Float(item); /* New reference. */
			if (num != NULL) {
				value[i].gauge = PyFloat_AsDouble(num);
				Py_XDECREF(num);
			}
			break;
		case DS_TYPE_DERIVE:
			/* This might overflow without raising an exception.
			 * Not much we can do about it */
			num = PyNumber_Long(item); /* New reference. */
			if (num != NULL) {
				value[i].derive = PyLong_AsLongLong(num);
				Py_XDECREF(num);
			}
			break;
		case DS_TYPE_ABSOLUTE:
			/* This might overflow without raising an exception.
			 * Not much we can do about it */
			num = PyNumber_Long(item); /* New reference. */
			if (num != NULL) {
				value[i].absolute = PyLong_AsUnsignedLongLong(num);
				Py_XDECREF(num);
			}
			break;
		default:
			free(value);
			PyErr_Format(PyExc_RuntimeError, "unknown data type %d for %s", ds->ds[i].type, value_list.type);
			return NULL;
		}
		if (PyErr_Occurred() != NULL) {
			free(value);
			return NULL;
		}
