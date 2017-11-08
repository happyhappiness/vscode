int pthread_cond_destroy(pthread_cond_t *cond)
{
	CloseHandle(cond->sema);
	CloseHandle(cond->continue_broadcast);
	DeleteCriticalSection(&cond->waiters_lock);
	return 0;
}