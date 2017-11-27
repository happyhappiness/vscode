static void perl_log (int level, const char *msg)
{
	dTHX;

	if (NULL == perl_threads)
		return;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	pplugin_call_all (aTHX_ PLUGIN_LOG, level, msg);
	return;
}