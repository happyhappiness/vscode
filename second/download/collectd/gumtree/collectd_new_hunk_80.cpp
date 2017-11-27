		}
		if (PyErr_Occurred())
			cpy_log_exception("building meta data");
		Py_XDECREF(value);
		Py_DECREF(key);
	}
	Py_XDECREF(l);
	return m;
}

static PyObject *Values_dispatch(Values *self, PyObject *args, PyObject *kwds) {
	int i, ret;
	const data_set_t *ds;
