	if (ret == NULL)
		return 1;
	return 0;
}

static int cpy_write_callback(const data_set_t *ds, const value_list_t *value_list, user_data_t *data) {
	int i;
	cpy_callback_t *c = data->data;
	PyObject *ret, *list, *temp, *dict = NULL;
	Values *v;

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
