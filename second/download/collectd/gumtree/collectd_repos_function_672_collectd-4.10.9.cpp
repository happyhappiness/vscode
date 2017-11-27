static PyObject *Values_repr(PyObject *s) {
	PyObject *ret, *tmp;
	static PyObject *l_interval = NULL, *l_values = NULL, *l_meta = NULL, *l_closing = NULL;
	Values *self = (Values *) s;
	
	if (l_interval == NULL)
		l_interval = cpy_string_to_unicode_or_bytes(",interval=");
	if (l_values == NULL)
		l_values = cpy_string_to_unicode_or_bytes(",values=");
	if (l_meta == NULL)
		l_meta = cpy_string_to_unicode_or_bytes(",meta=");
	if (l_closing == NULL)
		l_closing = cpy_string_to_unicode_or_bytes(")");
	
	if (l_interval == NULL || l_values == NULL || l_meta == NULL || l_closing == NULL)
		return NULL;
	
	ret = cpy_common_repr(s);
	if (self->interval != 0) {
		CPY_STRCAT(&ret, l_interval);
		tmp = PyInt_FromLong(self->interval);
		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}
	if (self->values && (!PyList_Check(self->values) || PySequence_Length(self->values) > 0)) {
		CPY_STRCAT(&ret, l_values);
		tmp = PyObject_Repr(self->values);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}
	if (self->meta && (!PyDict_Check(self->meta) || PyDict_Size(self->meta) > 0)) {
		CPY_STRCAT(&ret, l_meta);
		tmp = PyObject_Repr(self->meta);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}
	CPY_STRCAT(&ret, l_closing);
	return ret;
}