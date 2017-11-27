static inline void CPY_STRCAT(PyObject **a, PyObject *b) {
	PyObject *ret;

	if (!a || !*a)
		return;

	ret = PyUnicode_Concat(*a, b);
	Py_DECREF(*a);
	*a = ret;
}