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