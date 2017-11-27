static PyObject *cpy_unregister_generic(cpy_callback_t **list_head, PyObject *arg, const char *desc) {
	char buf[512];
	const char *name;
	cpy_callback_t *prev = NULL, *tmp;

	Py_INCREF(arg);
	name = cpy_unicode_or_bytes_to_string(&arg);
	if (name == NULL) {
		PyErr_Clear();
		if (!PyCallable_Check(arg)) {
			PyErr_SetString(PyExc_TypeError, "This function needs a string or a callable object as its only parameter.");
			Py_DECREF(arg);
			return NULL;
		}
		cpy_build_name(buf, sizeof(buf), arg, NULL);
		name = buf;
	}
	for (tmp = *list_head; tmp; prev = tmp, tmp = tmp->next)
		if (strcmp(name, tmp->name) == 0)
			break;

	Py_DECREF(arg);
	if (tmp == NULL) {
		PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.", desc, name);
		return NULL;
	}
	/* Yes, this is actually save. To call this function the caller has to
	 * hold the GIL. Well, save as long as there is only one GIL anyway ... */
	if (prev == NULL)
		*list_head = tmp->next;
	else
		prev->next = tmp->next;
	cpy_destroy_user_data(tmp);
	Py_RETURN_NONE;
}