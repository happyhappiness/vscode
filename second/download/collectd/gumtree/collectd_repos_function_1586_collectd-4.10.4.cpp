static inline const char *cpy_unicode_or_bytes_to_string(PyObject **o) {
	if (PyUnicode_Check(*o)) {
		PyObject *tmp;
		tmp = PyUnicode_AsEncodedString(*o, NULL, NULL); /* New reference. */
		if (tmp == NULL)
			return NULL;
		Py_DECREF(*o);
		*o = tmp;
	}
#ifdef IS_PY3K
	return PyBytes_AsString(*o);
#else
	return PyString_AsString(*o);
#endif
}