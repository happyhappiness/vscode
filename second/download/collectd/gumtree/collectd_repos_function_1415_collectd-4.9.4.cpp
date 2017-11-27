static void cpy_destroy_user_data(void *data) {
	cpy_callback_t *c = data;
	free(c->name);
	Py_DECREF(c->callback);
	Py_XDECREF(c->data);
	free(c);
}