int pthread_cond_init(pthread_cond_t *cond, const void *unused)
{
	cond->waiters = 0;
	cond->was_broadcast = 0;
	InitializeCriticalSection(&cond->waiters_lock);

	cond->sema = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
	if (!cond->sema)
		die("CreateSemaphore() failed");

	cond->continue_broadcast = CreateEvent(NULL,	/* security */
				FALSE,			/* auto-reset */
				FALSE,			/* not signaled */
				NULL);			/* name */
	if (!cond->continue_broadcast)
		die("CreateEvent() failed");

	return 0;
}