int pthread_cond_wait(pthread_cond_t *cond, CRITICAL_SECTION *mutex)
{
	int last_waiter;

	EnterCriticalSection(&cond->waiters_lock);
	cond->waiters++;
	LeaveCriticalSection(&cond->waiters_lock);

	/*
	 * Unlock external mutex and wait for signal.
	 * NOTE: we've held mutex locked long enough to increment
	 * waiters count above, so there's no problem with
	 * leaving mutex unlocked before we wait on semaphore.
	 */
	LeaveCriticalSection(mutex);

	/* let's wait - ignore return value */
	WaitForSingleObject(cond->sema, INFINITE);

	/*
	 * Decrease waiters count. If we are the last waiter, then we must
	 * notify the broadcasting thread that it can continue.
	 * But if we continued due to cond_signal, we do not have to do that
	 * because the signaling thread knows that only one waiter continued.
	 */
	EnterCriticalSection(&cond->waiters_lock);
	cond->waiters--;
	last_waiter = cond->was_broadcast && cond->waiters == 0;
	LeaveCriticalSection(&cond->waiters_lock);

	if (last_waiter) {
		/*
		 * cond_broadcast was issued while mutex was held. This means
		 * that all other waiters have continued, but are contending
		 * for the mutex at the end of this function because the
		 * broadcasting thread did not leave cond_broadcast, yet.
		 * (This is so that it can be sure that each waiter has
		 * consumed exactly one slice of the semaphor.)
		 * The last waiter must tell the broadcasting thread that it
		 * can go on.
		 */
		SetEvent(cond->continue_broadcast);
		/*
		 * Now we go on to contend with all other waiters for
		 * the mutex. Auf in den Kampf!
		 */
	}
	/* lock external mutex again */
	EnterCriticalSection(mutex);

	return 0;
}