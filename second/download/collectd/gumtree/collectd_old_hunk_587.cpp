	{"unregister_flush", cpy_unregister_flush, METH_O, unregister_doc},
	{"unregister_shutdown", cpy_unregister_shutdown, METH_O, unregister_doc},
	{0, 0, 0, 0}
};

static int cpy_shutdown(void) {
	cpy_callback_t *c;
	PyObject *ret;
	
	/* This can happen if the module was loaded but not configured. */
	if (state != NULL)
		PyEval_RestoreThread(state);

	for (c = cpy_shutdown_callbacks; c; c = c->next) {
		ret = PyObject_CallFunctionObjArgs(c->callback, c->data, (void *) 0); /* New reference. */
		if (ret == NULL)
			cpy_log_exception("shutdown callback");
		else
			Py_DECREF(ret);
	}
	PyErr_Print();
	Py_Finalize();
	return 0;
}

static void cpy_int_handler(int sig) {
	return;
}

static void *cpy_interactive(void *data) {
	sigset_t sigset;
	struct sigaction sig_int_action, old;
	
	/* Signal handler in a plugin? Bad stuff, but the best way to
	 * handle it I guess. In an interactive session people will
	 * press Ctrl+C at some time, which will generate a SIGINT.
	 * This will cause collectd to shutdown, thus killing the
	 * interactive interpreter, and leaving the terminal in a
	 * mess. Chances are, this isn't what the user wanted to do.
	 * 
	 * So this is the plan:
	 * 1. Block SIGINT in the main thread.
	 * 2. Install our own signal handler that does nothing.
	 * 3. Unblock SIGINT in the interactive thread.
	 *
	 * This will make sure that SIGINT won't kill collectd but
	 * still interrupt syscalls like sleep and pause.
	 * It does not raise a KeyboardInterrupt exception because so
	 * far nobody managed to figure out how to do that. */
	memset (&sig_int_action, '\0', sizeof (sig_int_action));
	sig_int_action.sa_handler = cpy_int_handler;
	sigaction (SIGINT, &sig_int_action, &old);
	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);
	PyEval_AcquireThread(state);
	if (PyImport_ImportModule("readline") == NULL) {
		/* This interactive session will suck. */
		cpy_log_exception("interactive session init");
	}
	PyRun_InteractiveLoop(stdin, "<stdin>");
	PyErr_Print();
	PyEval_ReleaseThread(state);
	NOTICE("python: Interactive interpreter exited, stopping collectd ...");
	/* Restore the original collectd SIGINT handler and raise SIGINT.
	 * The main thread still has SIGINT blocked and there's nothing we
	 * can do about that so this thread will handle it. But that's not
	 * important, except that it won't interrupt the main loop and so
	 * it might take a few seconds before collectd really shuts down. */
	sigaction (SIGINT, &old, NULL);
	raise(SIGINT);
	pause();
	return NULL;
}

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
		if (plugin_thread_create(&thread, NULL, cpy_interactive, NULL)) {
			ERROR("python: Error creating thread for interactive interpreter.");
		}
	}

	return 0;
}

static PyObject *cpy_oconfig_to_pyconfig(oconfig_item_t *ci, PyObject *parent) {
	int i;
	PyObject *item, *values, *children, *tmp;
	
	if (parent == NULL)
		parent = Py_None;
	
	values = PyTuple_New(ci->values_num); /* New reference. */
	for (i = 0; i < ci->values_num; ++i) {
		if (ci->values[i].type == OCONFIG_TYPE_STRING) {
			PyTuple_SET_ITEM(values, i, cpy_string_to_unicode_or_bytes(ci->values[i].value.string));
		} else if (ci->values[i].type == OCONFIG_TYPE_NUMBER) {
			PyTuple_SET_ITEM(values, i, PyFloat_FromDouble(ci->values[i].value.number));
		} else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN) {
			PyTuple_SET_ITEM(values, i, PyBool_FromLong(ci->values[i].value.boolean));
		}
	}
	
	tmp = cpy_string_to_unicode_or_bytes(ci->key);
	item = PyObject_CallFunction((void *) &ConfigType, "NONO", tmp, parent, values, Py_None);
	if (item == NULL)
		return NULL;
	children = PyTuple_New(ci->children_num); /* New reference. */
	for (i = 0; i < ci->children_num; ++i) {
		PyTuple_SET_ITEM(children, i, cpy_oconfig_to_pyconfig(ci->children + i, item));
	}
	tmp = ((Config *) item)->children;
	((Config *) item)->children = children;
	Py_XDECREF(tmp);
	return item;
