static void cpy_destroy_user_data(void *data) {
	cpy_callback_t *c = data;
	free(c->name);
	CPY_LOCK_THREADS
	Py_DECREF(c->callback);
	Py_XDECREF(c->data);
	free(c);
	--cpy_num_callbacks;
	if (!cpy_num_callbacks && cpy_shutdown_triggered) {
		Py_Finalize();
		return;
	}
	CPY_RELEASE_THREADS
}