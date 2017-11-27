	return 0;
}

static int cpy_write_callback(const data_set_t *ds, const value_list_t *value_list, user_data_t *data) {
	int i;
	cpy_callback_t *c = data->data;
	PyObject *ret, *list, *temp, *dict = NULL, *val;
	Values *v;

	CPY_LOCK_THREADS
		list = PyList_New(value_list->values_len); /* New reference. */
		if (list == NULL) {
			cpy_log_exception("write callback");
