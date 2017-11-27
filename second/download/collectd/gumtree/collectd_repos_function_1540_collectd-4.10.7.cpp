static int cpy_init(void) {
	cpy_callback_t *c;
	PyObject *ret;
	static pthread_t thread;
	sigset_t sigset;
	
	if (!Py_IsInitialized()) {
		WARNING("python: Plugin loaded but not configured.");
		plugin_unregister_shutdown("python");
		return 0;
	}
	PyEval_InitThreads();
	/* Now it's finally OK to use python threads. */
	for (c = cpy_init_callbacks; c; c = c->next) {
		ret = PyObject_CallFunctionObjArgs(c->callback, c->data, (void *) 0); /* New reference. */
		if (ret == NULL)
			cpy_log_exception("init callback");
		else
			Py_DECREF(ret);
	}
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	pthread_sigmask(SIG_BLOCK, &sigset, NULL);
	state = PyEval_SaveThread();
	if (do_interactive) {
		if (pthread_create(&thread, NULL, cpy_interactive, NULL)) {
			ERROR("python: Error creating thread for interactive interpreter.");
		}
	}

	return 0;
}