static void c_ithread_destructor (void *arg)
{
	c_ithread_t *ithread = (c_ithread_t *)arg;
	c_ithread_t *t = NULL;

	if (NULL == perl_threads)
		return;

	pthread_mutex_lock (&perl_threads->mutex);

	for (t = perl_threads->head; NULL != t; t = t->next)
		if (t == ithread)
			break;

	/* the ithread no longer exists */
	if (NULL == t)
	{
		pthread_mutex_unlock (&perl_threads->mutex);
		return;
	}

	c_ithread_destroy (ithread);

	pthread_mutex_unlock (&perl_threads->mutex);
	return;
}