static int init_pi (int argc, char **argv)
{
	dTHXa (NULL);

	if (NULL != perl_threads)
		return 0;

	log_info ("Initializing Perl interpreter...");
#if COLLECT_DEBUG
	{
		int i = 0;

		for (i = 0; i < argc; ++i)
			log_debug ("argv[%i] = \"%s\"", i, argv[i]);
	}
#endif /* COLLECT_DEBUG */

	if (0 != pthread_key_create (&perl_thr_key, c_ithread_destructor)) {
		log_err ("init_pi: pthread_key_create failed");

		/* this must not happen - cowardly giving up if it does */
		return -1;
	}

#ifdef __FreeBSD__
	/* On FreeBSD, PERL_SYS_INIT3 expands to some expression which
	 * triggers a "value computed is not used" warning by gcc. */
	(void)
#endif
	PERL_SYS_INIT3 (&argc, &argv, &environ);

	perl_threads = (c_ithread_list_t *)smalloc (sizeof (c_ithread_list_t));
	memset (perl_threads, 0, sizeof (c_ithread_list_t));

	pthread_mutex_init (&perl_threads->mutex, NULL);
	/* locking the mutex should not be necessary at this point
	 * but let's just do it for the sake of completeness */
	pthread_mutex_lock (&perl_threads->mutex);

	perl_threads->head = c_ithread_create (NULL);
	perl_threads->tail = perl_threads->head;

	if (NULL == (perl_threads->head->interp = perl_alloc ())) {
		log_err ("init_pi: Not enough memory.");
		exit (3);
	}

	aTHX = perl_threads->head->interp;
	pthread_mutex_unlock (&perl_threads->mutex);

	perl_construct (aTHX);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	if (0 != perl_parse (aTHX_ xs_init, argc, argv, NULL)) {
		log_err ("init_pi: Unable to bootstrap Collectd.");

		perl_destruct (perl_threads->head->interp);
		perl_free (perl_threads->head->interp);
		sfree (perl_threads);

		pthread_key_delete (perl_thr_key);
		return -1;
	}

	/* Set $0 to "collectd" because perl_parse() has to set it to "-e". */
	sv_setpv (get_sv ("0", 0), "collectd");

	perl_run (aTHX);

	plugin_register_log ("perl", perl_log);
	plugin_register_notification ("perl", perl_notify);
	plugin_register_init ("perl", perl_init);

	plugin_register_read ("perl", perl_read);

	plugin_register_write ("perl", perl_write);
	plugin_register_flush ("perl", perl_flush);
	plugin_register_shutdown ("perl", perl_shutdown);
	return 0;
}