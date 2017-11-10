int pthread_cond_broadcast(pthread_cond_t *cond)
{
	EnterCriticalSection(&cond->waiters_lock);

	if ((cond->was_broadcast = cond->waiters > 0)) {
		/* wake up all waiters */
		ReleaseSemaphore(cond->sema, cond->waiters, NULL);
		LeaveCriticalSection(&cond->waiters_lock);
		/*
		 * At this point all waiters continue. Each one takes its
		 * slice of the semaphor. Now it's our turn to wait: Since
		 * the external mutex is held, no thread can leave cond_wait,
		 * yet. For this reason, we can be sure that no thread gets
		 * a chance to eat *more* than one slice. OTOH, it means
		 * that the last waiter must send us a wake-up.
		 */
		WaitForSingleObject(cond->continue_broadcast, INFINITE);
		/*
		 * Since the external mutex is held, no thread can enter
		 * cond_wait, and, hence, it is safe to reset this flag
		 * without cond->waiters_lock held.
		 */
		cond->was_broadcast = 0;
	} else {
		LeaveCriticalSection(&cond->waiters_lock);
	}
	return 0;
}