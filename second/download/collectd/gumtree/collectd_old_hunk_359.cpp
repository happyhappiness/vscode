
/* Python 2.4 has this macro, older versions do not. */
#ifndef Py_RETURN_NONE
# define Py_RETURN_NONE return Py_INCREF(Py_None), Py_None
#endif

typedef struct {
	PyObject_HEAD        /* No semicolon! */
	PyObject *parent;    /* Config */
	PyObject *key;       /* String */
	PyObject *values;    /* Sequence */
	PyObject *children;  /* Sequence */
