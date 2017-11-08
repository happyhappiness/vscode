int pthread_cond_signal(pthread_cond_t *cond)
{
	int have_waiters;

	EnterCriticalSection(&cond->waiters_lock);
	have_waiters = cond->waiters > 0;
	LeaveCriticalSection(&cond->waiters_lock);

	/*
	 * Signal only when there are waiters
	 */
	if (have_waiters)
		return ReleaseSemaphore(cond->sema, 1, NULL) ?
			0 : err_win_to_posix(GetLastError());
	else
		return 0;
}