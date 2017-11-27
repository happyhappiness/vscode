static PyObject *PluginData_repr(PyObject *s) {
	PyObject *ret;
	static PyObject *l_closing = NULL;

	if (l_closing == NULL)
		l_closing = cpy_string_to_unicode_or_bytes(")");

	if (l_closing == NULL)
		return NULL;

	ret = cpy_common_repr(s);
	CPY_STRCAT(&ret, l_closing);
	return ret;
}