static PyObject *PluginData_getstring(PyObject *self, void *data) {
	const char *value = ((char *) self) + (intptr_t) data;

	return cpy_string_to_unicode_or_bytes(value);
}