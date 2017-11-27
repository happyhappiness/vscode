	return 0;
}

static int cpy_write_callback(const data_set_t *ds, const value_list_t *value_list, user_data_t *data) {
	int i;
	cpy_callback_t *c = data->data;
	PyObject *ret, *v, *list;

	CPY_LOCK_THREADS
		list = PyList_New(value_list->values_len); /* New reference. */
		if (list == NULL) {
			cpy_log_exception("write callback");
			CPY_RETURN_FROM_THREADS 0;
		}
		for (i = 0; i < value_list->values_len; ++i) {
			if (ds->ds[i].type == DS_TYPE_COUNTER) {
				if ((long) value_list->values[i].counter == value_list->values[i].counter)
					PyList_SetItem(list, i, PyInt_FromLong(value_list->values[i].counter));
				else
					PyList_SetItem(list, i, PyLong_FromUnsignedLongLong(value_list->values[i].counter));
			} else if (ds->ds[i].type == DS_TYPE_GAUGE) {
				PyList_SetItem(list, i, PyFloat_FromDouble(value_list->values[i].gauge));
			} else if (ds->ds[i].type == DS_TYPE_DERIVE) {
				if ((long) value_list->values[i].derive == value_list->values[i].derive)
					PyList_SetItem(list, i, PyInt_FromLong(value_list->values[i].derive));
				else
					PyList_SetItem(list, i, PyLong_FromLongLong(value_list->values[i].derive));
			} else if (ds->ds[i].type == DS_TYPE_ABSOLUTE) {
				if ((long) value_list->values[i].absolute == value_list->values[i].absolute)
					PyList_SetItem(list, i, PyInt_FromLong(value_list->values[i].absolute));
				else
					PyList_SetItem(list, i, PyLong_FromUnsignedLongLong(value_list->values[i].absolute));
			} else {
				Py_BEGIN_ALLOW_THREADS
				ERROR("cpy_write_callback: Unknown value type %d.", ds->ds[i].type);
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
	return 0;
}

static int cpy_notification_callback(const notification_t *notification, user_data_t *data) {
	cpy_callback_t *c = data->data;
	PyObject *ret, *n;

	CPY_LOCK_THREADS
		n = PyObject_CallFunction((void *) &NotificationType, "ssssssdi", notification->type, notification->message,
				notification->plugin_instance, notification->type_instance, notification->plugin,
				notification->host, (double) notification->time, notification->severity); /* New reference. */
		ret = PyObject_CallFunctionObjArgs(c->callback, n, c->data, (void *) 0); /* New reference. */
		Py_XDECREF(n);
		if (ret == NULL) {
			cpy_log_exception("notification callback");
		} else {
			Py_DECREF(ret);
		}
	CPY_RELEASE_THREADS
	return 0;
}

static void cpy_log_callback(int severity, const char *message, user_data_t *data) {
	cpy_callback_t * c = data->data;
	PyObject *ret;

	CPY_LOCK_THREADS
	if (c->data == NULL)
		ret = PyObject_CallFunction(c->callback, "is", severity, message); /* New reference. */
	else
		ret = PyObject_CallFunction(c->callback, "isO", severity, message, c->data); /* New reference. */

	if (ret == NULL) {
		/* FIXME */
		/* Do we really want to trigger a log callback because a log callback failed?
		 * Probably not. */
		PyErr_Print();
