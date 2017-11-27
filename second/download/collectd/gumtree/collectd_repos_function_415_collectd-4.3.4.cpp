static int perl_shutdown (void)
{
	c_ithread_t *t = NULL;

	int ret = 0;

	dTHX;

	plugin_unregister_complex_config ("perl");

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	log_debug ("perl_shutdown: c_ithread: interp = %p (active threads: %i)",
			aTHX, perl_threads->number_of_threads);

	plugin_unregister_log ("perl");
	plugin_unregister_notification ("perl");
	plugin_unregister_init ("perl");
	plugin_unregister_read ("perl");
	plugin_unregister_write ("perl");

	ret = pplugin_call_all (aTHX_ PLUGIN_SHUTDOWN);

	pthread_mutex_lock (&perl_threads->mutex);
	t = perl_threads->tail;

	while (NULL != t) {
		c_ithread_t *thr = t;

		/* the pointer has to be advanced before destroying
		 * the thread as this will free the memory */
		t = t->prev;

		c_ithread_destroy (thr);
	}

	pthread_mutex_unlock (&perl_threads->mutex);
	pthread_mutex_destroy (&perl_threads->mutex);

	sfree (perl_threads);

	pthread_key_delete (perl_thr_key);

	PERL_SYS_TERM ();

	plugin_unregister_shutdown ("perl");
	return ret;
}