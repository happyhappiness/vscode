 	{"unregister_flush", cpy_unregister_flush, METH_O, unregister_doc},
 	{"unregister_shutdown", cpy_unregister_shutdown, METH_O, unregister_doc},
 	{0, 0, 0, 0}
 };
 
 static int cpy_shutdown(void) {
-	cpy_callback_t *c;
 	PyObject *ret;
-	
-	/* This can happen if the module was loaded but not configured. */
-	if (state != NULL)
-		PyEval_RestoreThread(state);
 
-	for (c = cpy_shutdown_callbacks; c; c = c->next) {
+	if (!state) {
+		printf("================================================================\n");
+		printf("collectd shutdown while running an interactive session. This will\n");
+		printf("probably leave your terminal in a mess.\n");
+		printf("Run the command \"reset\" to get it back into a usable state.\n");
+		printf("You can press Ctrl+D in the interactive session to\n");
+		printf("close collectd and avoid this problem in the future.\n");
+		printf("================================================================\n");
+	}
+
+	CPY_LOCK_THREADS
+
+	for (cpy_callback_t *c = cpy_shutdown_callbacks; c; c = c->next) {
 		ret = PyObject_CallFunctionObjArgs(c->callback, c->data, (void *) 0); /* New reference. */
 		if (ret == NULL)
 			cpy_log_exception("shutdown callback");
 		else
 			Py_DECREF(ret);
 	}
 	PyErr_Print();
-	Py_Finalize();
+
+	Py_BEGIN_ALLOW_THREADS
+	cpy_unregister_list(&cpy_config_callbacks);
+	cpy_unregister_list(&cpy_init_callbacks);
+	cpy_unregister_list(&cpy_shutdown_callbacks);
+	cpy_shutdown_triggered = 1;
+	Py_END_ALLOW_THREADS
+
+	if (!cpy_num_callbacks) {
+		Py_Finalize();
+		return 0;
+	}
+
+	CPY_RELEASE_THREADS
 	return 0;
 }
 
-static void cpy_int_handler(int sig) {
-	return;
-}
+static void *cpy_interactive(void *pipefd) {
+	PyOS_sighandler_t cur_sig;
 
-static void *cpy_interactive(void *data) {
-	sigset_t sigset;
-	struct sigaction sig_int_action, old;
-	
 	/* Signal handler in a plugin? Bad stuff, but the best way to
 	 * handle it I guess. In an interactive session people will
 	 * press Ctrl+C at some time, which will generate a SIGINT.
 	 * This will cause collectd to shutdown, thus killing the
 	 * interactive interpreter, and leaving the terminal in a
 	 * mess. Chances are, this isn't what the user wanted to do.
-	 * 
+	 *
 	 * So this is the plan:
-	 * 1. Block SIGINT in the main thread.
-	 * 2. Install our own signal handler that does nothing.
-	 * 3. Unblock SIGINT in the interactive thread.
+	 * 1. Restore Python's own signal handler
+	 * 2. Tell Python we just forked so it will accept this thread
+	 *    as the main one. No version of Python will ever handle
+	 *    interrupts anywhere but in the main thread.
+	 * 3. After the interactive loop is done, restore collectd's
+	 *    SIGINT handler.
+	 * 4. Raise SIGINT for a clean shutdown. The signal is sent to
+	 *    the main thread to ensure it wakes up the main interval
+	 *    sleep so that collectd shuts down immediately not in 10
+	 *    seconds.
 	 *
 	 * This will make sure that SIGINT won't kill collectd but
-	 * still interrupt syscalls like sleep and pause.
-	 * It does not raise a KeyboardInterrupt exception because so
-	 * far nobody managed to figure out how to do that. */
-	memset (&sig_int_action, '\0', sizeof (sig_int_action));
-	sig_int_action.sa_handler = cpy_int_handler;
-	sigaction (SIGINT, &sig_int_action, &old);
-	
-	sigemptyset(&sigset);
-	sigaddset(&sigset, SIGINT);
-	pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);
-	PyEval_AcquireThread(state);
+	 * still interrupt syscalls like sleep and pause. */
+
 	if (PyImport_ImportModule("readline") == NULL) {
 		/* This interactive session will suck. */
 		cpy_log_exception("interactive session init");
 	}
+	cur_sig = PyOS_setsig(SIGINT, python_sigint_handler);
+	PyOS_AfterFork();
+	PyEval_InitThreads();
+	close(*(int *) pipefd);
 	PyRun_InteractiveLoop(stdin, "<stdin>");
+	PyOS_setsig(SIGINT, cur_sig);
 	PyErr_Print();
-	PyEval_ReleaseThread(state);
+	state = PyEval_SaveThread();
 	NOTICE("python: Interactive interpreter exited, stopping collectd ...");
-	/* Restore the original collectd SIGINT handler and raise SIGINT.
-	 * The main thread still has SIGINT blocked and there's nothing we
-	 * can do about that so this thread will handle it. But that's not
-	 * important, except that it won't interrupt the main loop and so
-	 * it might take a few seconds before collectd really shuts down. */
-	sigaction (SIGINT, &old, NULL);
-	raise(SIGINT);
-	pause();
+	pthread_kill(main_thread, SIGINT);
 	return NULL;
 }
 
 static int cpy_init(void) {
-	cpy_callback_t *c;
 	PyObject *ret;
+	int pipefd[2];
+	char buf;
 	static pthread_t thread;
-	sigset_t sigset;
-	
+
 	if (!Py_IsInitialized()) {
 		WARNING("python: Plugin loaded but not configured.");
 		plugin_unregister_shutdown("python");
+		Py_Finalize();
 		return 0;
 	}
-	PyEval_InitThreads();
-	/* Now it's finally OK to use python threads. */
-	for (c = cpy_init_callbacks; c; c = c->next) {
+	main_thread = pthread_self();
+	if (do_interactive) {
+		if (pipe(pipefd)) {
+			ERROR("python: Unable to create pipe.");
+			return 1;
+		}
+		if (plugin_thread_create(&thread, NULL, cpy_interactive, pipefd + 1)) {
+			ERROR("python: Error creating thread for interactive interpreter.");
+		}
+		if(read(pipefd[0], &buf, 1))
+			;
+		(void)close(pipefd[0]);
+	} else {
+		PyEval_InitThreads();
+		state = PyEval_SaveThread();
+	}
+	CPY_LOCK_THREADS
+	for (cpy_callback_t *c = cpy_init_callbacks; c; c = c->next) {
 		ret = PyObject_CallFunctionObjArgs(c->callback, c->data, (void *) 0); /* New reference. */
 		if (ret == NULL)
 			cpy_log_exception("init callback");
 		else
 			Py_DECREF(ret);
 	}
-	sigemptyset(&sigset);
-	sigaddset(&sigset, SIGINT);
-	pthread_sigmask(SIG_BLOCK, &sigset, NULL);
-	state = PyEval_SaveThread();
-	if (do_interactive) {
-		if (plugin_thread_create(&thread, NULL, cpy_interactive, NULL)) {
-			ERROR("python: Error creating thread for interactive interpreter.");
-		}
-	}
+	CPY_RELEASE_THREADS
 
 	return 0;
 }
 
 static PyObject *cpy_oconfig_to_pyconfig(oconfig_item_t *ci, PyObject *parent) {
-	int i;
 	PyObject *item, *values, *children, *tmp;
-	
+
 	if (parent == NULL)
 		parent = Py_None;
-	
+
 	values = PyTuple_New(ci->values_num); /* New reference. */
-	for (i = 0; i < ci->values_num; ++i) {
+	for (int i = 0; i < ci->values_num; ++i) {
 		if (ci->values[i].type == OCONFIG_TYPE_STRING) {
 			PyTuple_SET_ITEM(values, i, cpy_string_to_unicode_or_bytes(ci->values[i].value.string));
 		} else if (ci->values[i].type == OCONFIG_TYPE_NUMBER) {
 			PyTuple_SET_ITEM(values, i, PyFloat_FromDouble(ci->values[i].value.number));
 		} else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN) {
 			PyTuple_SET_ITEM(values, i, PyBool_FromLong(ci->values[i].value.boolean));
 		}
 	}
-	
+
 	tmp = cpy_string_to_unicode_or_bytes(ci->key);
 	item = PyObject_CallFunction((void *) &ConfigType, "NONO", tmp, parent, values, Py_None);
 	if (item == NULL)
 		return NULL;
 	children = PyTuple_New(ci->children_num); /* New reference. */
-	for (i = 0; i < ci->children_num; ++i) {
+	for (int i = 0; i < ci->children_num; ++i) {
 		PyTuple_SET_ITEM(children, i, cpy_oconfig_to_pyconfig(ci->children + i, item));
 	}
 	tmp = ((Config *) item)->children;
 	((Config *) item)->children = children;
 	Py_XDECREF(tmp);
 	return item;
