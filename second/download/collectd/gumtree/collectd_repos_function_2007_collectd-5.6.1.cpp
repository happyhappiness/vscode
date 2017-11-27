static void *cpy_interactive(void *pipefd) {
	PyOS_sighandler_t cur_sig;

	/* Signal handler in a plugin? Bad stuff, but the best way to
	 * handle it I guess. In an interactive session people will
	 * press Ctrl+C at some time, which will generate a SIGINT.
	 * This will cause collectd to shutdown, thus killing the
	 * interactive interpreter, and leaving the terminal in a
	 * mess. Chances are, this isn't what the user wanted to do.
	 *
	 * So this is the plan:
	 * 1. Restore Python's own signal handler
	 * 2. Tell Python we just forked so it will accept this thread
	 *    as the main one. No version of Python will ever handle
	 *    interrupts anywhere but in the main thread.
	 * 3. After the interactive loop is done, restore collectd's
	 *    SIGINT handler.
	 * 4. Raise SIGINT for a clean shutdown. The signal is sent to
	 *    the main thread to ensure it wakes up the main interval
	 *    sleep so that collectd shuts down immediately not in 10
	 *    seconds.
	 *
	 * This will make sure that SIGINT won't kill collectd but
	 * still interrupt syscalls like sleep and pause. */

	if (PyImport_ImportModule("readline") == NULL) {
		/* This interactive session will suck. */
		cpy_log_exception("interactive session init");
	}
	cur_sig = PyOS_setsig(SIGINT, python_sigint_handler);
	PyOS_AfterFork();
	PyEval_InitThreads();
	close(*(int *) pipefd);
	PyRun_InteractiveLoop(stdin, "<stdin>");
	PyOS_setsig(SIGINT, cur_sig);
	PyErr_Print();
	state = PyEval_SaveThread();
	NOTICE("python: Interactive interpreter exited, stopping collectd ...");
	pthread_kill(main_thread, SIGINT);
	return NULL;
}