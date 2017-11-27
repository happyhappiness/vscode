static void Values_dealloc(PyObject *self) {
	Values_clear(self);
	self->ob_type->tp_free(self);
}