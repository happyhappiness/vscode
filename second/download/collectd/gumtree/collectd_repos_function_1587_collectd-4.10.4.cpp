static inline PyObject *cpy_string_to_unicode_or_bytes(const char *buf) {
#ifdef IS_PY3K
/* Python3 preferrs unicode */
	PyObject *ret;
	ret = PyUnicode_Decode(buf, strlen(buf), NULL, NULL);
	if (ret != NULL)
		return ret;
	PyErr_Clear();
	return PyBytes_FromString(buf);
#else
	return PyString_FromString(buf);
#endif	
}