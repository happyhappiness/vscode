
/* Python 2.4 has this macro, older versions do not. */
#ifndef Py_RETURN_NONE
# define Py_RETURN_NONE return Py_INCREF(Py_None), Py_None
#endif

/* This macro is a shortcut for calls like
 * x = PyObject_Repr(x);
 * This can't be done like this example because this would leak
 * a reference the the original x and crash in case of x == NULL.
 * This calling syntax is less than elegant but it works, saves
 * a lot of lines and avoids potential refcount errors. */

#define CPY_SUBSTITUTE(func, a, ...) do {\
	if ((a) != NULL) {\
		PyObject *__tmp = (a);\
		(a) = func(__VA_ARGS__);\
		Py_DECREF(__tmp);\
	}\
} while(0)

/* Python3 compatibility layer. To keep the actual code as clean as possible
 * do a lot of defines here. */

#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif

#ifdef IS_PY3K

#define PyInt_FromLong PyLong_FromLong
#define CPY_INIT_TYPE         PyVarObject_HEAD_INIT(NULL, 0)
#define IS_BYTES_OR_UNICODE(o) (PyUnicode_Check(o) || PyBytes_Check(o))
#define CPY_STRCAT_AND_DEL(a, b) do {\
	CPY_STRCAT((a), (b));\
	Py_XDECREF((b));\
} while (0)
static inline void CPY_STRCAT(PyObject **a, PyObject *b) {
	PyObject *ret;
	
	if (!a || !*a)
		return;
	
	ret = PyUnicode_Concat(*a, b);
	Py_DECREF(*a);
	*a = ret;
}

#else

#define CPY_INIT_TYPE         PyObject_HEAD_INIT(NULL) 0,
#define IS_BYTES_OR_UNICODE(o) (PyUnicode_Check(o) || PyString_Check(o))
#define CPY_STRCAT_AND_DEL PyString_ConcatAndDel
#define CPY_STRCAT PyString_Concat

#endif

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

void cpy_log_exception(const char *context);

/* Python object declarations. */

typedef struct {
	PyObject_HEAD        /* No semicolon! */
	PyObject *parent;    /* Config */
	PyObject *key;       /* String */
	PyObject *values;    /* Sequence */
	PyObject *children;  /* Sequence */
